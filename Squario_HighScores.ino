#include "src/utils/Arduboy2Ext.h"
#include <EEPROM.h>

void initEEPROM() {

    uint8_t c1 = EEPROM.read(Constants::EEPROM_Start_C1);
    uint8_t c2 = EEPROM.read(Constants::EEPROM_Start_C2);

    if (c1 != 'S' || c2 != 'Q') {

        EEPROM.update(Constants::EEPROM_Start_C1, 'S');
        EEPROM.update(Constants::EEPROM_Start_C2, 'Q');  

        uint16_t score = 30;
        uint8_t sounds = 1;

        EEPROM.put(Constants::EEPROM_Sounds, sounds);

        for (uint8_t i = 0; i < 5; i++) {
            EEPROM.update(Constants::EEPROM_Seeds + i, 0);
        }

        for (uint8_t i = 0; i < Constants::NumberOfScores; i++) {

            EEPROM.put(Constants::EEPROM_Scores + (5 * i), score = score - 10);
            EEPROM.update(Constants::EEPROM_Scores + (5 * i) + 2, 65 + i);
            EEPROM.update(Constants::EEPROM_Scores + (5 * i) + 3, 65 + i);
            EEPROM.update(Constants::EEPROM_Scores + (5 * i) + 4, 65 + i);

        }

    } 
   
}


// Returns the new slot the provided high score should occupy ..
uint8_t checkHighScoreSlot(uint16_t score) {

    uint16_t tmpScore = 0;

    for (uint8_t i = 0; i < Constants::NumberOfScores; i++) {

        EEPROM.get(Constants::EEPROM_Scores + (5 * i), tmpScore);

        if (tmpScore < score) {
            return i;
        }

    }

    return Constants::EEPROM_No_Slot;

}

void writeHighScoreEntry(HighScoreVars &highScoreVars) {


    // Move the scores down one ..

    for (uint8_t j = Constants::NumberOfScores - 1; j > highScoreVars.slot; j--) {          

        for (uint8_t k = 0; k < 5; k++) {

            EEPROM.write(Constants::EEPROM_Scores + (5 * j) + k, (char)EEPROM.read(Constants::EEPROM_Scores + (5 * (j - 1)) + k));

        }

    }


    // Write score and initials to the nominated slot ..

    EEPROM.put(Constants::EEPROM_Scores + (5 * highScoreVars.slot), game.totalScore);
    EEPROM.update(Constants::EEPROM_Scores + (5 * highScoreVars.slot) + 2, highScoreVars.initials[0]);
    EEPROM.update(Constants::EEPROM_Scores + (5 * highScoreVars.slot) + 3, highScoreVars.initials[1]);
    EEPROM.update(Constants::EEPROM_Scores + (5 * highScoreVars.slot) + 4, highScoreVars.initials[2]);

}

void highScores() {

    uint16_t score;



    // Render screen ..

    // Sprites::drawOverwrite(16, 4, Images::Title_Top, 0);
    Sprites::drawSelfMasked(35, 17, Images::Text_HighScores, 0);

    for (int i = 0; i < Constants::NumberOfScores; i++) {

        // If we are not editing this slot, the render it normally ..
        if (i != highScoreVars.slot) {

            EEPROM.get(Constants::EEPROM_Scores + (5 * i), score);

            font4x6.setCursor(33, 34 + (i * 9));
            font4x6.print((char)EEPROM.read(Constants::EEPROM_Scores + (5 * i) + 2));
            font4x6.print((char)EEPROM.read(Constants::EEPROM_Scores + (5 * i) + 3));
            font4x6.print((char)EEPROM.read(Constants::EEPROM_Scores + (5 * i) + 4));

        }
        else {

            // Render in edit mode ..

            score = game.totalScore;
            font4x6.setCursor(33, 34 + (i * 9));
            font4x6.print(highScoreVars.initials[0]);
            font4x6.setCursor(38, 34 + (i * 9));
            font4x6.print(highScoreVars.initials[1]);
            font4x6.setCursor(43, 34 + (i * 9));
            font4x6.print(highScoreVars.initials[2]);


            // Render edit bars top and bottom ..

            for (uint8_t j = 0; j < 3; j++) {

                if (j == highScoreVars.index && arduboy.getFrameCountHalf(32)) {
                    arduboy.drawFastHLine(33 + (j * 5), 33 + (i * 9), 4, WHITE);
                    arduboy.drawFastHLine(33 + (j * 5), 42 + (i * 9), 4, WHITE);
                }

            }

        }

        // Render score always ..

        uint8_t digits[6] = {};
        extractDigits(digits, score);

        font4x6.setCursor(64, 34 + (i * 9));
        
        for (uint8_t i = 0; i < 6; i++) {
            font4x6.print(static_cast<char>(digits[5 - i] + 48));
        }

    }

    arduboy.drawPixel(24, 62, WHITE);
    arduboy.drawPixel(102, 62, WHITE);
    arduboy.drawFastHLine(25, 63, 77);


    // Handle player input ..

    switch (gameState) {

        case GameState::HighScore_DisplayAll:

            if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
                gameState = GameState::Title;
            }

            break;

        case GameState::HighScore_Enter:

            if (arduboy.justPressed(LEFT_BUTTON)) {

                if (highScoreVars.index > 0) {
                    highScoreVars.index--;
                }
                else if (soundOn) { 
                    /*arduboy.tunes.tone(1046, 250);*/
                }

            }

            if (arduboy.justPressed(RIGHT_BUTTON)) {

                if (highScoreVars.index < 2) {
                    highScoreVars.index++;
                }
                else if (soundOn) { 
                    /*arduboy.tunes.tone(1046, 250);*/
                }

            }

            if (arduboy.justPressed(UP_BUTTON) || (arduboy.pressed(UP_BUTTON) && arduboy.getFrameCountHalf(4))) {

                if (arduboy.justPressed(UP_BUTTON)) { arduboy.resetFrameCount(); }
                highScoreVars.initials[highScoreVars.index]++;

                //A-Za-z0-9.!
                if (highScoreVars.initials[highScoreVars.index] == '[') highScoreVars.initials[highScoreVars.index] = 'a';
                if (highScoreVars.initials[highScoreVars.index] == '{') highScoreVars.initials[highScoreVars.index] = '0';
                if (highScoreVars.initials[highScoreVars.index] == ':') highScoreVars.initials[highScoreVars.index] = '.';
                if (highScoreVars.initials[highScoreVars.index] == '/') highScoreVars.initials[highScoreVars.index] = '!';
                if (highScoreVars.initials[highScoreVars.index] == '"') highScoreVars.initials[highScoreVars.index] = 'A';
            }

            if (arduboy.justPressed(DOWN_BUTTON) || (arduboy.pressed(DOWN_BUTTON) && arduboy.getFrameCountHalf(4))) {

                if (arduboy.justPressed(DOWN_BUTTON)) { arduboy.resetFrameCount(); }
                highScoreVars.initials[highScoreVars.index]--;

                if (highScoreVars.initials[highScoreVars.index] == '@') highScoreVars.initials[highScoreVars.index] = '!';
                if (highScoreVars.initials[highScoreVars.index] == ' ') highScoreVars.initials[highScoreVars.index] = '.';
                if (highScoreVars.initials[highScoreVars.index] == '-') highScoreVars.initials[highScoreVars.index] = '9';
                if (highScoreVars.initials[highScoreVars.index] == '/') highScoreVars.initials[highScoreVars.index] = 'z';
                if (highScoreVars.initials[highScoreVars.index] == '`') highScoreVars.initials[highScoreVars.index] = 'Z';
            }

            if (arduboy.justPressed(A_BUTTON)) {

                // If on characters 0 or 1 move cursor right ..

                if (highScoreVars.index < 2) {
                    highScoreVars.index++;
                } 
                else {

                    // write score and initials to current slot
                    EEPROM.put(Constants::EEPROM_Scores + (5 * highScoreVars.slot), game.totalScore);
                    EEPROM.update(Constants::EEPROM_Scores + (5 * highScoreVars.slot) + 2, highScoreVars.initials[0]);
                    EEPROM.update(Constants::EEPROM_Scores + (5 * highScoreVars.slot) + 3, highScoreVars.initials[1]);
                    EEPROM.update(Constants::EEPROM_Scores + (5 * highScoreVars.slot) + 4, highScoreVars.initials[2]);

                    highScoreVars.initials[0] = ' ';
                    highScoreVars.initials[1] = ' ';
                    highScoreVars.initials[2] = ' ';

                    gameState = GameState::HighScore_DisplayAll;
                    highScoreVars.reset();

                    if (soundOn) { 
                        /*arduboy.tunes.tone(1046, 250);*/
                    }
                    return;
                }

            }

            break;

        default: break;            

    }

}
