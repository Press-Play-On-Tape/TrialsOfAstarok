#include <Arduboy2.h>
#include "SquarioGame.h"


//---------------------------------------------------------------------------------------------------
// Sprite
//---------------------------------------------------------------------------------------------------
//
uint8_t Sprite::getWidth()          { Serial.print("Width:"); Serial.print(pgm_read_byte(&this->spriteImg[0]));  return pgm_read_byte(&this->spriteImg[0]); }
uint8_t Sprite::getHeight()         { Serial.print(" Height:"); Serial.println(pgm_read_byte(&this->spriteImg[1]));  return pgm_read_byte(&this->spriteImg[1]); }
uint8_t Sprite::getMasks()          { return pgm_read_byte(this->spriteData + SpriteMasks); }
uint8_t Sprite::getMaxFrame()       { return pgm_read_byte(this->spriteData + SpriteMaxFrame); }
uint8_t Sprite::getCyclesPerFrame() { return pgm_read_byte(this->spriteData + SpritegetCyclesPerFrame); }
uint8_t Sprite::getFlags()          { return pgm_read_byte(this->spriteData + SpriteFlags); }

int16_t Sprite::getRightX() { return x + this->getWidth() - 1; }
int16_t Sprite::getBottomY() { return y + this->getHeight() - 1; }


const uint8_t * Sprite::FramePointer () {
  // int frameSize = this->getHeight() * this->getWidth() / 8;
  // return SpriteData + SpriteImageData + (frameSize * (currentFrame / getCyclesPerFrame()));
  return this->spriteImg;
}

const uint8_t * Sprite::MaskPointer () {
  // int frameSize = this->getHeight() * this->getWidth() / 8;
  // return SpriteData + SpriteImageData + (frameSize * getMaxFrame()) + (frameSize * (currentFrame / getCyclesPerFrame()));
  return this->spriteMask;
}

void Sprite::LoadSprite(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY) {
  this->spriteData = data;
  this->spriteImg = img;
  this->spriteMask = mask;
  x = tX; y = tY;
  vx = 0; vy = 0;
  Mirrored = false;
  currentFrame = 0;
}

void Sprite::ClearSprite() {
  this->spriteData = NULL;
  x = -1;
  y = -1;
  vx = 0;
  vy = 0;
  currentFrame = 0;
  Mirrored = false;
}

bool Sprite::IsIn(int tX, int tY) {
  if (tX >= x &&
       tX <= this->getRightX() &&
       tY >= y &&
       tY <= this->getBottomY()) return true;
  return false;
}

bool Sprite::IsInTopHalf(int tX, int tY) {
  if (tX >= x &&
       tX <= this->getRightX() &&
       tY >= y &&
       tY <= (y+(this->getHeight()/2))) return true;
  return false;
}

bool Sprite::GetPixelAbsolute(int tX, int tY) {
  int RelativeX = tX - x;
  int RelativeY = tY - y;
  if (RelativeX < 0 || RelativeY < 0 || RelativeX > this->getWidth() || RelativeY > this->getHeight()) return false;
  uint8_t row = RelativeY / 8;
  uint8_t offset = RelativeY % 8;
  byte selection = pgm_read_byte(MaskPointer() + (row * this->getWidth()) + RelativeX);
  return (selection & (1 << offset));
}

byte Sprite::Collide(int tX, int tY) {
  int nX = tX / TileSize;
  int nY = tY / TileSize;
  if (Game->level.CheckTile(nX, nY)) return 0xFF;
  return Game->level.CheckObject(nX, nY);
}

bool Sprite::Falling() {
  return !CollisionCheckY(Direction::Down);
}

void Sprite::Gravity() {
  if (vy < 6) vy++;
}

bool Sprite::CollisionCheckX(Direction direction) {
  for (uint8_t tY = 0; tY < (this->getHeight() / TileSize); tY++) {
    switch (direction) {
      case Left:
        if (Collide(x-1, y+(tY*TileSize)) || Collide(x-1, y+((tY + 1)*TileSize) - 1)) return true;
        break;
      case Right:
        if (Collide(x + this->getWidth(), y+(tY*TileSize)) || Collide(x + this->getWidth(), y+((tY + 1)*TileSize) - 1)) return true;
        break;
      default: break;
    }
  }
  return false;
}

bool Sprite::CollisionCheckY(Direction direction) {
  for (uint8_t tX = 0; tX < (this->getWidth() / TileSize); tX++) {
    switch (direction) {
      case Up:
        if (Collide(x+(tX*TileSize), y - 1) || Collide(x+((tX + 1)*TileSize)-1, y - 1)) return true;
        break;
      case Down:
        if (Collide(x+(tX*TileSize), y + this->getHeight()) || Collide(x+((tX + 1)*TileSize)-1, y + this->getHeight())) return true;
        break;
      default: break;
    }
  }
  return false;
}

void Sprite::Move() {
  if (this->getFlags() & 1) {
    x += vx;
    y += vy;
    return;
  }
  if (vy == 0) { // Start fall
    if (Falling()) Gravity();
  }
  if (vy > 0) { // Down
    for (int a = 0; a < vy; a++) {
      if (Falling()) {
        y++;
      }
      else { vy = 0; break; }
    }
    Gravity();
  }
  if (vy < 0) { // Up
    Gravity();
    for (int a = 0; a > vy; a--) {
      if (CollisionCheckY(Direction::Up)) { headCollision(); vy = 0; break; }
      else y--;
    }
  }
  if (vx > 0) { // Right
    for (int a = 0; a < vx; a++){
    if (this->getRightX() > Game->level.MaxXPixel()) break;
      if (CollisionCheckX(Direction::Right)) break;
      else x++;
    }
//  if (!Game->MainHand.Used) Mirrored = false;
  }
  if (vx < 0) { // Left
    for (int a = 0; a > vx; a--){
      if (x < Game->level.MinXPixel() + 1) break;
      if (CollisionCheckX(Direction::Left)) break;
      else x--;
    }
//  if (!Game->MainHand.Used) Mirrored = true;
  }
}

bool Sprite::Jump() {
  if (CollisionCheckY(Direction::Down)) { vy = -8; return true; }
  return false;
}

void Sprite::duck() {
  if (x < 64) return;
  if (Collide(x, y + this->getHeight() + 1) == STPipeCapLeft && Collide(this->getRightX() , y + this->getHeight() + 1) == STPipeCapRight) {
    Game->SFX = SFX_Pipe;
    Game->event = EventType::PipeDrop;
    Game->eventCounter = 0;
  }
}

void Sprite::headCollision() {

  if (this->getFlags() & 0b10) return;

  if (Collide(x, y - 1) == STTopPipeCapLeft && Collide(this->getRightX(), y - 1) == STTopPipeCapRight) {
    if (x < 64) return;
    Game->SFX = SFX_Pipe;
    Game->event = EventType::PipeRise;
    Game->eventCounter = 0;
  }

  byte LeftCheck = Collide(x, y - 1);
  byte RightCheck = Collide(this->getRightX(), y - 1);

  if (LeftCheck == STQBlock || LeftCheck == STMushBlock) {
    Game->level.handleObject(x / TileSize, (y - 1) / TileSize);
  }
  if (RightCheck == STQBlock || RightCheck == STMushBlock) {
    Game->level.handleObject(this->getRightX() / TileSize, (y - 1) / TileSize);
  }
  
}

void Sprite::draw(Arduboy2 &arduboy) {
  if (this->getMasks()) arduboy.drawBitmap(
    x - Game->cameraX,
    y - Game->cameraY,
    MaskPointer(), this->getWidth(), this->getHeight(), BLACK);
    Sprites::drawExternalMask(x - Game->cameraX, y - Game->cameraY, this->spriteImg, this->spriteMask, 0, 0);
    if (currentFrame + 1 < getMaxFrame() * getCyclesPerFrame()) currentFrame++;
    else currentFrame = 0;
}




//---------------------------------------------------------------------------------------------------
// AISprite
//---------------------------------------------------------------------------------------------------
//
uint8_t AISprite::Speed()        { return pgm_read_byte(this->spriteData + SpriteSpeed); }
byte    AISprite::Intelligence() { return pgm_read_byte(this->spriteData + SpriteIntelligence); }

void AISprite::Activate(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY) {
  // this->spriteData = data;
  // this->spriteImg = img;
  // this->spriteMask = mask;

  Active = true;
  this->facing = Direction::Left;
  LoadSprite(data, img, mask, tX * TileSize, tY * TileSize);
  if (data == Images::SpriteImages[ObjectTypes::STBolt]) {
    vx = -4;
    vy = 2;
  }
  Think();
}

void AISprite::Deactivate() {
  this->spriteData = NULL;
  Active = false;
  this->facing = Direction::Up;
  ClearSprite();
}

void AISprite::Think() {
  if   (Intelligence() & 0b00000100) {
    Seek();
    if (Intelligence() & 0b00001000) DetectJump();
  }
  else {
    if (Intelligence() & 0b00000001) DetectWall();
    if (Intelligence() & 0b00000010) DetectGap();
  }
  Move();
}

void AISprite::Seek() {
  if (Game->player.x + Game->player.getWidth() < x) {
    this->facing = Direction::Left;
    vx = Speed() * -1;
  }
  if (Game->player.x > x + this->getWidth()) {
    this->facing = Direction::Right;
    vx = Speed();
  }
}

void AISprite::DetectJump() {
  if (CollisionCheckX(this->facing)) Jump();
  if (this->facing == Direction::Left) {
    if (!Collide(x-1, (RoomHeight*TileSize) - 1)) Jump();
  }
  if (this->facing == Direction::Right) {
    if (!Collide(this->getRightX() + 1, (RoomHeight*TileSize) - 1)) Jump();
  }
}

void AISprite::DetectWall() {
  if (this->facing == Direction::Left) {
    if (CollisionCheckX(Direction::Left)) { this->facing = Direction::Right; vx = 0; return; }
    else vx = Speed() * -1;
  }
  if (this->facing == Direction::Right) {
    if (CollisionCheckX(Direction::Right)) { this->facing = Direction::Left; vx = 0; return; }
    else vx = Speed();
  }
}

void AISprite::DetectGap() {
  if (this->facing == Direction::Left) {
    if (!Collide(x-1, this->getBottomY() + 1)) { this->facing = Direction::Right; vx = 0; return; }
    else vx = Speed() * -1;
  }
  if (this->facing == Direction::Right) {
    if (!Collide(this->getRightX()+1, this->getBottomY() + 1)) { this->facing = Direction::Left; vx = 0; return; }
    else vx = Speed();
  }
}

void Room::ClearRoom() {
  for (int a = 0; a < RoomBytes; a++) data[a] = 0;
}

void Room::SetTile(int x, int y) {
  if (x > RoomWidth || y > RoomHeight) return;
  int Index = (RoomHeight/8) * x;
  if (y < 8) data[ Index ]   |= 1 << y;
  else         data[ Index+1 ] |= 1 << (y - 8);
}

bool Room::ReadTile(int x, int y) {
  if (x > RoomWidth || y > RoomHeight) return false;
  int Index = (RoomHeight/8) * x;
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

void Map::generateRoom(int RoomNum) {

  randomSeed(Game->Seeds[ (Game->mapNumber + RoomNum) % GameSeeds ] * Game->mapNumber + RoomNum);
  rooms[RoomNum%MapRooms].ClearRoom();
  uint8_t Floor = random(RoomHeight-3,RoomHeight);
  uint8_t Ceiling = (!(Game->mapNumber % 2)) ? 8 : 0;
  int Gap = 0;
  int tSpawnBarrier = RoomNum*RoomWidth;
  if (!RoomNum) {
    if (Ceiling) AddTopPipe(1, Ceiling + 1);
    else AddPipe(1, Floor-2);
  }
  for (int x = 0; x < RoomWidth; x++) {
    if (Ceiling) rooms[RoomNum % MapRooms].SetTile(x, Ceiling);
    if (!Gap) {
      for (int b = Floor; b < RoomHeight; b++) {
        rooms[RoomNum % MapRooms].SetTile(x, b);
      }
      if (RoomNum && (RoomNum < LastRoom)) {
        if (!random(10)) { 
          Gap = random(2,5);
          if (Ceiling) Gap--;
        }
        else if (!random(5) ) {
          if (!random(1) && Floor < RoomHeight - 1) Floor++;
          else Floor--;
        }
        if (tSpawnBarrier > SpawnBarrier) {
          if (!random(8)) {
            uint8_t MobSelector = random(20);
            if      (MobSelector < 10) Game->addMob(TriangleoSprite, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, Floor - 2);
            else if (MobSelector < 16) Game->addMob(SmileoSprite, Images::SpriteImages[ObjectTypes::STSmileo], Images::SpriteMasks[ObjectTypes::STSmileo], tSpawnBarrier + x, Floor - 2);
            else if (MobSelector < 19) {
              if (RoomNum > 8) Game->addMob(StarmanoSprite, Images::SpriteImages[ObjectTypes::STStarmano], Images::SpriteMasks[ObjectTypes::STStarmano], tSpawnBarrier + x, Floor - 2);
            }
            else { 
              if (RoomNum > 8) Game->addMob(BoltSprite, Images::SpriteImages[ObjectTypes::STBolt], Images::SpriteMasks[ObjectTypes::STBolt], tSpawnBarrier + x, 2);
            }
          }
          if (!random(16) && !Gap && Floor > Ceiling + 5 && x != RoomWidth - 1) {
            int y = random(max(Floor - 7, Ceiling + 2), Floor - 3);
            if (!random(4)) addObject (STMushBlock, tSpawnBarrier + x, y);
            else              addObject (STQBlock, tSpawnBarrier + x, y);
          }
        }
      }
    }
    else Gap--;
  }
  if (RoomNum == LastRoom) {
    if (Ceiling) AddTopPipe (MaxXTile() - 2, Ceiling + 1);
    else AddPipe(MaxXTile() - 2, Floor-2);
  }
  if (tSpawnBarrier > SpawnBarrier) SpawnBarrier = tSpawnBarrier;
}
void Map::AddPipe(int x, int y) {
  addObject(STPipeCapLeft,  x,   y);
  addObject(STPipeCapRight, x+1, y);
  for (uint8_t a = y+1; a < RoomHeight; a++) {
    addObject(STPipeLeft,     x,   a);
    addObject(STPipeRight,    x+1, a);
  }
}
void Map::AddTopPipe(int x, int y) {
  addObject(STTopPipeCapLeft,  x,   y + 1);
  addObject(STTopPipeCapRight, x+1, y + 1);
  addObject(STPipeLeft,     x,   y);
  addObject(STPipeRight,    x+1, y);
}

void Map::addObject(byte type, int tX, int tY) {
  if (CheckObject(tX, tY)) return;
  else {
    objects[ObjectIndex].x = tX;
    objects[ObjectIndex].y = tY;
    objects[ObjectIndex].type = type;
    ObjectIndex++;
    if (ObjectIndex == MapObjects) ObjectIndex = 0;
  }
}

void Map::handleObject(int x, int y) {
  for (int a = 0; a < MapObjects; a++) {
    if (objects[a].x == x && objects[a].y == y) {
      switch (objects[a].type) {
        case STQBlock: 
          Game->coins++;
          if (!(Game->coins % 20)) {
            Game->lives++;
            Game->SFX = SFX_Life;
          }
          else Game->SFX = SFX_Coin;
          objects[a].type = STBQBlock;
          break;
        case STMushBlock:
          Game->addMob (MushroomSprite,  Images::SpriteImages[ObjectTypes::STMushroom], Images::SpriteMasks[ObjectTypes::STMushroom], x, y - 1);
          objects[a].type = STBQBlock; break;
      }
    }
  }
}
void Map::RemoveObject(int x, int y) {
  for (int a = 0; a < MapObjects; a++) {
    if (objects[a].x == x && objects[a].y == y) {
      objects[a].y = -1;
      return;
    }
  }
}
void Map::NewMap() {
  // Reset Variables
  ObjectIndex = 0; LastLoadLocation = 0; FirstRoom = 0; SpawnBarrier = 0;
  for (uint8_t a = 0; a < MapObjects; a++) objects[a].y = -1;
  for (uint8_t a = 0; a < SpriteCap; a++) Game->mobs[a].Deactivate();

  // Seed for level length
  randomSeed(Game->Seeds[ Game->mapNumber % GameSeeds ] * Game->mapNumber);
  int LowEnd = MinLevelWidth + random(Game->mapNumber);
  int HighEnd = random(LowEnd, LowEnd + Game->mapNumber);
  LastRoom = random(LowEnd, HighEnd);

  for (uint8_t a = 0; a < MapRooms; a++) generateRoom(a);
}
void Map::LoadMap() {
  int RoomBeforePlayerIsIn = (Game->player.x / (RoomWidth*TileSize)) - 1;
  if (RoomBeforePlayerIsIn < 0) RoomBeforePlayerIsIn = 0;
  if (RoomBeforePlayerIsIn > FirstRoom) {
    FirstRoom = RoomBeforePlayerIsIn;
    generateRoom(RoomBeforePlayerIsIn + MapRooms - 1);
  }
}
bool Map::CheckTile(int x, int y) {
  int room = (x / RoomWidth) % MapRooms;
  return rooms[room].ReadTile (x % RoomWidth, y);
}
byte Map::CheckObject (int x, int y) {
  if (y < 0) return 0;
  for (int a = 0; a < MapObjects; a++) {
    if ((objects[a].x == x) && (objects[a].y == y)) return objects[a].type;
  }
  return 0;
}
int Map::MinXPixel() { return FirstRoom * RoomWidth * TileSize; }
int Map::MaxXPixel() { return ((LastRoom + 1) * RoomWidth * TileSize) - 1; }
int Map::MaxYPixel() { return ((MapHeight + 1) * RoomHeight * TileSize) - 1; }
int Map::MinXTile() { return FirstRoom * RoomWidth; }
int Map::MaxXTile() { return ((LastRoom + 1) * RoomWidth) - 1; }
int Map::MaxYTile() { return ((MapHeight + 1) * RoomHeight) - 1; }
