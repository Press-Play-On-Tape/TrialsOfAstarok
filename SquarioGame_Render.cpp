#include "src/utils/Arduboy2Ext.h"
#include "SquarioGame.h"
#include <EEPROM.h>

void SquarioGame::drawScorePanel(Font4x6 &font4x6) {

    arduboy->drawRect(22, 19, 83, 39, BLACK);
    arduboy->fillRect(23, 20, 81, 37, WHITE);
    Sprites::drawExternalMask(15, 8, Images::Scores, Images::Scores_Mask, 0, 0);

    font4x6.setTextColor(BLACK);
    font4x6.setCursor(28, 31); font4x6.print(F("Score"));
    font4x6.setCursor(28, 39); font4x6.print(F("Dist"));
    font4x6.setCursor(28, 47); font4x6.print(F("Total"));

    uint8_t digits[6] = {};
    extractDigits(digits, this->score);

    font4x6.setCursor(70, 31);
    for (uint8_t i = 0; i < 6; i++) {
        font4x6.print(static_cast<char>(digits[5 - i] + 48));
    }

    extractDigits(digits, this->distancePoints);

    font4x6.setCursor(70, 39);
    for (uint8_t i = 0; i < 6; i++) {
        font4x6.print(static_cast<char>(digits[5 - i] + 48));
    }

    extractDigits(digits, this->totalScore);

    font4x6.setCursor(70, 47);
    for (uint8_t i = 0; i < 6; i++) {
        font4x6.print(static_cast<char>(digits[5 - i] + 48));
    }

    font4x6.setTextColor(WHITE);

}

void SquarioGame::drawMobs() {

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (this->mobs[a].getActive()) {

            if (this->mobs[a].getRightX() - this->cameraX > 0 && this->mobs[a].x - this->cameraX < 128) {
                this->mobs[a].draw();
            }

        }

    }

}

void SquarioGame::drawHUD() {

    uint16_t tmpScore = this->score + this->distancePoints + this->player.x / Constants::TileSize; 
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

    int16_t backgroundXOffset = (this->cameraX / 4) % 64;
    int16_t backgroundYOffset = (this->cameraY / 12) - 8;

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        Sprites::drawOverwrite(0 - backgroundXOffset, backgroundYOffset + 2, Images::Sky, 0);
        Sprites::drawOverwrite(64 - backgroundXOffset, backgroundYOffset + 2, Images::Sky, 0);
        Sprites::drawOverwrite(128 - backgroundXOffset, backgroundYOffset + 2, Images::Sky, 0);

    }
    else {

        for (uint8_t a = 0; a <= 128; a += 64) {

            Sprites::drawOverwrite(a + 2 - backgroundXOffset, backgroundYOffset, Images::Underground_Chain, 0);
            Sprites::drawOverwrite(a + 22 - backgroundXOffset, backgroundYOffset + 6, Images::Underground_Brick, 0);
            Sprites::drawOverwrite(a + 42 - backgroundXOffset, backgroundYOffset + 11, Images::Underground_Brick, 0);

        }

    }

    for (int x = this->cameraX / Constants::TileSize; x < (this->cameraX / Constants::TileSize) + 17; x++) {

        for (int y = this->cameraY / Constants::TileSize; y < (this->cameraY / Constants::TileSize) + 9; y++) {

            if (this->level.isTile(x, y)) {

                if (this->mapNumber % 2 == MapLevel::AboveGround) {   
                    Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, 
                                              pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]),  
                                              pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), MapLevel::AboveGround, 0);
                }
                else {
                    Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, 
                                              pgm_read_word_near(&Images::SpriteImages[ObjectTypes::STBricks]), 
                                              pgm_read_word_near(&Images::SpriteMasks[ObjectTypes::STBricks]), 0, 0);
                }

            }
            else {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::STQBlock ... ObjectTypes::STBricks:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY, pgm_read_word_near(&Images::SpriteImages[tile]), pgm_read_word_near(&Images::SpriteMasks[tile]), 0, 0);
                        break;

                    case ObjectTypes::STAboveGroundExit:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX - 36, y * Constants::TileSize - this->cameraY - 24, Images::Outside_Exit_00, Images::Outside_Exit_00_Mask, 0, 0);
                        break;

                    case ObjectTypes::STUnderGroundExit:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->cameraX - 13, y * Constants::TileSize - this->cameraY - 4, Images::Underground_Exit_00, 0);
                        break;

                    case ObjectTypes::STSign:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->cameraX - 4, y * Constants::TileSize - this->cameraY - 4, Images::SignPost, this->mapNumber % 2);
                        break;

                    default: break;
                }

            }

        }

    }

}

void SquarioGame::drawMap_Foreground() {

    for (int x = this->cameraX / Constants::TileSize; x < (this->cameraX / Constants::TileSize) + 17; x++) {

        for (int y = this->cameraY / Constants::TileSize; y < (this->cameraY / Constants::TileSize) + 9; y++) {

            if (!this->level.isTile(x, y)) {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::STAboveGroundExit:
                        Sprites::drawExternalMask(x * Constants::TileSize - this->cameraX - 10, y * Constants::TileSize - this->cameraY - 24, Images::Outside_Exit_01, Images::Outside_Exit_01_Mask, 0, 0);
                        break;

                    case ObjectTypes::STUnderGroundExit:
                        Sprites::drawOverwrite(x * Constants::TileSize - this->cameraX, y * Constants::TileSize - this->cameraY - 4, Images::Underground_Exit_01, 0);
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

        if ( this->mapNumber % 2 == 0) {
        
            Sprites::drawExternalMask(this->player.x - this->cameraX, this->player.y - this->cameraY - 4, 
                                    pgm_read_word_near(&Images::Puffs[(28 - this->eventCounter) / 4]), 
                                    pgm_read_word_near(&Images::Puff_Masks[(28 - this->eventCounter) / 4]), 
                                    0,0);
        }
        else {

            Sprites::drawErase(this->player.x - this->cameraX, this->player.y - this->cameraY - 4, 
                                    pgm_read_word_near(&Images::Puffs[(28 - this->eventCounter) / 4]), 
                                    0);
        }

    }

    if (this->health) {

        for (uint8_t a = 0; a < this->health; a++) {
            arduboy->drawFastHLine(this->player.x + 1 - this->cameraX, this->player.y+11-(a*2)-this->cameraY, 6, WHITE);
            arduboy->drawFastHLine(this->player.x + 1 - this->cameraX, this->player.y+10-(a*2)-this->cameraY, 6, WHITE);
        }

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

}
