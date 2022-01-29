#include "src/utils/Arduboy2Ext.h"
#include "AstarokGame.h"
#include <EEPROM.h>

void AstarokGame::drawScorePanel() {

    Sprites::drawExternalMask(15, 15, Images::GameOver, Images::GameOver_Mask, 0, 0);

}

void AstarokGame::drawMobs() {

    for (AISprite &obj : this->mobs) {

        if (obj.getActive() || obj.explodeCounter > 16) {

            if (obj.getRightX() - this->camera.x > 0 && obj.x - this->camera.x < 128) {
                obj.draw();
            }

        }

        if (obj.explodeCounter > 0) {

            Sprites::drawExternalMask(obj.x - this->camera.x - 2, obj.y - this->camera.y - 2, 
                                      pgm_read_word_near(&Images::Puffs[(21 - obj.explodeCounter) / 3]), 
                                      pgm_read_word_near(&Images::Puff_Masks[(21 - obj.explodeCounter) / 3]), 
                                      this->mapNumber % 2 == 0 ? 0 : 1, 0);

        }

    }

}

void AstarokGame::drawHUD() {

    uint16_t tmpScore = this->score + this->player.x / Constants::TileSize; 
    uint8_t digits[6] = {};
    extractDigits(digits, tmpScore);

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        for(size_t index = 0; index < 58; ++index) arduboy->sBuffer[index] = 0xFF;

        Sprites::drawErase(1, 1, Images::Heart, this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline);
        Sprites::drawErase(9, 1, Images::Heart, this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline);
        Sprites::drawErase(17, 1, Images::Heart, this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline);

        for (uint8_t x = 6; x > 0; x--) {
            Sprites::drawErase(27 + ((6 - x) * 5), 1, Images::Numbers, digits[x - 1]);
        }

    }
    else {

        for(size_t index = 0; index < 58; ++index) arduboy->sBuffer[index] = 0x00;

        Sprites::drawSelfMasked(1, 1, Images::Heart, this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline);
        Sprites::drawSelfMasked(9, 1, Images::Heart, this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline);
        Sprites::drawSelfMasked(17, 1, Images::Heart, this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline);

        for (uint8_t x = 6; x > 0; x--) {
            Sprites::drawSelfMasked(27 + ((6 - x) * 5), 1, Images::Numbers, digits[x - 1]);
        }

    }

}

void AstarokGame::drawMap_Background() {

    int16_t backgroundXOffset = (this->camera.x / 4) % 64;
    int16_t backgroundYOffset = (this->camera.y / 12) - 8;

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        for (uint8_t i = 0; i <= 128; i += 64) {
            Sprites::drawOverwrite(i - backgroundXOffset, backgroundYOffset + 2, Images::Sky, 0);
        }

    }
    else {

        for (uint8_t i = 0; i <= 128; i += 64) {

            Sprites::drawOverwrite(i + 7 - backgroundXOffset, backgroundYOffset, Images::Underground_Chain, 0);
            Sprites::drawOverwrite(i + 22 - backgroundXOffset, backgroundYOffset + 6, Images::Underground_Brick, 0);
            Sprites::drawOverwrite(i + 42 - backgroundXOffset, backgroundYOffset + 11, Images::Underground_Brick, 0);

        }

    }

    for (int x = (this->camera.x / Constants::TileSize) - 12; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (this->level.isTile(x, y)) {

                if (y == 15 || this->level.isTile(x, y + 1)) {

                    if (this->mapNumber % 2 == MapLevel::AboveGround) {   
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                                  Images::Tile_Brick, Images::Tile_Mask, MapLevel::AboveGround, 0);
                    }
                    else {
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                                  Images::Tile_Brick, Images::Tile_Mask, MapLevel::BelowGround, 0);
                    }

                }
                else {
                    Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                              Images::Platform, Images::Platform_Mask, 0, 0);

                }

            }
            else {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::QBlock ... ObjectTypes::Bricks:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, pgm_read_word_near(&Images::SpriteImages[tile]), pgm_read_word_near(&Images::SpriteMasks[tile]), 0, 0);
                        break;

                    case ObjectTypes::AboveGroundExit:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x - 36, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_00, Images::Outside_Exit_00_Mask, 0, 0);
                        break;

                    case ObjectTypes::UnderGroundExit:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->camera.x - 13, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_00, 0);
                        break;

                    case ObjectTypes::Sign:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->camera.x - 4, y * Constants::TileSize - this->camera.y - 4, Images::SignPost, this->mapNumber % 2);
                        break;

                    case ObjectTypes::Coin:
                        Sprites::drawSelfMasked(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Coins_Masks, arduboy->getFrameCount(16) / 4);
                        Sprites::drawErase(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Coins, arduboy->getFrameCount(16) / 4);
                        break;

                    case ObjectTypes::Chest_Closed:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 3, Images::Chest_Closed, Images::Chest_Closed_Mask, 0, 0);
                        break;

                    case ObjectTypes::Chest_Open:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 2, Images::Chest_Open, Images::Chest_Open_Mask, 0, 0);
                        break;

                    default: break;
                }

            }

        }

    }

}

void AstarokGame::drawMap_Foreground() {

    for (int x = this->camera.x / Constants::TileSize; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (!this->level.isTile(x, y)) {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::AboveGroundExit:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x - 10, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_01, Images::Outside_Exit_01_Mask, 0, 0);
                        break;

                    case ObjectTypes::UnderGroundExit:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_01, 0);
                        break;

                    default: break;

                }

            }

        }

    }

}

void AstarokGame::drawPlayer() {


    // Rnder player ..

    switch (this->event) {

        case EventType::StartLevel:

            if (this->eventCounter < 12) { // Do not display for first half of puff cycle.
                this->player.draw();
            }

            break;

        case EventType::Death_Init:
        case EventType::Death:
        case EventType::Playing:   
        case EventType::Flash:   
            if (!(this->eventCounter % 2)) this->player.draw();
            break;

        default:
            this->player.draw();
            break;

    }


    // Render entrance puff of smoke ..

    if (this->event == EventType::StartLevel) { 

        Sprites::drawExternalMask(this->player.x - this->camera.x - 2, this->player.y - this->camera.y - 4, 
                                  pgm_read_word_near(&Images::Puffs[(28 - this->eventCounter) / 4]), 
                                  pgm_read_word_near(&Images::Puff_Masks[(28 - this->eventCounter) / 4]), 
                                  this->mapNumber % 2 == 0 ? 0 : 1, 0);

    }

}

void AstarokGame::draw() {

    drawMap_Background(); 
    drawPlayer(); 
    drawMobs(); 
    drawMap_Foreground(); 
    drawHUD();

    //arduboy->drawRect(player.getLeftX() - this->camera.x, player.getTopY() - this->camera.y, player.getWidth() - 3, player.getHeight(), BLACK);


}
