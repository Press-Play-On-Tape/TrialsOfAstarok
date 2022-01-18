#include <SPI.h>
#include <EEPROM.h>

#include "src/utils/Arduboy2Ext.h"
#include "src/images/Images.h"
#include "src/utils/Constants.h"
#include "SquarioGame.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"

Arduboy2Ext arduboy;
SquarioGame Game;

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

  arduboy.begin();
  arduboy.setFrameRate(30);
  initEEPROM();

}

void loop() {

    if (!arduboy.nextFrame()) return;
    arduboy.pollButtons();

// Serial.print(gameState);
// Serial.print(", ");
// Serial.println(Game.Event);

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
        // Serial.println("Game_Init 1");
        Game.newGame();
        gameState = GameState::Game_Play;
        // Serial.println("Game_Init 2");
        break;
        // [[fallthrough]]

      case GameState::Game_Play:
          //SoundEngine();
          // Serial.println("Cycle");
          Game.cycle(arduboy, gameState);
          //if (Game.Event) Game.draw(display);
          // Serial.println("draw");
          Game.draw(arduboy);

          if (Game.event == EventType::Death) {
            Game.drawScorePanel(arduboy);
          }

          arduboy.displayWithBackground(Game.mapNumber % 2 ? MapLevel::AboveGround : MapLevel::BelowGround);
          // arduboy.display(true);
          break;

      case GameState::HighScore_Check:
        if (checkHighScoreSlot(Game.score) != Constants::EEPROM_No_Slot) {
          highScoreVars.reset();
          gameState = GameState::HighScore_Enter;
          enterHighScore(); // repeated due to no fallthrough
        }
        else {
          gameState = GameState::HighScore_DisplayAll;
          displayHighScores(); // repeated due to no fallthrough
        }
        arduboy.display(true);
        //[[fallthrough]]
        break;

      case GameState::HighScore_Enter:
        enterHighScore();
        arduboy.display(true);
        break;        

      case GameState::HighScore_DisplayAll:
        displayHighScores();
        arduboy.display(true);
        break;


    }


}