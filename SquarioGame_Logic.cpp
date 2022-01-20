#include "src/utils/Arduboy2Ext.h"
#include "SquarioGame.h"

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

    this->health = 0;
    this->score = 0;
    this->distancePoints = 0;
    this->coins = 0;
    this->lives = 1;
    this->mapNumber = 1;
    this->player.init(Data::SmallSquario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], 10, spawnY());
    startLevel();

}

void SquarioGame::startLevel() {

    SFX = NULL;
    this->level.newMap();
    while (this->player.isFalling()) {
        this->player.move();
    }

    adjustCamera();

    this->event = EventType::StartLevel;
    this->eventCounter = 28;

}

uint8_t SquarioGame::spawnY() {
    if (this->mapNumber % 2) return 0;
    else return 88;
}

void SquarioGame::processButtons(Arduboy2 &arduboy) {

    uint8_t MaxSpeed = 3; //SJHarduboy.pressed(A_BUTTON) ? 4 : 3;

    if (!arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)) {
        if (this->player.vx > 0) this->player.vx--;
        if (this->player.vx < 0) this->player.vx++;
    }

    if (arduboy.pressed(LEFT_BUTTON))  { 
    
        if (!this->player.isFalling()) {
            this->player.facing = Direction::Left;
        }

        this->player.vx--; 
    
        if (this->player.vx < MaxSpeed * -1) {
            this->player.vx = MaxSpeed * -1; 
        }

    }

    if (arduboy.pressed(RIGHT_BUTTON)) { 

        if (!this->player.isFalling()) {
            this->player.facing = Direction::Right;
        }

        this->player.vx++; 

        if (this->player.vx > MaxSpeed) {
            this->player.vx = MaxSpeed; 
        }
    }

    if (arduboy.pressed(B_BUTTON)) {
        if (this->player.jump()) SFX = Sounds::SFX_Jump;
    }

    if (arduboy.pressed(A_BUTTON)) {
        this->player.x = 1000;
    }

}

void SquarioGame::adjustCamera() {

    int MaxX = this->level.MaxXPixel() - WIDTH;
    int MaxY = this->level.MaxYPixel() - HEIGHT;
    int MinX = this->level.MinXPixel();

    this->cameraX = this->player.x - (WIDTH /2); // Center X on player
    this->cameraY = this->player.y - 24;

    // Constrain for map edges
    if (this->cameraY > MaxY) this->cameraY = MaxY;
    if (this->cameraX > MaxX) this->cameraX = MaxX;
    if (this->cameraX < MinX) this->cameraX = MinX;

    // Reload map data
    this->level.loadMap();

}

void SquarioGame::cycle(Arduboy2 &arduboy, GameState &gameState) {

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

        case EventType::StartLevel:
            if (this->eventCounter > 0) {
                this->eventCounter--;
                if (this->eventCounter == 0) {
                    this->event = EventType::Playing;
                }
            }
            break;

        default: break;

    }


  // Have we touched an end of level thingy?

    for (uint8_t a = 0; a < Constants::MapObjects; a++) {

        uint8_t type = this->level.objects[a].type;

        switch (type) {

            case ObjectTypes::STAboveGroundExit:
            case ObjectTypes::STUnderGroundExit:

                if (this->level.objects[a].collide(player.x + player.getWidth(), player.y)) {
                    this->SFX = Sounds::SFX_Pipe;
                    this->event = EventType::LevelExit;
                    this->eventCounter = 0;
                }
                break;

        }

    }


    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (this->mobs[a].getActive()) {

            this->mobs[a].think();

            if (this->mobs[a].y > MapPixelHeight) {
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

                    if (this->health > 0) {

                        this->health--;

                    }
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

    int distances[Constants::SpriteCap];

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {
        if (!this->mobs[a].getActive()) { this->mobs[a].activate(data, img, mask, x, y); return; }
        distances[a] = this->player.x - this->mobs[a].x;
        if (distances[a] < 0) distances[a] *= -1;
    }

    uint8_t distance = distances[0];
    uint8_t candidate = 0;

    for (uint8_t a = 1; a < Constants::SpriteCap; a++) {
        if (distances[a] > distance) {
            candidate = a;
            distance = distances[a];
        }
    }

    this->mobs[candidate].activate(data, img, mask, x, y);

}
