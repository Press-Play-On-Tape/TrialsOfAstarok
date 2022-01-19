#include <EEPROM.h>
#include <SPI.h>

#include "Squariogame.h"
#include "src/fonts/Font4x6.h"
#include "src/images/Images.h"
#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"

Arduboy2Ext arduboy;
SquarioGame game;
Font4x6 font4x6;

GameState gameState = GameState::Title;
bool SoundOn = false;

uint8_t SoundCounter = 0;
const byte *SFX = 0;
const unsigned int *SFXNoteSet;
int SFX_Counter = -1;
unsigned long duration = 0, lastNote = 0;

HighScoreVars highScoreVars;
SeedVars seedVars;

void setup() {

    arduboy.boot();
    arduboy.setFrameRate(30);
    initEEPROM();

}

void loop() {

    if (!arduboy.nextFrame()) return;
    arduboy.pollButtons();

    switch (gameState) {

        case GameState::Title:

            TitleScreen();
            arduboy.display(true);
            break;

        case GameState::Seed_Init:

            seed_Init();
            seed();
            arduboy.display(true);
            break;

        case GameState::Seed:

            seed();
            arduboy.display(true);
            break;

        case GameState::Game_Init:

            game.newGame();
            gameState = GameState::Game_Play;
            break;

        case GameState::Game_Play:

            // SoundEngine();
            //  Serial.println("Cycle");
            game.cycle(arduboy, gameState);
            // if (game.Event) game.draw(display);
            //  Serial.println("draw");
            game.draw(arduboy);

            if (game.event == EventType::Death) {
                game.drawScorePanel(arduboy, font4x6);
            }

            arduboy.displayWithBackground(game.mapNumber % 2 ? MapLevel::AboveGround : MapLevel::BelowGround);
            break;

        case GameState::HighScore_Check:

            highScoreVars.reset();
            highScoreVars.slot = checkHighScoreSlot(game.totalScore);

            if (highScoreVars.slot != Constants::EEPROM_No_Slot) {
                writeHighScoreEntry(highScoreVars);
                gameState = GameState::HighScore_Enter;
            } 
            else {
                gameState = GameState::HighScore_DisplayAll;
            }

            highScores();
            arduboy.display(true);
            break;

        case GameState::HighScore_Enter:
        case GameState::HighScore_DisplayAll:

            highScores();
            arduboy.display(true);
            break;

    }

}