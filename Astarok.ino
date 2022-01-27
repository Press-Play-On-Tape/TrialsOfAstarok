#include <EEPROM.h>
#include <SPI.h>

#include "AstarokGame.h"
#include "src/images/Images.h"
#include "src/utils/Arduboy2Ext.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include <ArduboyTones.h>

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);
AstarokGame game(&arduboy, &sound);
GameState gameState = GameState::Title_Init;

TitleScreenVars titleScreenVars;
HighScoreVars highScoreVars;
SeedVars seedVars;

#ifndef DEBUG
    ARDUBOY_NO_USB 
#endif

void setup() {

    arduboy.boot();
    arduboy.setFrameRate(30);
	arduboy.flashlight();
	arduboy.systemButtons();

    #ifndef DEBUG
    arduboy.audio.begin();
    #endif

    initEEPROM(false);

}

void loop() {

    if (!arduboy.nextFrame()) return;
    arduboy.pollButtons();

    switch (gameState) {

        case GameState::Title_Init:

            sound.tones(Sounds::Theme);
            gameState = GameState::Title;
            [[Fallthrough]]

        case GameState::Title:

            titleScreen();
            arduboy.display(true);
            break;

        case GameState::Seed_Init:

            seed_Init();
            [[Fallthrough]]

        case GameState::Seed:

            seed();
            arduboy.display(true);
            break;

        case GameState::Game_Init:

            game.newGame();
            gameState = GameState::Game_Play;
            [[Fallthrough]]

        case GameState::Game_Play:

            // SoundEngine();
            game.cycle(gameState);
            game.draw();

            if (game.event == EventType::Death) {
                game.drawScorePanel();
            }

            arduboy.displayWithBackground(game.mapNumber % 2 ? MapLevel::AboveGround : MapLevel::BelowGround);
            break;

        case GameState::Game_Mini:

            game.draw();
            game.playMiniGame(gameState);
            arduboy.displayWithBackground(game.mapNumber % 2 ? MapLevel::AboveGround : MapLevel::BelowGround);
            break;

        case GameState::HighScore_Check:

            highScoreVars.reset();
            checkHighScoreSlot(game.totalScore);

            if (highScoreVars.slot != Constants::EEPROM_No_Slot) {
                game.arduboy->resetFrameCount();
                gameState = GameState::HighScore_Flash;
            } 
            else {
                gameState = GameState::HighScore_NoFlash;
            }

            highScores();
            arduboy.display(true);
            break;

        case GameState::HighScore_Flash:
        case GameState::HighScore_NoFlash:

            highScores();
            arduboy.display(true);
            break;

    }

}