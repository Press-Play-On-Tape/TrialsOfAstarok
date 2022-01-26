#include "src/utils/Arduboy2Ext.h"

void titleScreen() {

    uint8_t justPressed = arduboy.justPressedButtons();

    Sprites::drawOverwrite(24, 4, Images::Title, 0);
    Sprites::drawOverwrite(15, 0, Images::Underground_Chain, 0);
    Sprites::drawOverwrite(110, 0, Images::Underground_Chain, 0);
    Sprites::drawOverwrite(0, 27, Images::Underground_Brick, 0);
    Sprites::drawOverwrite(109, 27, Images::Underground_Brick, 0);
   
    Sprites::drawOverwrite(titleScreenVars.index == TitleScreenMode::Play ? 35 : 65, 59, Images::Title_Highlight, 0);

    if (arduboy.audio.enabled()) {
        Sprites::drawExternalMask(119, 56, Images::Sound_On, Images::Sound_Mask, 0, 0);
    }
    else {
        Sprites::drawExternalMask(119, 56, Images::Sound_Off, Images::Sound_Mask, 0, 0);
    }

    if ((justPressed & A_BUTTON) || (justPressed & B_BUTTON)) {

        switch (titleScreenVars.index) {

            case TitleScreenMode::Play:
                gameState = GameState::Seed_Init;
                break;

            case TitleScreenMode::HighScore:
                gameState = GameState::HighScore_NoFlash;
                break;

        }

    }

    if ((justPressed & UP_BUTTON) || (justPressed & DOWN_BUTTON)) {
        
        if (arduboy.audio.enabled()) {

            arduboy.audio.off(); 
            arduboy.audio.saveOnOff();

        }
        else {

            arduboy.audio.on(); 
            arduboy.audio.saveOnOff();

        }

    }

    if (justPressed & LEFT_BUTTON) {

        titleScreenVars.index = TitleScreenMode::Play;

    }

    if (justPressed & RIGHT_BUTTON) {

        titleScreenVars.index = TitleScreenMode::HighScore;

    }

}

