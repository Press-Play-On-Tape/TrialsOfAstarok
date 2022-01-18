#include "src/utils/Arduboy2Ext.h"

void TitleScreen() {


  Sprites::drawOverwrite(16, 4, Images::Title, 0);

  if (SoundOn) {
    Sprites::drawExternalMask(119, 56, Images::Sound_On, Images::Sound_Mask, 0, 0);
  }
  else {
    Sprites::drawExternalMask(119, 56, Images::Sound_Off, Images::Sound_Mask, 0, 0);
  }
    
    


      if (arduboy.justPressed(A_BUTTON)) {
        gameState = GameState::Seed_Init;
      }

      if (arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) SoundOn = !SoundOn;

      if (arduboy.justPressed(B_BUTTON)) {
        gameState = GameState::HighScore_DisplayAll;
      }

}

