#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Constants.h"
#include "src/images/Images.h"

void seed_Init() {

    seedVars.reset();
    gameState = GameState::Seed;

}

void seed() {

    Sprites::drawOverwrite(16, 4, Images::Title_Top, 0);
    Sprites::drawSelfMasked(35, 17, Images::Text_Seed, 0);

    for (uint8_t i = 0; i < 5; i++) {

        Sprites::drawOverwrite(30 + (i* 14), 40, Images::Rune_Frame, 0);
        Sprites::drawOverwrite(33 + (i* 14), 44, Images::Runes, seedVars.seed[i]);

    }

    Sprites::drawSelfMasked(34 + (seedVars.index * 14), 35, Images::ArrowUp, 0);
    Sprites::drawSelfMasked(34 + (seedVars.index* 14), 56, Images::ArrowDown, 0);


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

    if (arduboy.justPressed(A_BUTTON)) {

        randomSeed(seedVars.getSeedValue());
        for (uint8_t a = 0; a < Constants::GameSeeds; a++) game.Seeds[a] = random(255);
        gameState = GameState::Game_Init;

    }

    arduboy.drawPixel(24, 62, WHITE);
    arduboy.drawPixel(102, 62, WHITE);
    arduboy.drawFastHLine(25, 63, 77);

}

