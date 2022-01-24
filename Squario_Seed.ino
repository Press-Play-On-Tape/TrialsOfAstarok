#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Constants.h"
#include "src/images/Images.h"

void seed_Init() {

    seedVars.reset();
    gameState = GameState::Seed;

}

void seed() {

    Sprites::drawSelfMasked(34, 8, Images::EnterRunes_Text, 0);
    Sprites::drawSelfMasked(24, 21, Images::EnterRunes_LH, 0);
    Sprites::drawSelfMasked(96, 21, Images::EnterRunes_RH, 0);

    Sprites::drawOverwrite(2, 7, Images::Underground_Brick, 0);
    Sprites::drawOverwrite(107, 7, Images::Underground_Brick, 0);
    Sprites::drawOverwrite(7, 18, Images::Underground_Chain, 0);
    Sprites::drawOverwrite(118, 18, Images::Underground_Chain, 0);


    arduboy.drawFastHLine(24, 21, 72);
    arduboy.drawFastHLine(24, 54, 72);
    arduboy.drawFastHLine(26, 56, 70);

    for (uint8_t i = 0; i < 5; i++) {

        if (i == seedVars.index && seedVars.spinIndex > 0) {
            Sprites::drawOverwrite(30 + (i* 14), 31, Images::Rune_Frame, 16 - seedVars.spinIndex);
        }
        else {
            Sprites::drawOverwrite(30 + (i* 14), 31, Images::Rune_Frame, 0);
            Sprites::drawOverwrite(33 + (i* 14), 35, Images::Runes, seedVars.seed[i]);
        }

    }

    Sprites::drawSelfMasked(33 + (seedVars.index * 14), 26, Images::ArrowUp, 0);
    Sprites::drawSelfMasked(33 + (seedVars.index* 14), 47, Images::ArrowDown, 0);


    if (seedVars.spinIndex == 0) {

        if (arduboy.justPressed(UP_BUTTON)) {
            seedVars.incValue();
        }

        if (arduboy.justPressed(DOWN_BUTTON)) { 
            seedVars.decValue();
        }

        if (arduboy.justPressed(LEFT_BUTTON)) { 
            seedVars.decIndex();
        }

        if (arduboy.justPressed(RIGHT_BUTTON)) { 
            seedVars.incIndex();
        }

        if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {

            randomSeed(seedVars.getSeedValue());
            for (uint8_t &a : game.seeds) {
                a = random(255);
            }

            gameState = GameState::Game_Init;

        }

    }

    seedVars.decSpinIndex();

}

