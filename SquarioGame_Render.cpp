#include "src/utils/Arduboy2Ext.h"
#include "SquarioGame.h"
#include <EEPROM.h>

void SquarioGame::drawScorePanel(Font4x6 &font4x6) {

    Sprites::drawExternalMask(15, 15, Images::GameOver, Images::GameOver_Mask, 0, 0);

}

void SquarioGame::drawMobs() {

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (this->mobs[a].getActive()) {

            if (this->mobs[a].getRightX() - this->camera.x > 0 && this->mobs[a].x - this->camera.x < 128) {
                this->mobs[a].draw();
            }

        }

    }

}

void SquarioGame::drawHUD() {

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

void SquarioGame::drawMap_Background() {

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

    for (int x = this->camera.x / Constants::TileSize; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (this->level.isTile(x, y)) {

                if (this->mapNumber % 2 == MapLevel::AboveGround) {   
                    Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                              pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]),  
                                              pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), MapLevel::AboveGround, 0);
                }
                else {
                    Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                              pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]), 
                                              pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), 0, 0);
                }

            }
            else {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::STQBlock ... ObjectTypes::STBricks:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, pgm_read_word_near(&Images::SpriteImages[tile]), pgm_read_word_near(&Images::SpriteMasks[tile]), 0, 0);
                        break;

                    case ObjectTypes::STAboveGroundExit:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x - 36, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_00, Images::Outside_Exit_00_Mask, 0, 0);
                        break;

                    case ObjectTypes::STUnderGroundExit:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->camera.x - 13, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_00, 0);
                        break;

                    case ObjectTypes::STSign:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->camera.x - 4, y * Constants::TileSize - this->camera.y - 4, Images::SignPost, this->mapNumber % 2);
                        break;

                    default: break;
                }

            }

        }

    }

}

void SquarioGame::drawMap_Foreground() {

    for (int x = this->camera.x / Constants::TileSize; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (!this->level.isTile(x, y)) {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::STAboveGroundExit:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->camera.x - 10, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_01, Images::Outside_Exit_01_Mask, 0, 0);
                        break;

                    case ObjectTypes::STUnderGroundExit:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_01, 0);
                        break;

                    default: break;

                }

            }

        }

    }

}

void SquarioGame::drawPlayer() {

    if ((this->event == EventType::StartLevel && this->eventCounter < 12) || this->event != EventType::StartLevel) { 
        this->player.draw();
    }

    if (this->event == EventType::StartLevel) { 
    
        Sprites::drawExternalMask(this->player.x - this->camera.x - 2, this->player.y - this->camera.y - 4, 
                                  pgm_read_word_near(&Images::Puffs[(28 - this->eventCounter) / 4]), 
                                  pgm_read_word_near(&Images::Puff_Masks[(28 - this->eventCounter) / 4]), 
                                  this->mapNumber % 2 == 0 ? 0 : 1, 0);

    }

}

void SquarioGame::draw() {

    switch (this->event) {

        case EventType::Death_Init:
        case EventType::Death:
        case EventType::Playing:   
            drawMap_Background(); 
            drawHUD();
            drawMobs(); 
            if (!(this->eventCounter % 2)) drawPlayer();
            drawMap_Foreground(); 
            break;

        case EventType::StartLevel:   
            drawMap_Background(); 
            drawPlayer(); 
            drawHUD();
            drawMobs(); 
            drawMap_Foreground(); 
            break;

        default: break;

    }

// if (arduboy->pressed(A_BUTTON)){
//   arduboy->drawRect(this->player.x - this->camera.x + 2, this->player.y - this->camera.y, this->player.getWidth() - 2, this->player.getHeight(), BLACK);
// }

}
