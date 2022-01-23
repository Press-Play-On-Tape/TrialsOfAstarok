#include "src/utils/Arduboy2Ext.h"
#include "SquarioGame.h"

SquarioGame::SquarioGame(Arduboy2Ext *arduboy) {

    this->player.game = this;
    this->level.game = this;
    this->arduboy = arduboy;

    for (AISprite &mobileObject : this->mobs) {

        mobileObject.game = this;
        mobileObject.arduboy = arduboy;

    }

    for (InteractiveObject &interactiveObject : this->level.objects) {

        interactiveObject.game = this;
        interactiveObject.arduboy = arduboy;

    }

}

void SquarioGame::newGame() {

    this->score = 0;
    this->distancePoints = 0;
    this->coins = 0;
    this->lives = 1;
    this->mapNumber = 1;
    this->player.init(Data::Squario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], 24, spawnY());

    startLevel();

}

void SquarioGame::startLevel() {

    SFX = NULL;
    this->level.newMap();
    this->player.init(Data::Squario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], 24, spawnY());

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

void SquarioGame::processButtons() {

    uint8_t MaxSpeed = 3; //SJHarduboy->pressed(A_BUTTON) ? 4 : 3;

    if (!arduboy->pressed(LEFT_BUTTON) && !arduboy->pressed(RIGHT_BUTTON)) {
        if (this->player.vx > 0) this->player.vx--;
        if (this->player.vx < 0) this->player.vx++;
    }

    if (arduboy->pressed(LEFT_BUTTON))  { 
    
        if (!this->player.isFalling()) {
            this->player.facing = Direction::Left;
        }

        this->player.vx--; 
    
        if (this->player.vx < MaxSpeed * -1) {
            this->player.vx = MaxSpeed * -1; 
        }

    }

    if (arduboy->pressed(RIGHT_BUTTON)) { 

        if (!this->player.isFalling()) {
            this->player.facing = Direction::Right;
        }

        this->player.vx++; 

        if (this->player.vx > MaxSpeed) {
            this->player.vx = MaxSpeed; 
        }
    }

    if (arduboy->pressed(B_BUTTON)) {
        if (this->player.jump()) SFX = Sounds::SFX_Jump;
    }

    // if (arduboy->pressed(A_BUTTON)) {
    //     this->player.x = 1000;
    // }

}

void SquarioGame::adjustCamera() {

    int16_t maxX = this->level.maxXPixel() - WIDTH;
    int16_t maxY = this->level.maxYPixel() - HEIGHT;
    int16_t minX = this->level.minXPixel();

    this->cameraX = this->player.x - (WIDTH /2); // Center X on player
    this->cameraY = this->player.y - 9;


    // Constrain for map edges ..

    if (this->cameraY > maxY) this->cameraY = maxY;
    if (this->cameraX > maxX) this->cameraX = maxX;
    if (this->cameraX < minX) this->cameraX = minX;


    // Reload map data ..

    this->level.loadMap();

}

void SquarioGame::cycle(GameState &gameState) {

    int MapPixelHeight = this->level.maxYPixel();
    processButtons();

    switch (this->event) {

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

    for (InteractiveObject &obj : this->level.objects) {

        if (obj.x >= 0) {

            switch (obj.type) {

                case ObjectTypes::STAboveGroundExit:
                case ObjectTypes::STUnderGroundExit:

                    if (obj.collide(player.x + player.getWidth(), player.y)) {
                        this->SFX = Sounds::SFX_Pipe;
                        this->event = EventType::LevelExit;
                        this->eventCounter = 0;
                    }

                    break;

            }

        }

    }


    for (AISprite &obj : this->mobs) {

        if (obj.getActive()) {

            if (obj.y > MapPixelHeight) {
                obj.deactivate();
            }

            obj.think();

            if (obj.y > MapPixelHeight) {
                obj.deactivate();
            }
            else if (testCollision(&player, &obj)) {
                    
                uint8_t type = obj.getType();

                switch (type) {

                    case ObjectTypes::STMushroom:
                        obj.deactivate();
                        this->score += Constants::Points_Mushroom;
                        SFX = Sounds::SFX_Mushroom;
                        break;

                }

                if (this->player.isFalling()) {

                    obj.deactivate();
                    this->score += Constants::Points_Skill;
                    SFX = Sounds::SFX_Hit;
                    //SJH if (arduboy->pressed(A_BUTTON)) { this->player.vy = -10;}
                    //SJH else { this->player.vy = -4; } 
                    this->player.vy = -4; //SJH         

                }
                else if (this->eventCounter == 0) {

                    if (this->player.getHeight() == Constants::TileSize) { 
                    //SJH this->lives--; 
                    //SJH this->event = EventType::Death_Init; 
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
                die(gameState);
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

bool SquarioGame::testCollision(Sprite * player, AISprite * sprite) {

    Rect rect1 = { player->x + 2, player->y, player->getWidth() - 2, player->getHeight()};
    Rect rect2 = { sprite->x, sprite->y, sprite->getWidth(), sprite->getHeight()};

    return arduboy->collide(rect1, rect2);

}

void SquarioGame::die(GameState &gameState) {

    if (this->lives > 0) {

        this->player.init(Data::Squario, Images::SpriteImages[ObjectTypes::STSquario], Images::SpriteMasks[ObjectTypes::STSquario], 10, spawnY());
        startLevel();

    }
    else {

        if (this->event == EventType::Death_Init) {
            this->totalScore = this->score;
            this->distancePoints += this->player.x / Constants::TileSize;
            this->totalScore += this->distancePoints;
            this->event = EventType::Death;
        }

        // Move to High Score mode .. 
        if (arduboy->justPressed(A_BUTTON)) {
            gameState = GameState::HighScore_Check;
            this->event = EventType::Off;
        }

    }

}

void SquarioGame::addMob(const uint8_t *data, const uint8_t * img, const uint8_t * mask, int x, int y) {

    int distances[Constants::SpriteCap];

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (!this->mobs[a].getActive()) { this->mobs[a].activate(data, img, mask, x, y); 
            return; 
        }

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

    return;

}

uint8_t SquarioGame::getSpareMobCount() {

    uint8_t numberOfSpares = 0;

    for (AISprite &mobileObject : this->mobs) {   

        if (!mobileObject.getActive()) { 
            numberOfSpares++; 
        }

    }

    return numberOfSpares;

}