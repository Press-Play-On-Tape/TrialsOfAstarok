#include "src/utils/Arduboy2Ext.h"

void TitleScreen() {


    Sprites::drawOverwrite(16, 4, Images::Title_Top, 0);
    Sprites::drawOverwrite(27, 33, Images::Title_Bottom, 0);
    Sprites::drawSelfMasked(35, 17, Images::Text_Trials, 0);

    if (soundOn) {
        Sprites::drawExternalMask(119, 56, Images::Sound_On, Images::Sound_Mask, 0, 0);
    }
    else {
        Sprites::drawExternalMask(119, 56, Images::Sound_Off, Images::Sound_Mask, 0, 0);
    }

    if (arduboy.justPressed(A_BUTTON)) {
        gameState = GameState::Seed_Init;
    }

    if (arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) {
        soundOn = !soundOn;
        EEPROM.update(Constants::EEPROM_Sounds, soundOn);
    }

    if (arduboy.justPressed(B_BUTTON)) {
        gameState = GameState::HighScore_DisplayAll;
    }

}

