#pragma once

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

class SquarioGame {

    public:  // Constructor
        SquarioGame(Arduboy2Ext *arduboy);

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
        const uint8_t *       SFX;

        Sprite                player;
        AISprite              mobs[Constants::SpriteCap];
        Map                   level;
        Arduboy2Ext           * arduboy;

    public:  // Methods
        void newGame();
        void cycle(GameState &gameState);
        void draw();
        void addMob(const uint8_t *data, const uint8_t *sprite, const uint8_t *mask,  int x, int y);
        uint8_t getSpareMobCount();
        void drawScorePanel(Font4x6 &font4x6);

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
