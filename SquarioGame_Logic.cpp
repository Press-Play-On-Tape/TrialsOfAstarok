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
    this->eventCounter = Constants::EventCounter_LevelStart;

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
    
        this->player.facing = Direction::Left;
        this->player.vx--; 
    
        if (this->player.vx < MaxSpeed * -1) {
            this->player.vx = MaxSpeed * -1; 
        }

    }

    if (arduboy->pressed(RIGHT_BUTTON)) { 

        this->player.facing = Direction::Right;
        this->player.vx++; 

        if (this->player.vx > MaxSpeed) {
            this->player.vx = MaxSpeed; 
        }
    }

    if (arduboy->justPressed(B_BUTTON)) {

        if (!this->player.isFalling()) {
            if (this->player.jump()) SFX = Sounds::SFX_Jump;
        }

    }

    if (arduboy->pressed(B_BUTTON)) {

        if (this->player.isFalling()) {

            if (this->player.jumpBoost < 6) {

                this->player.jumpBoost++;

                if (this->player.jumpBoost % 2 == 0) this->player.vy-=2;

            }
            else if (this->player.jumpBoost < 12) {

                this->player.jumpBoost++;

                if (this->player.jumpBoost % 2 == 0) this->player.vy--;

            }

        }

    }

    // if (arduboy->pressed(A_BUTTON)) {
    //     this->player.x = 1000;
    // }

}

void SquarioGame::adjustCamera() {

    int16_t maxX = this->level.maxXPixel() - WIDTH;
    int16_t maxY = this->level.maxYPixel() - HEIGHT;
    int16_t minX = this->level.minXPixel();

    this->camera.x = this->player.x - (WIDTH /2); // Center X on player
    this->camera.y = this->player.y - 9;


    // Constrain for map edges ..

    if (this->camera.y > maxY) this->camera.y = maxY;
    if (this->camera.x > maxX) this->camera.x = maxX;
    if (this->camera.x < minX) this->camera.x = minX;


    // Reload map data ..

    this->level.loadMap();

}

void SquarioGame::cycle(GameState &gameState) {

    int mapPixelHeight = this->level.maxYPixel();
    this->processButtons();

    switch (this->event) {

        case EventType::Death_Init:
        case EventType::Death:

            switch (this->eventCounter) {

                case Constants::EventCounter_Death - 2 ... Constants::EventCounter_Death:  // bump up before going down
                    this->player.y--;
                    break;

                case 1 ... Constants::EventCounter_Death - 3:
                    this->player.y+=2;
                    break;

            }

            if (this->player.y > mapPixelHeight) {
                this->eventCounter = 0;
            }
            else {
                this->eventCounter--;
            }

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

            switch (obj.getType()) {

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


    // Have we touched another object?

    for (AISprite &obj : this->mobs) {

        if (obj.getActive()) {

            switch (obj.getType()) {

                case ObjectTypes::STFireball:
                    obj.move();
                    break;

                default:

                    if (obj.y > mapPixelHeight) {
                        obj.deactivate();
                    }

                    obj.think();

                    if (obj.y > mapPixelHeight) {
                        obj.deactivate();
                    }

                    break;

            }

            // if (obj.y > mapPixelHeight) {
            //     obj.deactivate();
            // }

            // obj.think();

            // if (obj.y > mapPixelHeight) {
            //     obj.deactivate();
            // }
            // else if (testCollision(&player, &obj)) {
            if (obj.getActive() && testCollision(&player, &obj)) {
                    
                uint8_t type = obj.getType();

                switch (type) {

                    case ObjectTypes::STMushroom:
                        obj.deactivate();
                        this->score += Constants::Points_Mushroom;
                        SFX = Sounds::SFX_Mushroom;
                        break;

                    default: break;

                }

                if (this->player.isFalling()) { // And therefore landing on top of an object

                    switch (type) {

                        case ObjectTypes::STFireball:

                            #ifndef NO_DEATH
                            if (this->eventCounter == 0) {
                                this->lives--; 
                                this->event = EventType::Death_Init; 
                                this->eventCounter = Constants::EventCounter_Death;   
                            }
                            #endif

                            break;

                        default:
                            
                            obj.deactivate();
                            this->score += Constants::Points_Skill;
                            SFX = Sounds::SFX_Hit;


                            // Get a bounce if we are pressing 'A' ..

                            if (arduboy->pressed(B_BUTTON)) { 
                                this->player.vy = -8;
                            }
                            else { 
                                this->player.vy = -3; 
                            } 

                            break;

                    }

                }
                else if (this->eventCounter == 0) {

                    if (this->player.getHeight() == Constants::TileSize) { 
                        #ifndef NO_DEATH
                        this->lives--; 
                        this->event = EventType::Death_Init; 
                        #endif
                    }

                    this->eventCounter = Constants::EventCounter_Death;

                }
            }
        }
    }

    switch (this->event) {

        case EventType::Playing:

            if (this->player.y > mapPixelHeight) { 
                this->lives--; 
                this->event = EventType::Death_Init; 
                this->eventCounter = Constants::EventCounter_Death - 3; 
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

    Rect rect1 = { player->getLeftX(), player->getTopY(), player->getWidth(), player->getHeight()};
    Rect rect2 = { sprite->getLeftX(), sprite->getTopY(), sprite->getWidth(), sprite->getHeight()};

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

        if (arduboy->justPressed(A_BUTTON) || arduboy->justPressed(B_BUTTON)) {
            gameState = GameState::HighScore_Check;
            this->event = EventType::Off;
        }

    }

}

void SquarioGame::addMob(const uint8_t *data, const uint8_t * img, const uint8_t * mask, int x, uint8_t y, uint8_t maxHeight) {

    int distances[Constants::SpriteCap];

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (!this->mobs[a].getActive()) {

            this->mobs[a].activate(data, img, mask, x, y); 

            if (maxHeight != 255) {
                this->mobs[a].maxHeight = maxHeight * Constants::TileSize;
            }

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

    if (maxHeight != 255) {
        this->mobs[candidate].maxHeight = maxHeight * Constants::TileSize;
    }

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