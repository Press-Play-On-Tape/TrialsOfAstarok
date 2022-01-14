#include <Arduboy2.h>
#include <EEPROM.h>

void initEEPROM() {

  uint8_t c1 = EEPROM.read(EEPROM_START_C1);
  uint8_t c2 = EEPROM.read(EEPROM_START_C2);

  if (c1 != 'S' || c2 != 'Q') {

    EEPROM.update(EEPROM_START_C1, 'S');
    EEPROM.update(EEPROM_START_C2, 'Q');  

    uint16_t score = 1;
    
    
    for (uint8_t i = 0; i < 10; i++) {

        EEPROM.put(EEPROM_SCORES + (5 * i), score++);
        EEPROM.update(EEPROM_SCORES + (5 * i) + 2, 65 + i);
        EEPROM.update(EEPROM_SCORES + (5 * i) + 3, 65 + i);
        EEPROM.update(EEPROM_SCORES + (5 * i) + 4, 65 + i);


    }
  }  
}

uint8_t checkHighScoreSlot(uint16_t score) {

  uint16_t tmpScore = 0;

  // High score processing
  for (byte i = 0; i < 10; i++) {
    EEPROM.get(EEPROM_SCORES + (5 * i), tmpScore);
    if (tmpScore < score) {
      return i;
    }
  }

  return EEPROM_NO_SLOT;
}

void enterHighScore() {
  // Each block of EEPROM has 10 high scores, and each high score entry
  // is 5 bytes long:  3 bytes for initials and two bytes for score.

  arduboy.setCursor(16, 0);
  arduboy.print(F("HIGH SCORE"));
  arduboy.setCursor(88, 0);
  arduboy.print(Game.score);
  arduboy.setCursor(56, 20);
  arduboy.print(highScoreVars.initials[0]);
  arduboy.setCursor(64, 20);
  arduboy.print(highScoreVars.initials[1]);
  arduboy.setCursor(72, 20);
  arduboy.print(highScoreVars.initials[2]);

  for (byte i = 0; i < 3; i++) {
    arduboy.drawLine(56 + (i * 8), 27, 56 + (i * 8) + 6, 27, 1);
  }

  arduboy.drawLine(56, 28, 88, 28, 0);
  arduboy.drawLine(56 + (highScoreVars.index * 8), 28, 56 + (highScoreVars.index * 8) + 6, 28, 1);
  
  if (arduboy.justPressed(LEFT_BUTTON)) {
    if (highScoreVars.index > 0) highScoreVars.index--;
    else if (SoundOn) { /*arduboy.tunes.tone(1046, 250);*/
    }
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {

    highScoreVars.index++;
    if (highScoreVars.index > 2)
      highScoreVars.index = 2;
    else if (SoundOn) { /*arduboy.tunes.tone(1046, 250);*/
    }
  }
  if (arduboy.justPressed(UP_BUTTON)) {
    highScoreVars.initials[highScoreVars.index]++;
    if (SoundOn) { /*arduboy.tunes.tone(523, 250);*/
    }
    // A-Z 0-9 :-? !-/ ' '
    if (highScoreVars.initials[highScoreVars.index] == '0') highScoreVars.initials[highScoreVars.index] = ' ';
    if (highScoreVars.initials[highScoreVars.index] == '!') highScoreVars.initials[highScoreVars.index] = 'A';
    if (highScoreVars.initials[highScoreVars.index] == '[') highScoreVars.initials[highScoreVars.index] = '0';
    if (highScoreVars.initials[highScoreVars.index] == '@') highScoreVars.initials[highScoreVars.index] = '!';
  }
  if (arduboy.justPressed(DOWN_BUTTON)) {
    highScoreVars.initials[highScoreVars.index]--;
    if (SoundOn) { /* arduboy.tunes.tone(523, 250);*/
    }
    if (highScoreVars.initials[highScoreVars.index] == ' ') highScoreVars.initials[highScoreVars.index] = '?';
    if (highScoreVars.initials[highScoreVars.index] == '/') highScoreVars.initials[highScoreVars.index] = 'Z';
    if (highScoreVars.initials[highScoreVars.index] == 31) highScoreVars.initials[highScoreVars.index] = '/';
    if (highScoreVars.initials[highScoreVars.index] == '@') highScoreVars.initials[highScoreVars.index] = ' ';
  }
  if (arduboy.justPressed(A_BUTTON)) {

      // If on characters o or 1 move cursor right ..

    if (highScoreVars.index < 2) {
      highScoreVars.index++;
      if (SoundOn) { /*arduboy.tunes.tone(1046, 250);*/
      }
    } 
    else {

        // Shuffle existing slots down to make room for new enrtry ..

      uint8_t i = checkHighScoreSlot(Game.score);
        for (uint8_t j = 9; j > i; j--) {          
        
        for (uint8_t k = 0; k < 5; k++) {

            EEPROM.write(EEPROM_SCORES + (5 * j) + k, (char)EEPROM.read(EEPROM_SCORES + (5 * (j - 1)) + k));


      }
}

        // write score and initials to current slot
        EEPROM.put(EEPROM_SCORES + (5 * i), Game.score);
        EEPROM.update(EEPROM_SCORES + (5 * i) + 2, highScoreVars.initials[0]);
        EEPROM.update(EEPROM_SCORES + (5 * i) + 3, highScoreVars.initials[1]);
        EEPROM.update(EEPROM_SCORES + (5 * i) + 4, highScoreVars.initials[2]);

      highScoreVars.initials[0] = ' ';
      highScoreVars.initials[1] = ' ';
      highScoreVars.initials[2] = ' ';

      gameState = GameState::HighScore_DisplayAll;

      if (SoundOn) { /*arduboy.tunes.tone(1046, 250);*/
      }
      return;
    }
  }

}
void displayHighScores() {
  unsigned int Score;
  byte y = 10;
  byte x = 24;

  // Each block of EEPROM has 10 high scores, and each high score entry
  // is 5 bytes long:  3 bytes for initials and two bytes for score.


  arduboy.setCursor(32, 0);
  arduboy.print(F("HIGH SCORES"));
  for (int i = 0; i < 10; i++) {
    arduboy.setCursor(x, y + (i * 8));
    arduboy.print(i);
    EEPROM.get(EEPROM_SCORES + (5 * i), Score);


    if (Score > 0) {
      sprintf(highScoreVars.text, "%c%c%c %u", (char)EEPROM.read(EEPROM_SCORES + (5 * i) + 2),
              (char)EEPROM.read(EEPROM_SCORES + (5 * i) + 3),
              (char)EEPROM.read(EEPROM_SCORES + (5 * i) + 4), Score);
      arduboy.setCursor(x + 24, y + (i * 8));
      arduboy.print(highScoreVars.text);
    }
  }

  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      gameState = GameState::Title;
  }
}
