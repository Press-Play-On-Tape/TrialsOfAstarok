#include "src/utils/Arduboy2Ext.h"
#include "Squariogame.h"


//---------------------------------------------------------------------------------------------------
// Sprite
//---------------------------------------------------------------------------------------------------
//
uint8_t Sprite::getFlags()      { return pgm_read_byte(this->spriteData + SpriteFlags); }
uint8_t Sprite::getType()       { return pgm_read_byte(this->spriteData + SpriteType); }

int16_t Sprite::getRightX()     { return this->x + this->getWidth() - 1; }
int16_t Sprite::getBottomY()    { return this->y + this->getHeight() - 1; }

uint8_t Sprite::getWidth()      { 
  #ifdef ORIG_GAME_TILESIZE_8
    return pgm_read_byte(&this->spriteImg[0]);
  #else
    if (this->getType() == ObjectTypes::STSquario) {
      return 12; 
    }
    else {
      return pgm_read_byte(&this->spriteImg[0]); 
    }
  #endif
}

uint8_t Sprite::getHeight()      { 
  #ifdef ORIG_GAME_TILESIZE_8
    return pgm_read_byte(&this->spriteImg[0]);
  #else
    if (this->getType() == ObjectTypes::STSquario) {
      return 12; 
    }
    else {
      return pgm_read_byte(&this->spriteImg[1]); 
    }
  #endif
}

void Sprite::init(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY) {
  this->spriteData = data;
  this->spriteImg = img;
  this->spriteMask = mask;
  this->x = tX; 
  this->y = tY;
  this->vx = 0; 
  this->vy = 0;
  this->currentFrame = 0;

  // Serial.print("init Type: ");
  // Serial.println(this->getType());
}

void Sprite::clear() {
  this->spriteData = NULL;
  this->x = -1;
  this->y = -1;
  this->vx = 0;
  this->vy = 0;
  this->currentFrame = 0;
}

byte Sprite::collide(int tX, int tY) {
  int nX = tX / Constants::TileSize;
  int nY = tY / Constants::TileSize;
  if (Game->level.isTile(nX, nY)) return 0xFF;
  return Game->level.checkObject(nX, nY);
}

bool Sprite::isFalling() {
  return !this->collisionCheckY(Direction::Down);
}

void Sprite::applyGravity() {
  if (vy < 6) vy++;
}

bool Sprite::collisionCheckX(Direction direction) {
  for (uint8_t tY = 0; tY < (this->getHeight() / Constants::TileSize); tY++) {
    switch (direction) {
      case Left:
        if (this->collide(x - 1, y + (tY * Constants::TileSize)) || this->collide(x - 1, y + ((tY + 1) * Constants::TileSize) - 1)) return true;
        break;
      case Right:
        if (this->collide(x + this->getWidth(), y+(tY * Constants::TileSize)) || this->collide(x + this->getWidth(), y + ((tY + 1) * Constants::TileSize) - 1)) return true;
        break;
      default: break;
    }
  }
  return false;
}

bool Sprite::collisionCheckY(Direction direction) {

  #ifdef DEBUG
  Serial.println("this->collisionCheckY() Start");
  #endif

  for (uint8_t tX = 0; tX < (this->getWidth() / Constants::TileSize); tX++) {
    switch (direction) {
      case Up:
        if (this->collide(x + (tX * Constants::TileSize), y - 1) || this->collide(x + ((tX + 1) * Constants::TileSize) - 1, y - 1)) {

            #ifdef DEBUG
            Serial.println("this->collisionCheckY() 1 = true End");
            #endif

            return true;
        }
        break;
      case Down:
        if (this->collide(x + (tX * Constants::TileSize), y + this->getHeight()) || this->collide(x + ((tX + 1) * Constants::TileSize) - 1, y + this->getHeight())) {

            #ifdef DEBUG
            Serial.println("this->collisionCheckY() 2 = true End");
            #endif

            return true;
        }
        break;
      default: break;
    }
  }

  #ifdef DEBUG
  Serial.println("this->collisionCheckY() = false End");
  #endif

  return false;
}

void Sprite::move() {
  if (this->getFlags() & 1) {
    x += vx;
    y += vy;
    return;
  }
  if (vy == 0) { // Start fall
    if (isFalling()) applyGravity();
  }
  if (vy > 0) { // Down
    for (int a = 0; a < vy; a++) {
      if (isFalling()) {
        // if (this->getType() == ObjectTypes::STTriangleo) {
        // }
        y++;
      }
      else { 
        vy = 0; 
        break; 
      }
    }

    if (isFalling()) {
      applyGravity();
    }
  }
  if (vy < 0) { // Up
    applyGravity();
    for (int a = 0; a > vy; a--) {
      if (this->collisionCheckY(Direction::Up)) { headCollision(); vy = 0; break; }
      else {
        y--;
      }
    }
  }
  if (vx > 0) { // Right
    for (int a = 0; a < vx; a++){
    if (this->getRightX() > Game->level.MaxXPixel()) break;
      if (this->collisionCheckX(Direction::Right)) break;
      else { 
        this->x++;
        if (this->getType() == ObjectTypes::STSquario) {
// Serial.print("vy=");
// Serial.println(vy);
        }
        if (vy == 0 && !isFalling()) {
          this->frame = (this->frame + 1) % 4;
        }
      }
    }
  }
  if (vx < 0) { // Left
    for (int a = 0; a > vx; a--){
      if (x < Game->level.MinXPixel() + 1) break;
      if (this->collisionCheckX(Direction::Left)) break;
      else {
        x--;
        if (vy == 0 && !isFalling()) {
          this->frame = (this->frame + 1) % 4;
        }
      }
    }
  }
}

bool Sprite::jump() {

  #ifdef ORIG_GAME_TILESIZE_8
    if (this->collisionCheckY(Direction::Down)) { vy = -8; return true; }
  #else
    if (this->collisionCheckY(Direction::Down)) { vy = -10; return true; }
  #endif
  return false;
}

void Sprite::duck() {
  if (x < 64) return;
  if (this->collide(x, y + this->getHeight() + 1) == STPipeCapLeft && this->collide(this->getRightX(), y + this->getHeight() + 1) == STPipeCapRight) {
    Game->SFX = Sounds::SFX_Pipe;
    Game->event = EventType::PipeDrop;
    Game->eventCounter = 0;
  }
}

void Sprite::headCollision() {

  if (this->getFlags() & 0b10) return;

  if (this->collide(x, y - 1) == STTopPipeCapLeft && this->collide(this->getRightX(), y - 1) == STTopPipeCapRight) {
    if (x < 64) return;
    Game->SFX = Sounds::SFX_Pipe;
    Game->event = EventType::PipeRise;
    Game->eventCounter = 0;
  }

  byte LeftCheck = this->collide(x, y - 1);
  byte RightCheck = this->collide(this->getRightX(), y - 1);

  if (LeftCheck == STQBlock || LeftCheck == STMushBlock) {
    Game->level.handleObject(x / Constants::TileSize, (y - 1) / Constants::TileSize);
  }
  if (RightCheck == STQBlock || RightCheck == STMushBlock) {
    Game->level.handleObject(this->getRightX() / Constants::TileSize, (y - 1) / Constants::TileSize);
  }
  
}

void Sprite::draw() {

  #ifdef ORIG_GAME_TILESIZE_8
    Sprites::drawExternalMask(x - Game->cameraX, y - Game->cameraY, this->spriteImg, this->spriteMask, 0, 0);
  #else
    if (this->getType() == ObjectTypes::STSquario) {

// Serial.print("Render ObjectTypes::STSquario ");
// Serial.print(y);
// Serial.print(" ");
// Serial.print(this->getHeight() - 8);
// Serial.print(" ");
// Serial.print(Game->cameraY);
// Serial.print(" = ");
// Serial.print(y - (this->getHeight() - 8) - Game->cameraY);
// Serial.print(", frame = ");
// Serial.println(this->getFrame());

      // Sprites::drawExternalMask(x - Game->cameraX, y - (this->getHeight() - 8) - Game->cameraY, Images::Player_Walking_00, Images::Player_Walking_00_Mask, 0, 0);
      Sprites::drawExternalMask(x - Game->cameraX, y - 1 - Game->cameraY, pgm_read_word_near(&Images::Player_Images[this->getFrame()]), pgm_read_word_near(&Images::Player_Masks[this->getFrame()]), this->facing == Direction::Right, this->facing == Direction::Right);
    }
    else {
// Serial.print("Image:");
// Serial.print(this->getType());
// Serial.print(", x:");
// Serial.print(x - Game->cameraX);
// Serial.print(", y:");
// Serial.print(y - (getHeight() - 8) - Game->cameraY);
// Serial.println("");

      if (this->Game->mapNumber % 2 == MapLevel::AboveGround) {
//        Sprites::drawErase(x - Game->cameraX, y - (this->getHeight() - 8) - Game->cameraY, this->spriteImg, 0);
        Sprites::drawErase(x - Game->cameraX, y -  Game->cameraY, this->spriteImg, 0);
      }
      else {
        Sprites::drawExternalMask(x - Game->cameraX, y - Game->cameraY, this->spriteImg, this->spriteMask, 0, 0);
      }
    }
  #endif

}

uint8_t Sprite::getFrame() {

  return this->frame;

}

//---------------------------------------------------------------------------------------------------
// AISprite
//---------------------------------------------------------------------------------------------------
//
uint8_t AISprite::getSpeed()        { return pgm_read_byte(this->spriteData + SpriteSpeed); }
uint8_t AISprite::getIntelligence() { return pgm_read_byte(this->spriteData + SpriteIntelligence); }

void AISprite::activate(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY) {
// Serial.println("activate");
  this->active = true;
  this->facing = Direction::Left;
  init(data, img, mask, tX * Constants::TileSize, tY * Constants::TileSize);
  if (data == Images::SpriteImages[ObjectTypes::STBolt]) {
    vx = -4;
    vy = 2;
  }
  this->think();
}

void AISprite::deactivate() {
  // Serial.println("Deactivate");
  this->spriteData = NULL;
  this->active = false;
  this->facing = Direction::Up;
  this->clear();
}

bool AISprite::getActive() {
  return this->active;
}

void AISprite::think() {
  if   (this->getIntelligence() & 0b00000100) {
    this->seek();
    if (this->getIntelligence() & 0b00001000) this->detectJump();
  }
  else {
    if (this->getIntelligence() & 0b00000001) this->detectWall();
    if (this->getIntelligence() & 0b00000010) this->detectGap();
  }
  move();
}

void AISprite::seek() {
  if (Game->player.x + Game->player.getWidth() < x) {
    this->facing = Direction::Left;
    vx = this->getSpeed() * -1;
  }
  if (Game->player.x > x + this->getWidth()) {
    this->facing = Direction::Right;
    vx = this->getSpeed();
  }
}

void AISprite::detectJump() {

  if (this->collisionCheckX(this->facing)) jump();
  if (this->facing == Direction::Left) {
    if (!this->collide(x - 1, (Constants::RoomHeight * Constants::TileSize) - 1)) jump();
  }
  if (this->facing == Direction::Right) {
    if (!this->collide(this->getRightX() + 1, (Constants::RoomHeight * Constants::TileSize) - 1)) jump();
  }

}

void AISprite::detectWall() {
  if (this->facing == Direction::Left) {
    if (this->collisionCheckX(Direction::Left)) { this->facing = Direction::Right; vx = 0; return; }
    else vx = this->getSpeed() * -1;
  }
  if (this->facing == Direction::Right) {
    if (this->collisionCheckX(Direction::Right)) { this->facing = Direction::Left; vx = 0; return; }
    else vx = this->getSpeed();
  }
}

void AISprite::detectGap() {
  if (this->facing == Direction::Left) {
    if (!this->collide(x-1, this->getBottomY() + 1)) { this->facing = Direction::Right; vx = 0; return; }
    else vx = this->getSpeed() * -1;
  }
  if (this->facing == Direction::Right) {
    if (!this->collide(this->getRightX()+1, this->getBottomY() + 1)) { this->facing = Direction::Left; vx = 0; return; }
    else vx = this->getSpeed();
  }
}


//---------------------------------------------------------------------------------------------------
// InteractiveObject
//---------------------------------------------------------------------------------------------------
//
byte InteractiveObject::collide(int tX, int tY) {
  int16_t nX = tX / Constants::TileSize;
  int16_t nY = tY / Constants::TileSize;
  if (Game->level.isTile(nX, nY)) {
    // Serial.print("Game->level.isTile(nX, nY) ");
    // Serial.println(Game->level.isTile(nX, nY));
    return 0xFF;
  }
  // Serial.print("Game->level.checkObject(nX, nY) ");
  // Serial.println(Game->level.checkObject(nX, nY));
  return Game->level.checkObject(nX, nY);
}

//---------------------------------------------------------------------------------------------------
// Room
//---------------------------------------------------------------------------------------------------
//
void Room::clearRoom() {
  for (int a = 0; a < Constants::RoomBytes; a++) data[a] = 0;
}

void Room::setTile(int x, int y) {

  if (x > Constants::RoomWidth || y > Constants::RoomHeight) return;

  int index = (Constants::RoomHeight/8) * x;
  if (y < 8) data[index]     |= 1 << y;
  else       data[index + 1] |= 1 << (y - 8);
}

bool Room::readTile(int x, int y) {
  if (x > Constants::RoomWidth || y > Constants::RoomHeight) return false;
  int Index = (Constants::RoomHeight/8) * x;
  if (y < 8) {
    byte Mask = 1 << y;
    if (data[ Index ] & Mask) return true;
  }
  else {
    byte Mask = 1 << (y - 8);
    if (data[ Index+1 ] & Mask) return true;
  }
  return false;
}


//---------------------------------------------------------------------------------------------------
// Map
//---------------------------------------------------------------------------------------------------
//
void Map::generateRoom(int roomNum) {
// Serial.print("generateRoom(");
// Serial.print(roomNum);
// Serial.println(") Start");
  randomSeed(Game->Seeds[ (Game->mapNumber + roomNum) % Constants::GameSeeds ] * Game->mapNumber + roomNum);
  rooms[roomNum%Constants::MapRooms].clearRoom();
  uint8_t floor = random(Constants::RoomHeight-3,Constants::RoomHeight);

  #ifdef ORIG_GAME_CEILING
  uint8_t ceiling = (!(Game->mapNumber % 2)) ? 8 : 0;
  #endif

  int Gap = 0;
  int tSpawnBarrier = roomNum * Constants::RoomWidth;

  if (roomNum == 0) {
    #ifdef ORIG_GAME_CEILING
    if (ceiling) addTopPipe(1, ceiling + 1);
    else addPipe(1, floor - 2);
    #else
    addPipe(1, floor - 2);
    #endif
  }
  for (int x = 0; x < Constants::RoomWidth; x++) {
// Serial.print("generateRoom() 1 -");
// Serial.print(x);
// Serial.print(" of ");
// Serial.println(Constants::RoomWidth);
    #ifdef ORIG_GAME_CEILING
    if (ceiling) rooms[roomNum % Constants::MapRooms].setTile(x, ceiling);
    #endif
    if (!Gap) {
      for (int b = floor; b < Constants::RoomHeight; b++) {
        rooms[roomNum % Constants::MapRooms].setTile(x, b);
      }
      if (roomNum && (roomNum < LastRoom)) {
// Serial.println("generateRoom() 2");
        if (!random(10)) { 
          Gap = random(2,5);
          #ifdef ORIG_GAME_CEILING
          if (ceiling) Gap--;
          #endif
        }
        else if (!random(5) ) {
          if (!random(1) && floor < Constants::RoomHeight - 1) floor++;
          else floor--;
        }

        if (tSpawnBarrier > SpawnBarrier) {
// Serial.println("generateRoom() 3");

          if (!random(8)) {
// Serial.println("generateRoom() 4.1");
                // Game->addMob(Data::Triangleo, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, floor - 2);


            switch (random(20)) {

              case 0 ... 9:
// Serial.println("generateRoom() 4.1");
                Game->addMob(Data::Triangleo, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, floor - 2);
                break;

              case 10 ... 15:
// Serial.println("generateRoom() 4.2");
                Game->addMob(Data::Smileo, Images::SpriteImages[ObjectTypes::STSmileo], Images::SpriteMasks[ObjectTypes::STSmileo], tSpawnBarrier + x, floor - 2);
                break;

              case 16 ... 18:
                if (roomNum > 8) {
// Serial.println("generateRoom() 4.3");
                  Game->addMob(Data::Starmano, Images::SpriteImages[ObjectTypes::STStarmano], Images::SpriteMasks[ObjectTypes::STStarmano], tSpawnBarrier + x, floor - 2);
                }
                break;

              default:
                if (roomNum > 8) {
// Serial.println("generateRoom() 4.4");
                  Game->addMob(Data::Bolt, Images::SpriteImages[ObjectTypes::STBolt], Images::SpriteMasks[ObjectTypes::STBolt], tSpawnBarrier + x, 2);
                }
                break;

            }

          }

          #ifdef ORIG_GAME_MUSHROOM
          if (!random(16) && !Gap && floor > ceiling + 5 && x != Constants::RoomWidth - 1) {

            int y = random(max(floor - 7, ceiling + 2), floor - 3);

            if (!random(4)) {
              addObject (STMushBlock, tSpawnBarrier + x, y);
            }
            else {
              addObject(STQBlock, tSpawnBarrier + x, y);
            }

          }
          #endif

        }

      }

    }
    else Gap--;

// Serial.println("generateRoom() End");

  }


  // If this is the last room in a map, then add a pipe so we can leave ..

  if (roomNum == LastRoom) {
    #ifdef ORIG_GAME_CEILING
    if (ceiling) {
      addTopPipe (MaxXTile() - 2, ceiling + 1);
    }
    else {
      addPipe(MaxXTile() - 2, floor - 2);
    }
    #else
    
    addExit(this->Game->mapNumber % 2 == MapLevel::AboveGround ? ObjectTypes::STAboveGroundExit : ObjectTypes::STUnderGroundExit, MaxXTile() - 2, floor - 1);

    #endif
  }
  
  if (tSpawnBarrier > SpawnBarrier) SpawnBarrier = tSpawnBarrier;

}

void Map::addExit(ObjectTypes exitType, int x, int y) {

  addObject(exitType, x, y);

}

void Map::addPipe(int x, int y) {

  addObject(STPipeCapLeft,  x,   y);
  addObject(STPipeCapRight, x+1, y);

  for (uint8_t a = y+1; a < Constants::RoomHeight; a++) {
    addObject(STPipeLeft,     x,   a);
    addObject(STPipeRight,    x+1, a);
  }

}

void Map::addTopPipe(int x, int y) {

  addObject(STTopPipeCapLeft,  x,   y + 1);
  addObject(STTopPipeCapRight, x+1, y + 1);
  addObject(STPipeLeft,     x,   y);
  addObject(STPipeRight,    x+1, y);

}

void Map::addObject(byte type, int tX, int tY) {

  if (checkObject(tX, tY)) {
    return;
  }
  else {
   
    objects[ObjectIndex].x = tX;
    objects[ObjectIndex].y = tY;
    objects[ObjectIndex].type = type;
    ObjectIndex++;

    if (ObjectIndex == Constants::MapObjects) ObjectIndex = 0;

  }

}

void Map::handleObject(int x, int y) {
  for (int a = 0; a < Constants::MapObjects; a++) {
    if (objects[a].x == x && objects[a].y == y) {
      switch (objects[a].type) {
        case STQBlock: 
          Game->coins++;
          if (!(Game->coins % 20)) {
            Game->lives++;
            Game->SFX = Sounds::SFX_Life;
          }
          else Game->SFX = Sounds::SFX_Coin;
          objects[a].type = STBQBlock;
          break;
        case STMushBlock:
          Game->addMob(Data::Mushroom, Images::SpriteImages[ObjectTypes::STMushroom], Images::SpriteMasks[ObjectTypes::STMushroom], x, y - 1);
          objects[a].type = STBQBlock; break;
      }
    }
  }
}


void Map::newMap() {
// Serial.println("newMap() Start");  
  // Reset Variables
  ObjectIndex = 0; LastLoadLocation = 0; FirstRoom = 0; SpawnBarrier = 0;
  for (uint8_t a = 0; a < Constants::MapObjects; a++) objects[a].y = -1;
  for (uint8_t a = 0; a < Constants::SpriteCap; a++) Game->mobs[a].deactivate();

  // Seed for level length
  randomSeed(Game->Seeds[ Game->mapNumber % Constants::GameSeeds ] * Game->mapNumber);
  int LowEnd = Constants::MinLevelWidth + random(Game->mapNumber);
  int HighEnd = random(LowEnd, LowEnd + Game->mapNumber);
  LastRoom = random(LowEnd, HighEnd);

  for (uint8_t a = 0; a < Constants::MapRooms; a++) {
    generateRoom(a);
  }
// Serial.println("newMap() End");
}

void Map::loadMap() {
  int RoomBeforePlayerIsIn = (Game->player.x / (Constants::RoomWidth*Constants::TileSize)) - 1;
  if (RoomBeforePlayerIsIn < 0) RoomBeforePlayerIsIn = 0;
  if (RoomBeforePlayerIsIn > FirstRoom) {
    FirstRoom = RoomBeforePlayerIsIn;
    generateRoom(RoomBeforePlayerIsIn + Constants::MapRooms - 1);
  }
}

bool Map::isTile(int x, int y) {
  int room = (x / Constants::RoomWidth) % Constants::MapRooms;

  #ifdef DEBUG
  // Serial.print("isTile(");
  // Serial.print(x);
  // Serial.print(",");
  // Serial.print(y);
  // Serial.print(") room = ");
  // Serial.print(room);
  // Serial.print(", tile = ");
  // Serial.println(rooms[room].readTile(x % Constants::RoomWidth, y));
  #endif

  return rooms[room].readTile(x % Constants::RoomWidth, y);
}

byte Map::checkObject(int x, int y) {
  if (y < 0) return 0;
  for (int a = 0; a < Constants::MapObjects; a++) {
    if ((objects[a].x == x) && (objects[a].y == y)) return objects[a].type;
  }
  return 0;
}

int Map::MinXPixel() { return FirstRoom * Constants::RoomWidth * Constants::TileSize; }
int Map::MaxXPixel() { return ((LastRoom + 1) * Constants::RoomWidth * Constants::TileSize) - 1; }
int Map::MaxYPixel() { return ((MapHeight + 1) * Constants::RoomHeight * Constants::TileSize) - 1; }
int Map::MinXTile() { return FirstRoom * Constants::RoomWidth; }
int Map::MaxXTile() { return ((LastRoom + 1) * Constants::RoomWidth) - 1; }
int Map::MaxYTile() { return ((MapHeight + 1) * Constants::RoomHeight) - 1; }
