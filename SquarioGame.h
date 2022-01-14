#pragma once

#include <Arduboy2.h>
#include "src/images/Images.h"
#include "src/utils/Enums.h"
#include "src/utils/DefinesImagesAndSounds.h"


class Room;
class Map;
class Sprite;
class AISprite;
class SquarioGame;

class Sprite {

  public:
    void LoadSprite(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY);
    void ClearSprite();
    bool IsIn (int tX, int tY);
    bool IsInTopHalf (int tX, int tY);
    virtual bool GetPixelAbsolute(int tX, int tY);
    byte Collide(int tX, int tY);
    bool CollisionCheckX(Direction direction);
    bool CollisionCheckY(Direction direction);
    void headCollision();
    bool Falling();
    void Gravity();
    void Move();
    bool Jump();
    void duck();
    void draw(Arduboy2 &arduboy);
    
    uint8_t getWidth();
    uint8_t getHeight();
    uint8_t getMasks();
    uint8_t getMaxFrame();
    uint8_t getCyclesPerFrame();
    int16_t getRightX();
    int16_t getBottomY();

    byte getFlags();
    const uint8_t * FramePointer();
    const uint8_t * MaskPointer();

    SquarioGame         * Game;
    const uint8_t       * spriteData;
    const uint8_t       * spriteImg;
    const uint8_t       * spriteMask;
    int                   x, y, vx, vy;
    int                   currentFrame;
    bool                  Mirrored;

};

class AISprite : public Sprite {
  public:
    void Activate(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY);
    void Deactivate();
    void Think();
    void Seek();
    void DetectJump();
    void DetectWall();
    void DetectGap();
    
    uint8_t Speed();
    byte Intelligence();
    bool                  Active;

  private:
    Direction             facing;
};
class InteractiveObject {
  public:
    int x, y;
    byte type;
};
class Room {
  public:
    void ClearRoom();
    void SetTile(int x, int y);
    bool ReadTile(int x, int y);
    byte         data[ RoomBytes ];
};
class Map {
  public:
    void NewMap();
    void LoadMap();
    void generateRoom(int RoomNum);
    void addObject(byte type, int x, int y);
    void handleObject (int x, int y);
    void RemoveObject(int x, int y);
    byte CheckObject(int x, int y);
    bool CheckTile(int x, int y);
    void AddPipe(int x, int y);
    void AddTopPipe(int x, int y);

    int MinXPixel();
    int MaxXPixel();
    int MaxYPixel();
    int MinXTile();
    int MaxXTile();
    int MaxYTile();
    
    SquarioGame         * Game;
    Room                  rooms[MapRooms];
    InteractiveObject     objects[MapObjects];
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
    void drawMap(Arduboy2 &arduboy);
    void drawPlayer(Arduboy2 &arduboy);
    void drawMobs(Arduboy2 &arduboy);
    void addMob(const uint8_t *data, const uint8_t *sprite, const uint8_t *mask,  int x, int y);
    void adjustCamera();
    void processButtons(Arduboy2 &arduboy);
    
    Sprite                player;
    AISprite              mobs[ SpriteCap ];
    Map                   level;

    int                   health;
    unsigned int          origScore;
    unsigned int          score;
    unsigned int          distancePoints;
    int                   coins, lives, mapNumber;
    byte                  inventory;
    int                   cameraX, cameraY;
    EventType             event;
    int                   eventCounter;
    const byte *          SFX;
    byte                  Seeds[ GameSeeds ];
    unsigned long         lastPress;
};
