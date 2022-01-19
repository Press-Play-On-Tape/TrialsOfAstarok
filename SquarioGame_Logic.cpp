#include "src/utils/Arduboy2Ext.h"
#include "Squariogame.h"

SquarioGame::SquarioGame() {

  this->player.Game = this;
  this->level.Game = this;
  
  for (uint8_t a = 0; a < Constants::SpriteCap; a++) {
    this->mobs[a].Game = this;
  }

  for (uint8_t a = 0; a < Constants::MapObjects; a++) {
    this->level.objects[a].Game = this;
  }
}
void SquarioGame::newGame() {

// Serial.println("newGame() Start");
  this->health = 0;
  this->score = 0;
  this->distancePoints = 0;
  this->coins = 0;
  this->lives = 1;
  this->mapNumber = 1;
  this->player.init(Data::SmallSquario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], 10, spawnY());
  startLevel();
// Serial.println("newGame() End");

}

void SquarioGame::startLevel() {

// Serial.println("startLevel() Start");
  this->event = EventType::Playing;
  SFX = NULL;
// Serial.println("startLevel() 1");
  this->level.newMap();
// Serial.println("startLevel() 2");
  while (this->player.isFalling()) {
// Serial.println("startLevel() 3");
    this->player.move();
  }
// Serial.println("startLevel() 4");
  adjustCamera();

// Serial.println("startLevel() End");

}

uint8_t SquarioGame::spawnY() {
  if (this->mapNumber % 2) return 0;
  else return 88;
}
void SquarioGame::processButtons(Arduboy2 &arduboy) {

  uint8_t MaxSpeed = 3; //SJHarduboy.pressed(A_BUTTON) ? 4 : 3;
// Serial.println(this->player.x);

  if (!arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)) {
    if (this->player.vx > 0) this->player.vx--;
    if (this->player.vx < 0) this->player.vx++;
  }

  if (arduboy.pressed(LEFT_BUTTON))  { 
    if (!this->player.isFalling()) {
      this->player.facing = Direction::Left;
    }
    this->player.vx--; 
    if (this->player.vx < MaxSpeed * -1) this->player.vx = MaxSpeed * -1; 
  }

  if (arduboy.pressed(RIGHT_BUTTON)) { 
    if (!this->player.isFalling()) {
      this->player.facing = Direction::Right;
    }
    this->player.vx++; 
    if (this->player.vx > MaxSpeed) this->player.vx = MaxSpeed; 
  }

  if (arduboy.pressed(B_BUTTON)) {
    if (this->player.jump()) SFX = Sounds::SFX_Jump;
  }

  if (arduboy.pressed(A_BUTTON)) {
    this->player.x = 1000;
  }

  if (arduboy.pressed(DOWN_BUTTON)) this->player.duck();

}
void SquarioGame::adjustCamera() {
  int MaxX = this->level.MaxXPixel() - WIDTH;
  int MaxY = this->level.MaxYPixel() - HEIGHT;
  int MinX = this->level.MinXPixel();

  // Serial.print("adjustCamera ");
  // Serial.print(this->cameraX);
  // Serial.print(" to ");
  this->cameraX = this->player.x - (WIDTH/2); // Center X on player


  #ifdef ORIG_GAME_TILESIZE_8
  this->cameraY = this->player.y - 8;
  #else
  this->cameraY = this->player.y - 24;
  #endif
  // Serial.println(this->cameraX);

  // Constrain for map edges
  if (this->cameraY > MaxY) this->cameraY = MaxY;
  if (this->cameraX > MaxX) this->cameraX = MaxX;
  if (this->cameraX < MinX) this->cameraX = MinX;

  // Reload map data
    this->level.loadMap();

}

void SquarioGame::cycle(Arduboy2 &arduboy, GameState &gameState) {

// Serial.print(this->score);
// Serial.print(" ");
// Serial.print(this->player.x / Constants::TileSize);
// Serial.print(" ");
// Serial.print(this->totalScore);
// Serial.println(" ");

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
      this->player.move();
      adjustCamera();
      break;

    default: break;

  }


  // Have we touched an end of level thingy?
// Serial.print("level.objects ");
  for (uint8_t a = 0; a < Constants::MapObjects; a++) {

    uint8_t type = this->level.objects[a].type;
//     Serial.print(type);
// Serial.print(" (");
//     Serial.print(this->level.objects[a].x);
// Serial.print(") ");


    switch (type) {

          case ObjectTypes::STAboveGroundExit:
          case ObjectTypes::STUnderGroundExit:

            // ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));
            // if (testCollision(arduboy, &player, &this->mobs[a])) {
// Serial.print("Test for coll ");
// Serial.print(player.x);
// Serial.print(", ");
// Serial.println(this->level.objects[a].x);
            if (this->level.objects[a].collide(player.x + player.getWidth(), player.y)) {
              this->SFX = Sounds::SFX_Pipe;
              this->event = EventType::LevelExit;
              this->eventCounter = 0;
            }
            break;

    }

  }
// Serial.println("");


  for (uint8_t a = 0; a < Constants::SpriteCap; a++) {
    if (this->mobs[a].getActive()) {
      this->mobs[a].think();
      if (this->mobs[a].y > MapPixelHeight) {
        // Serial.print("this->mobs[a].y > MapPixelHeight ");
        // Serial.print(this->mobs[a].y);
        // Serial.print(", ");
        // Serial.println(MapPixelHeight);
        this->mobs[a].deactivate();
      }
      else if (testCollision(arduboy, &player, &this->mobs[a])) {
        
        uint8_t type = this->mobs[a].getType();

        switch (type) {

          case ObjectTypes::STMushroom:
            this->mobs[a].deactivate();
            this->score += Constants::Points_Mushroom;
            SFX = Sounds::SFX_Mushroom;
            if (this->player.getType() == ObjectTypes::STSquario) {
              this->player.init(Data::STBigSquario, Images::SpriteImages[ObjectTypes::STBigSquario], Images::SpriteMasks[ObjectTypes::STBigSquario], this->player.x, this->player.y-8);
            }
            else if (this->health < 5) this->health++;
            break;

        }

        if (this->player.isFalling()) {
          this->mobs[a].deactivate();
          this->score += Constants::Points_Skill;
          SFX = Sounds::SFX_Hit;
          //SJH if (arduboy.pressed(A_BUTTON)) { this->player.vy = -10;}
          //SJH else { this->player.vy = -4; } 
          this->player.vy = -4; //SJH         
        }
        else if (!this->eventCounter) {
          if (this->health > 0) this->health--;
          else {
            if (this->player.getHeight() == Constants::TileSize) { 
              //SJH this->lives--; 
              //SJH this->event = EventType::Death_Init; 
            }
            if (this->player.getHeight() > Constants::TileSize) {
              this->player.init(Data::SmallSquario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], this->player.x, this->player.y+8);
              SFX = Sounds::SFX_Hit;
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
        this->event = EventType::Death_Init; 
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
        this->distancePoints += this->player.x / Constants::TileSize;
        this->mapNumber++;
        this->player.x = 10;
        this->player.y = spawnY();
        // Serial.println("startLevel 2");
        startLevel();
      }
      break;

    case EventType::LevelExit:
      this->eventCounter = 0;
      this->distancePoints += this->player.x / Constants::TileSize;
      this->mapNumber++;
      this->player.x = 10;
      this->player.y = spawnY();
      startLevel();
    

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
    this->player.init(Data::SmallSquario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], 10, spawnY());
    startLevel();
  }
  else {

    if (this->event == EventType::Death_Init) {
      this->totalScore = this->score;
      this->distancePoints += this->player.x / Constants::TileSize;
      this->totalScore += this->distancePoints;
      this->event = EventType::Death;
    }

    // Move to High this->score mode .. 
    if (arduboy.justPressed(A_BUTTON)) {
      gameState = GameState::HighScore_Check;
      this->event = EventType::Off;
    }

  }

}

void SquarioGame::addMob(const uint8_t *data, const uint8_t * img, const uint8_t * mask, int x, int y) {

  int Distances[ Constants::SpriteCap ];
  for (uint8_t a = 0; a < Constants::SpriteCap; a++) {
    if (!this->mobs[a].getActive()) { this->mobs[a].activate(data, img, mask, x, y); return; }
    Distances[a] = this->player.x - this->mobs[a].x;
    if (Distances[a] < 0) Distances[a] *= -1;
  }
  uint8_t Distance = Distances[0];
  uint8_t Candidate = 0;
  for (uint8_t a = 1; a < Constants::SpriteCap; a++) {
    if (Distances[a] > Distance) {
      Candidate = a;
      Distance = Distances[a];
    }
  }
  this->mobs[Candidate].activate(data, img, mask, x, y);
  
}
