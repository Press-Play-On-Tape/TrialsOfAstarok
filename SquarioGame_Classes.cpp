/*
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
    this->xInit = tX; 
    this->yInit = tY;
    this->vx = 0; 
    this->vy = 0;
    this->currentFrame = 0;
    this->facing = Direction::Right;

}

void Sprite::clear() {

    this->spriteData = nullptr;
    this->x = -1;
    this->y = -1;
    this->vx = 0;
    this->vy = 0;
    this->currentFrame = 0;
    this->relatedSprite = nullptr;

}

uint8_t Sprite::collide(int16_t tX, int16_t tY) {

    int16_t nX = tX / Constants::TileSize;
    int16_t nY = tY / Constants::TileSize;

    if (this->game->level.isTile(nX, nY)) return 0xFF;

    uint8_t object = this->game->level.checkObject(nX, nY);

    switch (object) {

        case ObjectTypes::STTriangleo ... ObjectTypes::STUnderGroundExit:
        case ObjectTypes::STFireball ... ObjectTypes::STFirepit:
            return object;

        case STSign:
            return 0;

    }

    return 0;
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

    for (uint8_t tX = 0; tX < (this->getWidth() / Constants::TileSize); tX++) {

        switch (direction) {

            case Up:
                if (this->collide(x + (tX * Constants::TileSize), y - 1) || this->collide(x + ((tX + 1) * Constants::TileSize) - 1, y - 1)) {
                    return true;
                }
                break;

            case Down:
                if (this->collide(x + (tX * Constants::TileSize), y + this->getHeight()) || this->collide(x + ((tX + 1) * Constants::TileSize) - 1, y + this->getHeight())) {
                    return true;
                }
                break;

            default: break;
        }

    }
    return false;

}

void Sprite::move() {


    // Handle player frame if stationary ..

    if (this->getType() == ObjectTypes::STSquario) {

       if (this->vx == 0 && this->vy == 0) {
           if (arduboy->getFrameCount(6) == 0) {
            this->frame = (this->frame + 1) % 3;
           }
        }

    }
 
    switch (this->getType()) {

        case ObjectTypes::STFireball:

            if (this->vy == Constants::Fireball_NotMoving && random(0, 40) == 0) {
                this->vy = Constants::Fireball_StartPos;
            }

            if (this->vy != Constants::Fireball_NotMoving) {
                this->y = this->y + (this->vy / 4);                
                this->vy++;
            }

            if (this->vy == -Constants::Fireball_StartPos) {
                this->vy = Constants::Fireball_NotMoving;
                this->y = this->yInit;
            }

            break;

        default:

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

                for (int a = 0; a < vx; a++) {

                    if (this->getRightX() > this->game->level.maxXPixel()) break;

                    if (this->collisionCheckX(Direction::Right)) {
                        break;
                    }
                    else { 
                        this->x++;
                        if (vy == 0 && !isFalling()) {
                            this->frame = (this->frame + 1) % 4;
                        }

                    }

                }

            }

            if (vx < 0) { // Left

                for (int a = 0; a > vx; a--)  {

                    if (x < this->game->level.minXPixel() + 1) break;

                    if (this->collisionCheckX(Direction::Left)) {
                        break;
                    }
                    else {

                        x--;
                        if (vy == 0 && !isFalling()) {
                            this->frame = (this->frame + 1) % 4;
                        }

                    }

                }

            }

            break;

    }

}

bool Sprite::jump() {

  if (this->collisionCheckY(Direction::Down)) { 

    vy = -10; return true; }
  return false;

}


void Sprite::headCollision() {

  if (this->getFlags() & 0b10) return;

  byte LeftCheck = this->collide(x, y - 1);
  byte RightCheck = this->collide(this->getRightX(), y - 1);

  if (LeftCheck == STQBlock || LeftCheck == STMushBlock) {
    this->game->level.handleObject(x / Constants::TileSize, (y - 1) / Constants::TileSize);
  }
  if (RightCheck == STQBlock || RightCheck == STMushBlock) {
    this->game->level.handleObject(this->getRightX() / Constants::TileSize, (y - 1) / Constants::TileSize);
  }
  
}

void Sprite::draw() {

    switch (this->getType()) {

       case ObjectTypes::STSquario:

            if (this->isFalling()) {
                Sprites::drawExternalMask(x - this->game->cameraX, y - 1 - this->game->cameraY, Images::Player_Jumping, Images::Player_Jumping_Mask, this->facing == Direction::Right, this->facing == Direction::Right);
            }
            else if (this->vx == 0 && this->vy == 0) {
                Sprites::drawExternalMask(x - this->game->cameraX, y - 1 - this->game->cameraY, pgm_read_word_near(&Images::Player_Idle[this->getFrame()]), pgm_read_word_near(&Images::Player_Idle_Masks[this->getFrame()]), this->facing == Direction::Right, this->facing == Direction::Right);
            }
            else {
                Sprites::drawExternalMask(x - this->game->cameraX, y - 1 - this->game->cameraY, pgm_read_word_near(&Images::Player_Images[this->getFrame()]), pgm_read_word_near(&Images::Player_Masks[this->getFrame()]), this->facing == Direction::Right, this->facing == Direction::Right);
            }
            break;

        case ObjectTypes::STFirepit:
            Sprites::drawExternalMask(x - this->game->cameraX, y + 1 - this->game->cameraY, this->spriteImg, this->spriteMask, arduboy->getFrameCount(24) / 8, arduboy->getFrameCount(24) / 8);
            break;

        case ObjectTypes::STSmileo:
        case ObjectTypes::STTriangleo:
            if (this->game->mapNumber % 2 == MapLevel::AboveGround) {
                Sprites::drawErase(x - this->game->cameraX, y -  this->game->cameraY, this->spriteImg, this->facing == Direction::Right);
            }
            else {
                Sprites::drawExternalMask(x - this->game->cameraX, y - this->game->cameraY, this->spriteImg, this->spriteMask, this->facing == Direction::Right, this->facing == Direction::Right);
            }
            break;

        case ObjectTypes::STFireball:
            Sprites::drawExternalMask(x - this->game->cameraX, y - this->game->cameraY, this->spriteImg, this->spriteMask, this->vy > 0, this->vy > 0);
            break;

        default:

            if (this->game->mapNumber % 2 == MapLevel::AboveGround) {
                Sprites::drawErase(x - this->game->cameraX, y -  this->game->cameraY, this->spriteImg, 0);
            }
            else {
                Sprites::drawExternalMask(x - this->game->cameraX, y - this->game->cameraY, this->spriteImg, this->spriteMask, 0, 0);
            }

            break;
    }

}

uint8_t Sprite::getFrame() {

    if (this->vx == 0 && this->vy == 0 && this->frame >= 3) this->frame = 0;
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

    if (data == Data::Bolt) {
        vx = -4;
        vy = 2;
    }

    if (data == Data::Fireball) {
        vx = 0;
        vy = Constants::Fireball_NotMoving;
    }

    this->think();

}

void AISprite::deactivate() {

    this->spriteData = nullptr;
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

    this->move();

}

void AISprite::seek() {

    if (this->game->player.x + this->game->player.getWidth() < x) {
        this->facing = Direction::Left;
        vx = this->getSpeed() * -1;
    }

    if (this->game->player.x > x + this->getWidth()) {
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
uint8_t InteractiveObject::collide(int16_t tX, int16_t tY) {

    int16_t nX = tX / Constants::TileSize;
    int16_t nY = tY / Constants::TileSize;

    if (this->game->level.isTile(nX, nY)) {
        return 0xFF;
    }

    return this->game->level.checkObject(nX, nY);

}

void InteractiveObject::deactivate() {

    this->x = -1;
    this->y = -1;

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

    int index = (Constants::RoomHeight / 8) * x;
    if (y < 8) data[index]     |= 1 << y;
    else       data[index + 1] |= 1 << (y - 8);

}

void Room::clearTile(int x, int y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return;

    int index = (Constants::RoomHeight / 8) * x;

    if (y < 8) data[index]     &= ~(1 << y);
    else       data[index + 1] &= ~(1 << (y - 8));

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
void Map::generateRoom(uint8_t roomNum) {
   
    randomSeed(this->game->Seeds[ (this->game->mapNumber + roomNum) % Constants::GameSeeds ] * this->game->mapNumber + roomNum);
    rooms[roomNum%Constants::MapRooms].clearRoom();
    uint8_t floor = random(Constants::RoomHeight - 3, Constants::RoomHeight);

    int8_t gap = 0;
    uint8_t firePit = 0;
    int tSpawnBarrier = roomNum * Constants::RoomWidth;


    // If this is the first room on a level, add the sign ..

    if (roomNum == 0) {
        addSign(1, floor - 1);
    }

    for (int x = 0; x < Constants::RoomWidth; x++) {

        if (gap == 0) {


            // Fill the map data from the current floor to the bottom of the map ..

            for (int b = floor; b < Constants::RoomHeight; b++) {
                rooms[roomNum % Constants::MapRooms].setTile(x, b);
            }

            if (roomNum && (roomNum < this->lastRoom)) {

                if (firePit > 0) { // We must keep floor level ..

                    if (firePit == 2) {
                        rooms[roomNum % Constants::MapRooms].clearTile(x, floor);
                        this->game->addMob(Data::Fireball, Images::Fireball, Images::Fireball_Mask, tSpawnBarrier + x, floor);
                        this->game->addMob(Data::Firepit, Images::Firepit, Images::Firepit_Mask, tSpawnBarrier + x, floor - 1);
                    }

                    firePit--;

                }
                else if (random(10) == 0) { 
                    gap = random(2,5);
                }
                else if (random(5) == 5) {
                    if (!random(1) && floor < Constants::RoomHeight - 1) floor++;
                    else floor--;
                }
                else if (floor < 15 && random(7) == 0) {
                    firePit = 3; 
                }

                if (tSpawnBarrier > SpawnBarrier && firePit != 2) {

                    if (!random(8)) {

                        switch (random(20)) {

                            case 0 ... 9:
                                this->game->addMob(Data::Triangleo, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, floor - 2);
                                break;

                            case 10 ... 15:
                                this->game->addMob(Data::Smileo, Images::SpriteImages[ObjectTypes::STSmileo], Images::SpriteMasks[ObjectTypes::STSmileo], tSpawnBarrier + x, floor - 2);
                                break;

                            case 16 ... 18:
                                if (roomNum > 8) {
                                    this->game->addMob(Data::Starmano, Images::SpriteImages[ObjectTypes::STStarmano], Images::SpriteMasks[ObjectTypes::STStarmano], tSpawnBarrier + x, floor - 2);
                                }
                                break;

                            default:
                                if (roomNum > 8) {
                                    this->game->addMob(Data::Bolt, Images::SpriteImages[ObjectTypes::STBolt], Images::SpriteMasks[ObjectTypes::STBolt], tSpawnBarrier + x, 2);
                                }
                                break;

                        }

                    }

                    #ifdef ORIG_GAME_MUSHROOM
                    if (!random(16) && !gap && floor > ceiling + 5 && x != Constants::RoomWidth - 1) {

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
        else gap--;

    }


    // If this is the last room in a map, then add a pipe so we can leave ..

    if (roomNum == this->lastRoom) {

        addExit(this->game->mapNumber % 2 == MapLevel::AboveGround ? ObjectTypes::STAboveGroundExit : ObjectTypes::STUnderGroundExit, maxXTile() - 2, floor - 1);

    }

    if (tSpawnBarrier > SpawnBarrier) SpawnBarrier = tSpawnBarrier;

}

void Map::addExit(ObjectTypes exitType, int x, int y) {

  addObject(exitType, x, y);

}

void Map::addSign(int x, int y) {

  addObject(ObjectTypes::STSign,  x,   y);

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
          this->game->coins++;
          if (!(this->game->coins % 20)) {
            this->game->lives++;
            this->game->SFX = Sounds::SFX_Life;
          }
          else this->game->SFX = Sounds::SFX_Coin;
          objects[a].type = STBQBlock;
          break;
        // case STMushBlock:
        //   this->game->addMob(Data::Mushroom, Images::SpriteImages[ObjectTypes::STMushroom], Images::SpriteMasks[ObjectTypes::STMushroom], x, y - 1);
        //   objects[a].type = STBQBlock; break;
      }
    }
  }
}


void Map::newMap() {

    // Reset Variables

    ObjectIndex = 0; 
    this->lastLoadLocation = 0; 
    this->firstRoom = 0; 
    SpawnBarrier = 0;

    for (uint8_t a = 0; a < Constants::MapObjects; a++) objects[a].deactivate();
    for (uint8_t a = 0; a < Constants::SpriteCap; a++) this->game->mobs[a].deactivate();

    // Seed for level length

    randomSeed(this->game->Seeds[ this->game->mapNumber % Constants::GameSeeds ] * this->game->mapNumber);
    int lowEnd = Constants::MinLevelWidth + random(this->game->mapNumber);
    int highEnd = random(lowEnd, lowEnd + this->game->mapNumber);
    this->lastRoom = random(lowEnd, highEnd);

    for (uint8_t a = 0; a < Constants::MapRooms; a++) {
        generateRoom(a);
    }

}

void Map::loadMap() {

    int roomBeforePlayerIsIn = (this->game->player.x / (Constants::RoomWidth*Constants::TileSize)) - 1;

    if (roomBeforePlayerIsIn < 0) roomBeforePlayerIsIn = 0;

    if (roomBeforePlayerIsIn > this->firstRoom) {
        this->firstRoom = roomBeforePlayerIsIn;
        generateRoom(roomBeforePlayerIsIn + Constants::MapRooms - 1);
    }

}

bool Map::isTile(int x, int y) {

  int room = (x / Constants::RoomWidth) % Constants::MapRooms;
  return rooms[room].readTile(x % Constants::RoomWidth, y);

}

byte Map::checkObject(int x, int y) {
  if (y < 0) return 0;
  for (int a = 0; a < Constants::MapObjects; a++) {
    if ((objects[a].x == x) && (objects[a].y == y)) return objects[a].type;
  }
  return 0;
}

int16_t Map::minXPixel() { return this->firstRoom * Constants::RoomWidth * Constants::TileSize; }
int16_t Map::maxXPixel() { return ((this->lastRoom + 1) * Constants::RoomWidth * Constants::TileSize) - 1; }
int16_t Map::maxYPixel() { return ((this->mapHeight + 1) * Constants::RoomHeight * Constants::TileSize) - 1; }
int16_t Map::minXTile() { return this->firstRoom * Constants::RoomWidth; }
int16_t Map::maxXTile() { return ((this->lastRoom + 1) * Constants::RoomWidth) - 1; }
int16_t Map::maxYTile() { return ((this->mapHeight + 1) * Constants::RoomHeight) - 1; }
*/