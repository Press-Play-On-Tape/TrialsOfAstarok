#include "src/utils/Arduboy2Ext.h"

void TitleScreen() {


    Sprites::drawOverwrite(24, 4, Images::Title, 0);
    Sprites::drawOverwrite(15, 0, Images::Underground_Chain, 0);
    Sprites::drawOverwrite(110, 0, Images::Underground_Chain, 0);
    Sprites::drawOverwrite(0, 27, Images::Underground_Brick, 0);
    Sprites::drawOverwrite(109, 27, Images::Underground_Brick, 0);
   
    Sprites::drawOverwrite(titleScreenVars.index == TitleScreenMode::Play ? 35 : 65, 59, Images::Title_Highlight, 0);

    if (soundOn) {
        Sprites::drawExternalMask(119, 56, Images::Sound_On, Images::Sound_Mask, 0, 0);
    }
    else {
        Sprites::drawExternalMask(119, 56, Images::Sound_Off, Images::Sound_Mask, 0, 0);
    }

    if (arduboy.justPressed(A_BUTTON)) {

        switch (titleScreenVars.index) {

            case TitleScreenMode::Play:
                gameState = GameState::Seed_Init;
                break;

            case TitleScreenMode::HighScore:
                gameState = GameState::HighScore_DisplayAll;
                break;

        }

    }

    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON)) {
        soundOn = !soundOn;
        EEPROM.update(Constants::EEPROM_Sounds, soundOn);
    }

    if (arduboy.justPressed(LEFT_BUTTON)) {

        titleScreenVars.index = TitleScreenMode::Play;
        
    }

    if (arduboy.justPressed(RIGHT_BUTTON)) {

        titleScreenVars.index = TitleScreenMode::HighScore;
        
    }

}

