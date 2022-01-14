#include <Arduboy2.h>
#include "DefinesImagesAndSounds.h"
#include "SquarioGame.h"

SquarioGame::SquarioGame() {

  this->player.Game = this;
  this->level.Game = this;
  
  for (uint8_t a = 0; a < SpriteCap; a++) {
    this->mobs[a].Game = this;
  }

}
void SquarioGame::newGame() {

  this->health = 0;
  this->score = 0;
  this->distancePoints = 0;
  this->coins = 0;
  this->lives = 1;
  this->mapNumber = 1;
  this->player.LoadSprite(SmallSquarioSprite, 10, spawnY());
  startLevel();

}
void SquarioGame::startLevel() {

  this->event = EventType::Playing;
  SFX = NULL;
  this->level.NewMap();
  while (this->player.Falling()) this->player.Move();
  adjustCamera();
}

uint8_t SquarioGame::spawnY() {
  if (this->mapNumber % 2) return 0;
  else return 88;
}
void SquarioGame::processButtons(Arduboy2 &arduboy) {

  uint8_t MaxSpeed = arduboy.pressed(A_BUTTON) ? 4 : 3;


  if (!arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)) {
    if (this->player.vx > 0) this->player.vx--;
    if (this->player.vx < 0) this->player.vx++;
  }
  if (arduboy.pressed(LEFT_BUTTON))  { this->player.vx--; if (this->player.vx < MaxSpeed * -1) this->player.vx = MaxSpeed * -1; }
  if (arduboy.pressed(RIGHT_BUTTON)) { this->player.vx++; if (this->player.vx > MaxSpeed) this->player.vx = MaxSpeed; }
  if (arduboy.pressed(B_BUTTON)) {
    if (this->player.Jump()) SFX = SFX_Jump;
  }
  if (arduboy.pressed(DOWN_BUTTON)) this->player.duck();


}
void SquarioGame::adjustCamera() {
  int MaxX = this->level.MaxXPixel() - WIDTH;
  int MaxY = this->level.MaxYPixel() - HEIGHT;
  int MinX = this->level.MinXPixel();
  this->cameraX = this->player.x - (WIDTH/2); // Center X on player
  this->cameraY = this->player.y - 8;

  // Constrain for map edges
  if (this->cameraY > MaxY) this->cameraY = MaxY;
  if (this->cameraX > MaxX) this->cameraX = MaxX;
  if (this->cameraX < MinX) this->cameraX = MinX;

  // Reload map data
    this->level.LoadMap();

}

void SquarioGame::cycle(Arduboy2 &arduboy, GameState &gameState) {
  bool Death = false;
  int MapPixelHeight = this->level.MaxYPixel();
  processButtons(arduboy);

  switch (this->event) {

    case EventType::PipeDrop:
      if (this->eventCounter < this->player.getHeight()) {
        this->player.y++;
        this->eventCounter++;
      }
      break;

    case EventType::PipeRise:
      if (this->eventCounter < this->player.getHeight()) {
        this->player.y--;
        this->eventCounter++;
      }
      break;

    case EventType::Death_Init:
    case EventType::Death:
      if (this->eventCounter > 25) this->player.y--;
      else this->player.y+=2;
      if (this->player.y > MapPixelHeight) this->eventCounter = 0;
      else this->eventCounter--;
      break;

    case EventType::Playing:
      this->player.Move();
      adjustCamera();
      break;

    default: break;

  }
  for (uint8_t a = 0; a < SpriteCap; a++) {
    if (this->mobs[a].Active) {
      this->mobs[a].Think();
      if (this->mobs[a].y > MapPixelHeight) this->mobs[a].Deactivate();
      else if (testCollision(arduboy, &player, &this->mobs[a])) {
        if (this->mobs[a].SpriteData == MushroomSprite) {
          this->mobs[a].Deactivate();
          this->score += POINTSMushroom;
          SFX = SFX_Mushroom;
          if (this->player.SpriteData == SmallSquarioSprite) this->player.LoadSprite(BigSquarioSprite, this->player.x, this->player.y-8);
          else if (this->health < 5) this->health++;
        }
        else if (this->player.Falling()) {
          this->mobs[a].Deactivate();
          this->score += POINTSKill;
          SFX = SFX_Hit;
//          if (ButtonState[ ButtonJump ]) { this->player.vy = -10; }
          if (arduboy.pressed(A_BUTTON)) { this->player.vy = -10;}
          else { this->player.vy = -4; }          
        }
        else if (!this->eventCounter) {
          if (this->health > 0) this->health--;
          else {
            if (this->player.getHeight() == TileSize) { 
              this->lives--; 
              //SJH this->event = EventType::Death_Init; 
            }
            if (this->player.getHeight() > TileSize) {
              this->player.LoadSprite(SmallSquarioSprite, this->player.x, this->player.y+8);
              SFX = SFX_Hit;
            }
          }
          this->eventCounter = 30;
        }
      }
    }
  }

  switch (this->event) {

    case EventType::Playing:
      if (this->player.y > MapPixelHeight) { 
        this->lives--; 
        //SJH this->event = EventType::Death_Init; 
        this->eventCounter = 25; 
      }

      if (this->eventCounter > 0) this->eventCounter--;
      break;

    case EventType::Death_Init:
    case EventType::Death:
      if (this->eventCounter == 0) {
        die(arduboy, gameState);
      }
      break;

    case EventType::PipeDrop:
    case EventType::PipeRise:
      if (this->eventCounter == this->player.getHeight()) {
        this->eventCounter = 0;
        this->distancePoints += this->player.x / TileSize;
        this->mapNumber++;
        this->player.x = 10;
        this->player.y = spawnY();
        Serial.println("startLevel 2");
        startLevel();
      }

      break;

    default: break;

  }

}

bool SquarioGame::testCollision(Arduboy2 &arduboy, Sprite * sprite1, AISprite * sprite2) {

  Rect rect1 = { sprite1->x, sprite1->y, sprite1->getWidth(), sprite1->getHeight()};
  Rect rect2 = { sprite2->x, sprite2->y, sprite2->getWidth(), sprite2->getHeight()};

  return arduboy.collide(rect1, rect2);

}

void SquarioGame::die(Arduboy2 &arduboy, GameState &gameState) {


  if (this->lives > 0) {
    this->health = 0;
    this->player.LoadSprite(SmallSquarioSprite, 10, spawnY());
    startLevel();
  }
  else {

    if (this->event == EventType::Death_Init) {
      this->origScore = this->score;
      this->distancePoints += this->player.x / TileSize;
      this->score += this->distancePoints;
      this->event = EventType::Death;
    }

    arduboy.drawRect(16,8,96,48, WHITE); // Box border
    arduboy.fillRect(17,9,94,46, BLACK); // Black out the inside
    arduboy.drawSlowXYBitmap(30,12,gameover,72,14,1);
    
    arduboy.setCursor(26,29); arduboy.print(F("Score"));
    arduboy.setCursor(20,37); arduboy.print(F("+Dist."));
    arduboy.setCursor(26,45); arduboy.print(F("Total"));

    arduboy.setCursor(76, 29);
    arduboy.print(this->origScore);
    arduboy.setCursor(76, 37);
    arduboy.print(this->distancePoints);
    arduboy.setCursor(76, 45);
    arduboy.print(this->score);

    // Move to High this->score mode .. 
    if (arduboy.justPressed(A_BUTTON)) {
      gameState = GameState::HighScore_Check;
      this->event = EventType::Off;
    }

  }

}


void SquarioGame::drawMobs(Arduboy2 &arduboy) {
  for (uint8_t a = 0; a < SpriteCap; a++) {
    if (this->mobs[a].Active) {
      if (this->mobs[a].getRightX() - this->cameraX > 0 && this->mobs[a].x - this->cameraX < 128) this->mobs[a].draw(arduboy);
    }
  }
}
void SquarioGame::drawMap(Arduboy2 &arduboy) {
  int mountainOffset = (this->cameraX / 4) % 64;
  int mountainYOffset = (this->cameraY / 12) - 4;
  if (this->mapNumber % 2) {
    arduboy.drawBitmap( 0 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
    arduboy.drawBitmap(64 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
    arduboy.drawBitmap(128 - mountainOffset, mountainYOffset,OverworldBG,64,16,1);
  }
  else {
    for (uint8_t a = 0; a < 196; a += 96) {
      arduboy.drawBitmap( a - (this->cameraX / 4) % 96, mountainYOffset+20, UndergroundBricks, 37, 24, 1);
    }
  }
  for (int x = this->cameraX / TileSize; x < (this->cameraX / TileSize) + 17; x++) {
    for (int y = this->cameraY / TileSize; y < (this->cameraY / TileSize) + 9; y++) {
      if (this->level.CheckTile(x, y)) {
        arduboy.drawBitmap(x*TileSize - this->cameraX, y*TileSize - this->cameraY, tMask, TileSize, TileSize, BLACK);
        arduboy.drawBitmap(x*TileSize - this->cameraX, y*TileSize - this->cameraY, tBrick, TileSize, TileSize, WHITE);
      }
      else {
        const uint8_t * tempTile = 0;
        switch (this->level.CheckObject(x,y)) {
          case STMushBlock:
          case STQBlock:        tempTile = tQBlock; break;
          case STBQBlock:       tempTile = tBQBlock; break;
          case STPipeCapLeft:   tempTile = tPipeCapLeft; break;
          case STPipeCapRight:  tempTile = tPipeCapRight; break;
          case STTopPipeCapLeft:   tempTile = tTopPipeCapLeft; break;
          case STTopPipeCapRight:  tempTile = tTopPipeCapRight; break;
          case STPipeLeft:      tempTile = tPipeLeft; break;
          case STPipeRight:     tempTile = tPipeRight; break;
        }
        if (tempTile) {
          arduboy.drawBitmap(x*TileSize - this->cameraX, y*TileSize - this->cameraY, tMask, TileSize, TileSize, BLACK);
          arduboy.drawBitmap(x*TileSize - this->cameraX, y*TileSize - this->cameraY, tempTile, TileSize, TileSize, WHITE);
        }
      }
    }
  }
}

void SquarioGame::drawPlayer(Arduboy2 &arduboy) {
  this->player.draw(arduboy);
  if (this->health) {
    for (uint8_t a = 0; a < this->health; a++) {
      arduboy.drawFastHLine(this->player.x + 1 - this->cameraX, this->player.y+11-(a*2)-this->cameraY, 6, WHITE);
      arduboy.drawFastHLine(this->player.x + 1 - this->cameraX, this->player.y+10-(a*2)-this->cameraY, 6, WHITE);
    }
  }  
}

void SquarioGame::draw(Arduboy2 &arduboy) {

  switch (this->event) {

    case EventType::Death_Init:
    case EventType::Death:
    case EventType::Playing:   
      drawMap(arduboy); 
      drawMobs(arduboy); 
      if (!(this->eventCounter % 2)) drawPlayer(arduboy);
      break;

    case EventType::PipeDrop:
    case EventType::PipeRise:  
      drawPlayer(arduboy); 
      drawMap(arduboy); 
      drawMobs(arduboy); 
      break;

    default: break;

  }

}

void SquarioGame::addMob(const uint8_t *dataPointer, int x, int y) {

  int Distances[ SpriteCap ];
  for (uint8_t a = 0; a < SpriteCap; a++) {
    if (!this->mobs[a].Active) { this->mobs[a].Activate(dataPointer, x, y); return; }
    Distances[a] = this->player.x - this->mobs[a].x;
    if (Distances[a] < 0) Distances[a] *= -1;
  }
  uint8_t Distance = Distances[0];
  uint8_t Candidate = 0;
  for (uint8_t a = 1; a < SpriteCap; a++) {
    if (Distances[a] > Distance) {
      Candidate = a;
      Distance = Distances[a];
    }
  }
  this->mobs[Candidate].Activate(dataPointer, x, y);
  
}
