#pragma once

#include <ArduboyTones.h>
#include "src/utils/Arduboy2Ext.h"
#include "src/data/SpriteData.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"
#include "src/utils/Enums.h"
#include "src/utils/Constants.h"
#include "src/utils/Utils.h"
#include "src/fonts/Font4x6.h"

#include "src/entities/Sprite.h"
#include "src/entities/AISprite.h"
#include "src/entities/InteractiveObject.h"
#include "src/entities/Room.h"
#include "src/entities/Map.h"

class AstarokGame {

    public:  // Constructor
        AstarokGame(Arduboy2Ext *arduboy, ArduboyTones *sound);

    public:  // Variables
        EventType             event;
        uint8_t               eventCounter;
        byte                  seeds[Constants::GameSeeds];
        uint16_t              coins;
        uint8_t               lives;
        uint16_t              totalScore;
        uint16_t              score;
        uint16_t              distancePoints;
        uint16_t              mapNumber;
        Point                 camera;

        Sprite                player;
        AISprite              mobs[Constants::SpriteCap];
        Map                   level;
        Arduboy2Ext           * arduboy;
        ArduboyTones          * sound;

    public:  // Methods
        void newGame();
        void cycle(GameState &gameState);
        void draw();
        void addMob(const uint8_t *data, const uint8_t *sprite, const uint8_t *mask, int16_t x, uint8_t y, uint8_t maxHeight = 255);
        uint8_t getSpareMobCount();
        void drawScorePanel();

    private:  // Methods
        void startLevel();
        bool testCollision(Sprite * player, AISprite * sprite);
        void die(GameState &gameState);
        void drawMap_Background();
        void drawMap_Foreground();
        void drawHUD();
        void drawPlayer();
        void drawMobs();
        void adjustCamera();
        void processButtons();
        uint8_t spawnY();

};