#include <SPI.h>
#include <EEPROM.h>

#include <Arduboy2.h>
#include "SquarioGame.h"
#include "DefinesImagesAndSounds.h"
#include "Enums.h"
#include "Structs.h"
#include "src/fonts/Font3x5.h"

Arduboy2 arduboy;
SquarioGame Game;

GameState gameState = GameState::Title;
bool SoundOn = false;
uint8_t RandomSeedSeed = 1;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  // arduboy.initRandomSeed(1);
  initEEPROM();
}


uint8_t SoundCounter = 0;
const byte *SFX = 0;
const unsigned int *SFXNoteSet;
int SFX_Counter = -1;
unsigned long duration = 0, lastNote = 0;


HighScoreVars highScoreVars;


void loop() {

    if (!arduboy.nextFrame()) return;
    arduboy.clear();
    arduboy.pollButtons();

// Serial.print(gameState);
// Serial.print(", ");
// Serial.println(Game.Event);

    switch (gameState) {

      case GameState::Title:
        TitleScreen();
        break;

      case GameState::Game_Init:
        Game.newGame();
        gameState = GameState::Game_Play;
        break;
        // [[fallthrough]]

      case GameState::Game_Play:
          SoundEngine();
          arduboy.clear();
          Game.cycle(arduboy, gameState);
          //if (Game.Event) Game.draw(display);
          Game.draw(arduboy);
          arduboy.setCursor(0,0);
          break;

      case GameState::HighScore_Check:
        if (checkHighScoreSlot(Game.score) != EEPROM_NO_SLOT) {
          highScoreVars.reset();
          gameState = GameState::HighScore_Enter;
          enterHighScore(); // repeated due to no fallthrough
        }
        else {
          gameState = GameState::HighScore_DisplayAll;
          displayHighScores(); // repeated due to no fallthrough
        }
        //[[fallthrough]]
        break;

      case GameState::HighScore_Enter:
        enterHighScore();
        break;        

      case GameState::HighScore_DisplayAll:
        displayHighScores();
        break;


    }

    arduboy.display();

}