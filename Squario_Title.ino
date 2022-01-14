

void TitleScreen() {

  arduboy.drawBitmap(14,0,TitleSquarioText,96,32,1);
  arduboy.drawBitmap(66,29,TitleSquarioGuys,53,32,1);
  arduboy.setCursor(0,56); arduboy.print(F("Sound: "));
  arduboy.setCursor(0,48); arduboy.print(F("Seed:  ")); arduboy.print(RandomSeedSeed);

  if (SoundOn) arduboy.print(F("On"));
  else arduboy.print(F("Off"));

      if (arduboy.justPressed(A_BUTTON)) {
        randomSeed(RandomSeedSeed);
        for (uint8_t a = 0; a < GameSeeds; a++) Game.Seeds[a] = random(255);
        gameState = GameState::Game_Init;
      }

      if (arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) SoundOn = !SoundOn;

      if (arduboy.justPressed(B_BUTTON)) {
        gameState = GameState::HighScore_DisplayAll;
      }

      if (arduboy.justPressed(UP_BUTTON)) {
        if ( RandomSeedSeed == 255 ) RandomSeedSeed = 1;
        else RandomSeedSeed++;
      }

      if (arduboy.justPressed(DOWN_BUTTON)) { 
        if ( RandomSeedSeed == 1 ) RandomSeedSeed = 255;
        else RandomSeedSeed--;
      }

}

