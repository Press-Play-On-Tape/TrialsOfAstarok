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
    void duck();
    void draw();
    
    uint8_t getWidth();
    uint8_t getHeight();
    int16_t getRightX();
    int16_t getBottomY();

    uint8_t getFlags();
    uint8_t getType();
    uint8_t getFrame();

    int                   x, y, vx, vy;
    int                   currentFrame;
    Direction             facing;
    SquarioGame         * Game;

  private:
    uint8_t               frame;


  protected:
    void clear();
    void applyGravity();
    byte collide(int tX, int tY);
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
    int x, y;
    byte type;
    SquarioGame         * Game;
  
    byte collide(int tX, int tY);
  
};

class Room {
  public:
    void clearRoom();
    void setTile(int x, int y);
    bool readTile(int x, int y);
    byte         data[ Constants::RoomBytes ];
};
class Map {
  public:
    void newMap();
    void loadMap();
    void generateRoom(int RoomNum);
    void addObject(byte type, int x, int y);
    void handleObject (int x, int y);
    byte checkObject(int x, int y);
    bool isTile(int x, int y);
    void addPipe(int x, int y);
    void addTopPipe(int x, int y);
    void addExit(ObjectTypes exitType, int x, int y);

    int MinXPixel();
    int MaxXPixel();
    int MaxYPixel();
    int MinXTile();
    int MaxXTile();
    int MaxYTile();
    
    SquarioGame         * Game;
    Room                  rooms[Constants::MapRooms];
    InteractiveObject     objects[Constants::MapObjects];
    int                   ObjectIndex;
    int                   RandomChance;
    int                   FirstRoom, LastRoom, MapHeight, LastLoadLocation, SpawnBarrier;
};

class SquarioGame {

  public:  // Constructor
    SquarioGame();

  public:  // Methods
    void newGame();
    void startLevel();
    uint8_t spawnY();
    void cycle(Arduboy2 &arduboy, GameState &gameState);
    bool testCollision(Arduboy2 &arduboy, Sprite * sprite1, AISprite * sprite2);
    void draw(Arduboy2 &arduboy);
    void die(Arduboy2 &arduboy, GameState &gameState);
    void drawScorePanel(Arduboy2 &arduboy, Font4x6 &font4x6);
    void drawMap_Background(Arduboy2 &arduboy);
    void drawMap_Foreground(Arduboy2 &arduboy);
    void drawHUD(Arduboy2 &arduboy);
    void drawPlayer(Arduboy2 &arduboy);
    void drawMobs();
    void addMob(const uint8_t *data, const uint8_t *sprite, const uint8_t *mask,  int x, int y);
    void adjustCamera();
    void processButtons(Arduboy2 &arduboy);
    
    Sprite                player;
    AISprite              mobs[ Constants::SpriteCap ];
    Map                   level;

    int16_t               health; //SJH needed?
    uint16_t              totalScore;
    uint16_t              score;
    uint16_t              distancePoints;
    int                   coins, lives, mapNumber;
    int16_t               cameraX, cameraY;
    EventType             event;
    uint8_t               eventCounter;
    const byte *          SFX;
    byte                  Seeds[ Constants::GameSeeds ];
    unsigned long         lastPress;
};
