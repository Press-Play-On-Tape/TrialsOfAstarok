#pragma once

#include "src/utils/Arduboy2Ext.h"
#include "src/data/SpriteData.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"
#include "src/utils/Enums.h"
#include "src/utils/Constants.h"
#include "src/utils/Utils.h"
#include "src/fonts/Font4x6.h"


class Room;
class Map;
class Sprite;
class AISprite;
class SquarioGame;

#include "src/entities/Sprite.h"
#include "src/entities/AISprite.h"
#include "src/entities/InteractiveObject.h"
#include "src/entities/Room.h"
#include "src/entities/Map.h"
/*
class Sprite {

    protected:
        const uint8_t       * spriteData;
        const uint8_t       * spriteImg;
        const uint8_t       * spriteMask;

    public:

        void init(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY);
        bool isFalling();
        void move();
        bool jump();
        void draw();

        uint8_t getWidth();
        uint8_t getHeight();
        int16_t getRightX();
        int16_t getBottomY();

        uint8_t getFlags();
        uint8_t getType();
        uint8_t getFrame();

        int16_t               x, y, vx, vy, xInit, yInit;
        int16_t               currentFrame;
        Direction             facing;
        SquarioGame           * game;
        Sprite                * relatedSprite;
        Arduboy2Ext           * arduboy;

    private:
        uint8_t               frame;

    protected:
        void clear();
        void applyGravity();
        uint8_t collide(int16_t tX, int16_t tY);
        bool collisionCheckX(Direction direction);
        bool collisionCheckY(Direction direction);
        void headCollision();

};

class AISprite : public Sprite {

    private:
        bool  active;

    private:
        void seek();
        void detectJump();
        void detectWall();
        void detectGap();
        uint8_t getSpeed();
        uint8_t getIntelligence();

    public:
        void activate(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY);
        void deactivate();
        void think();
        bool getActive();

};

class InteractiveObject {

    public:
        int16_t             x, y;
        uint8_t             type;
        SquarioGame         * game;
        Arduboy2Ext         * arduboy;

        uint8_t collide(int16_t tX, int16_t tY);
        void deactivate();
};

class Room {

    public:
        void clearRoom();
        void setTile(int x, int y);
        void clearTile(int x, int y);
        bool readTile(int x, int y);

        uint8_t data[ Constants::RoomBytes ];

};

class Map {

    public:
        void newMap();
        void loadMap();
        void generateRoom(uint8_t roomNum);
        void addObject(uint8_t type, int x, int y);
        void handleObject (int x, int y);
        byte checkObject(int x, int y);
        bool isTile(int x, int y);
        void addSign(int x, int y);
        void addExit(ObjectTypes exitType, int x, int y);

        int16_t minXPixel();
        int16_t maxXPixel();
        int16_t maxYPixel();
        int16_t minXTile();
        int16_t maxXTile();
        int16_t maxYTile();

        SquarioGame           * game;
        Room                  rooms[Constants::MapRooms];
        InteractiveObject     objects[Constants::MapObjects];
        int16_t               ObjectIndex;
        int16_t               RandomChance;
        int16_t               firstRoom, lastRoom, mapHeight, lastLoadLocation, SpawnBarrier;
};
*/
class SquarioGame {

    public:  // Constructor
        SquarioGame(Arduboy2Ext *arduboy);

    public:  // Variables
        int16_t               health; //SJH needed?
        EventType             event;
        uint8_t               eventCounter;
        byte                  Seeds[ Constants::GameSeeds ];
        uint16_t              coins;
        uint8_t               lives;
        uint16_t              totalScore;
        uint16_t              score;
        uint16_t              distancePoints;
        uint16_t              mapNumber;
        int16_t               cameraX, cameraY;
        const uint8_t *       SFX;

        Sprite                player;
        AISprite              mobs[ Constants::SpriteCap ];
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
        bool testCollision(Sprite * sprite1, AISprite * sprite2);
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
