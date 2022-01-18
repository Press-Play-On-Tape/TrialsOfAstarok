#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Constants.h"
#include "src/images/Images.h"

void seed_Init() {

    seedVars.reset();
    gameState = GameState::Seed;

}

void seed() {

    for (uint8_t i = 0; i < 5; i++) {

        Sprites::drawOverwrite(20 + (i* 14), 20, Images::Rune_Frame, 0);
        Sprites::drawOverwrite(23 + (i* 14), 24, Images::Runes, seedVars.seed[i]);

        // seedVars[i] = static_cast<uint8_t>(EEPROM.read(Constants::EEPROM_Seeds + i));
    }

    Sprites::drawSelfMasked(24 + (seedVars.index * 14), 15, Images::ArrowUp, 0);
    Sprites::drawSelfMasked(24 + (seedVars.index* 14), 36, Images::ArrowDown, 0);


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
        for (uint8_t a = 0; a < Constants::GameSeeds; a++) Game.Seeds[a] = random(255);
        gameState = GameState::Game_Init;
      }

}

