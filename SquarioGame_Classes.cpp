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

uint8_t Sprite::getWidth() { 

    if (this->getType() == ObjectTypes::STSquario) {
        return 12; 
    }
    else {
        return pgm_read_byte(&this->spriteImg[0]); 
    }

}

uint8_t Sprite::getHeight() { 

    if (this->getType() == ObjectTypes::STSquario) {
        return 12; 
    }
    else {
        return pgm_read_byte(&this->spriteImg[1]); 
    }

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
    this->facing = Direction::Right;

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

  if (this->collisionCheckY(Direction::Down)) { vy = -10; return true; }
  return false;

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

    if (this->getType() == ObjectTypes::STSquario) {
      Sprites::drawExternalMask(x - Game->cameraX, y - 1 - Game->cameraY, pgm_read_word_near(&Images::Player_Images[this->getFrame()]), pgm_read_word_near(&Images::Player_Masks[this->getFrame()]), this->facing == Direction::Right, this->facing == Direction::Right);
    }
    else {

      if (this->Game->mapNumber % 2 == MapLevel::AboveGround) {
        Sprites::drawErase(x - Game->cameraX, y -  Game->cameraY, this->spriteImg, 0);
      }
      else {
        Sprites::drawExternalMask(x - Game->cameraX, y - Game->cameraY, this->spriteImg, this->spriteMask, 0, 0);
      }
    }

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

    this->spriteData = NULL;
    this->active = false;
    this->facing = Direction::Up;
    this->clear();

}

bool AISprite::getActive() {

    return this->active;

}

void AISprite::think() {
    
    if (this->getIntelligence() & 0b00000100) {
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
        if (this->collisionCheckX(Direction::Left)) { 
            this->facing = Direction::Right; vx = 0; return; 
        }
        else {
            vx = this->getSpeed() * -1;
        }
    }

    if (this->facing == Direction::Right) {
        if (this->collisionCheckX(Direction::Right)) { 
            this->facing = Direction::Left; vx = 0; return; 
        }
        else {
            vx = this->getSpeed();
        }
    }

}

void AISprite::detectGap() {

    if (this->facing == Direction::Left) {
        if (!this->collide(x-1, this->getBottomY() + 1)) { 
            this->facing = Direction::Right; vx = 0; return; 
        }
        else {
            vx = this->getSpeed() * -1;
        }
    }

    if (this->facing == Direction::Right) {
        if (!this->collide(this->getRightX()+1, this->getBottomY() + 1)) { 
            this->facing = Direction::Left; vx = 0; return; 
        }
        else {
            vx = this->getSpeed();
        }
    }

}


//---------------------------------------------------------------------------------------------------
// InteractiveObject
//---------------------------------------------------------------------------------------------------
//
uint8_t InteractiveObject::collide(int tX, int tY) {

    int16_t nX = tX / Constants::TileSize;
    int16_t nY = tY / Constants::TileSize;

    if (Game->level.isTile(nX, nY)) {
        return 0xFF;
    }

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

    int index = (Constants::RoomHeight/8) * x;

    if (y < 8) {
        uint8_t mask = 1 << y;
        if (data[index] & mask) return true;
    }
    else {
        uint8_t mask = 1 << (y - 8);
        if (data[index + 1] & mask) return true;
    }

    return false;
}


//---------------------------------------------------------------------------------------------------
// Map
//---------------------------------------------------------------------------------------------------
//
void Map::generateRoom(int roomNum) {

    randomSeed(Game->Seeds[ (Game->mapNumber + roomNum) % Constants::GameSeeds ] * Game->mapNumber + roomNum);
    rooms[roomNum%Constants::MapRooms].clearRoom();
    uint8_t floor = random(Constants::RoomHeight-3,Constants::RoomHeight);

    int Gap = 0;
    int tSpawnBarrier = roomNum * Constants::RoomWidth;

    if (roomNum == 0) {
        //Remove Pipe addPipe(1, floor - 2);
    }
    for (int x = 0; x < Constants::RoomWidth; x++) {

        if (!Gap) {
            for (int b = floor; b < Constants::RoomHeight; b++) {
            rooms[roomNum % Constants::MapRooms].setTile(x, b);
            }
            if (roomNum && (roomNum < LastRoom)) {

                if (!random(10)) { 
                    Gap = random(2,5);
                }
                else if (!random(5) ) {
                    if (!random(1) && floor < Constants::RoomHeight - 1) floor++;
                    else floor--;
                }

                if (tSpawnBarrier > SpawnBarrier) {

                    if (!random(8)) {

                        switch (random(20)) {

                            case 0 ... 9:
                                Game->addMob(Data::Triangleo, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, floor - 2);
                                break;

                            case 10 ... 15:
                                Game->addMob(Data::Smileo, Images::SpriteImages[ObjectTypes::STSmileo], Images::SpriteMasks[ObjectTypes::STSmileo], tSpawnBarrier + x, floor - 2);
                                break;

                            case 16 ... 18:
                                if (roomNum > 8) {
                                    Game->addMob(Data::Starmano, Images::SpriteImages[ObjectTypes::STStarmano], Images::SpriteMasks[ObjectTypes::STStarmano], tSpawnBarrier + x, floor - 2);
                                }
                                break;

                            default:
                                if (roomNum > 8) {
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

        addExit(this->Game->mapNumber % 2 == MapLevel::AboveGround ? ObjectTypes::STAboveGroundExit : ObjectTypes::STUnderGroundExit, MaxXTile() - 2, floor - 1);

    }

    if (tSpawnBarrier > SpawnBarrier) SpawnBarrier = tSpawnBarrier;

}

void Map::addExit(ObjectTypes exitType, int x, int y) {

  addObject(exitType, x, y);

}

// void Map::addPipe(int x, int y) {

//   addObject(STPipeCapLeft,  x,   y);
//   addObject(STPipeCapRight, x+1, y);

//   for (uint8_t a = y+1; a < Constants::RoomHeight; a++) {
//     addObject(STPipeLeft,     x,   a);
//     addObject(STPipeRight,    x+1, a);
//   }

// }

// void Map::addTopPipe(int x, int y) {

//   addObject(STTopPipeCapLeft,  x,   y + 1);
//   addObject(STTopPipeCapRight, x+1, y + 1);
//   addObject(STPipeLeft,     x,   y);
//   addObject(STPipeRight,    x+1, y);

// }

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
