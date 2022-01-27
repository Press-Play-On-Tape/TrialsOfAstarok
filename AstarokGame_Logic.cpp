#include "src/utils/Arduboy2Ext.h"
#include "AstarokGame.h"

AstarokGame::AstarokGame(Arduboy2Ext *arduboy, ArduboyTones *sound) {

    this->player.game = this;
    this->level.game = this;
    this->arduboy = arduboy;
    this->sound = sound;

    for (AISprite &mobileObject : this->mobs) {

        mobileObject.game = this;
        mobileObject.arduboy = arduboy;

    }

    for (InteractiveObject &interactiveObject : this->level.objects) {

        interactiveObject.game = this;
        interactiveObject.arduboy = arduboy;

    }

}

void AstarokGame::newGame() {

    this->score = 0;
    this->distancePoints = 0;
    //this->coins = 0;
    this->lives = 1;
    this->mapNumber = 1;
    this->player.init(Data::Astarok, Images::SpriteImages[ObjectTypes::Player], Images::SpriteMasks[ObjectTypes::Player], 24, spawnY());

    startLevel();

}

void AstarokGame::startLevel() {

    this->sound->tones(Sounds::NewLevel);

    this->level.newMap();
    this->player.init(Data::Astarok, Images::SpriteImages[ObjectTypes::Player], Images::SpriteMasks[ObjectTypes::Player], 24, spawnY());

    while (this->player.isFalling()) {
        this->player.move();
    }

    adjustCamera();

    this->event = EventType::StartLevel;
    this->eventCounter = Constants::EventCounter_LevelStart;

}

uint8_t AstarokGame::spawnY() {

    if (this->mapNumber % 2) return 0;
    else return 88;

}

void AstarokGame::processButtons() {

    uint8_t justPressed = arduboy->justPressedButtons();
    uint8_t pressed = arduboy->pressedButtons();

    uint8_t MaxSpeed = 3; //SJHarduboy->pressed(A_BUTTON) ? 4 : 3;

    if (!(pressed & LEFT_BUTTON) && !(pressed & RIGHT_BUTTON)) {
        if (this->player.vx > 0) this->player.vx--;
        if (this->player.vx < 0) this->player.vx++;
    }

    if (pressed & LEFT_BUTTON)  { 
    
        this->player.facing = Direction::Left;
        this->player.vx--; 
    
        if (this->player.vx < MaxSpeed * -1) {
            this->player.vx = MaxSpeed * -1; 
        }

    }

    if (pressed & RIGHT_BUTTON) { 

        this->player.facing = Direction::Right;
        this->player.vx++; 

        if (this->player.vx > MaxSpeed) {
            this->player.vx = MaxSpeed; 
        }
    }

    if (justPressed & B_BUTTON) {

        if (!this->player.isFalling()) {
            if (this->player.jump()) {
                this->sound->tones(Sounds::Jump);
            }
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
    //     this->player.x = 2200;
    // }

}

void AstarokGame::adjustCamera() {

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

void AstarokGame::cycle(GameState &gameState) {

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

            Rect playerRect = { player.getLeftX(), player.getTopY(), player.getWidth() - 2, player.getHeight() };
            Rect objRect = { obj.x * Constants::TileSize, obj.y * Constants::TileSize, Constants::TileSize, Constants::TileSize };

            switch (obj.getType()) {

                case ObjectTypes::Chest_Closed:
                    objRect.width = 20;
                    break;

                case ObjectTypes::AboveGroundExit:
                case ObjectTypes::UnderGroundExit:
                    objRect.x = (obj.x * Constants::TileSize) - 2;
                    playerRect.width = 12;
                    break;

                default: break;

            }
            
            if (arduboy->collide(playerRect, objRect)) {
                    
                switch (obj.getType()) {

                    case ObjectTypes::AboveGroundExit:
                    case ObjectTypes::UnderGroundExit:

                        //if (obj.collide(player.x + player.getWidth(), player.y)) {
                            //this->SFX = Sounds::SFX_Pipe;
                            this->event = EventType::LevelExit;
                            this->eventCounter = 0;
                        //}

                        break;

                    case ObjectTypes::Coin:

                        //if (obj.collide(player.x + player.getWidth(), player.y)) {
                            obj.deactivate();
                            this->score += Constants::Points_Coin;
                            this->sound->tones(Sounds::Coin);
                        //}

                        break;

                    case ObjectTypes::Chest_Closed:
                        {

                            uint8_t pressed = this->arduboy->justPressedButtons();

                            if (pressed & A_BUTTON) {
                                
                                obj.type = ObjectTypes::Chest_Open;
                                gameState = GameState::Game_Mini;

                                this->chest.x = obj.x;
                                this->chest.y = (obj.y * Constants::TileSize) - camera.y;
                                this->ballDirection = Direction::Left;
                                this->ballX = 15;
                                this->ballIdx = 5;
                                this->ballDelay = 4;

                            }

                        }

                        break;

                    default: break;

                }

            }

        }

    }



    for (AISprite &obj : this->mobs) {

        // Adjust explode counter if explostion is in action ..

        obj.updateExplosion();

        if (obj.getActive()) {

            switch (obj.getType()) {

                case ObjectTypes::Fireball:
                    obj.move();
                    break;

                default:

                    if (obj.y > mapPixelHeight) {
                        obj.deactivate(true);
                    }

                    obj.think();

                    if (obj.y > mapPixelHeight) {
                        obj.deactivate(true);
                    }

                    break;

            }


            // Have we touched another object?

            if (obj.getActive() && testCollision(&player, &obj)) {
                    
                uint8_t type = obj.getType();

                switch (type) {

                    case ObjectTypes::Mushroom:
                        obj.deactivate(true);
                        this->score += Constants::Points_Mushroom;
                        if (this->lives < 3) this->lives++;
                        break;

                    case ObjectTypes::Coin:
                        obj.deactivate(false);
                        this->score += Constants::Points_Coin;
                        this->sound->tones(Sounds::Coin);
                        break;
                        
                    default: break;

                }

                if (obj.getActive()) { // May have been deativated just above (ie. a mushroom) ..
                    
                    if (this->player.isFalling()) { // And therefore landing on top of an object

                        switch (type) {

                            case ObjectTypes::Fireball:

                                #ifndef NO_DEATH
                                if (this->eventCounter == 0) {
                                    if (this->lives > 0) this->lives--; 
                                    this->event = EventType::Death_Init; 
                                    this->eventCounter = Constants::EventCounter_Death;   
                                    this->sound->tones(Sounds::Dying);
                                    obj.deactivate(true);
                                }
                                #endif

                                break;

                            default:

                                obj.deactivate(true);
                                this->score += Constants::Points_Skill;
                                this->sound->tones(Sounds::LandOnTop);


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
                            if (this->lives > 0) this->lives--; 
                            this->event = EventType::Death_Init; 
                            this->eventCounter = Constants::EventCounter_Death;
                            this->sound->tones(Sounds::Dying);
                            #endif
                        }

                    }

                }

            }

        }

    }

    switch (this->event) {

        case EventType::Playing:

            if (this->player.y > mapPixelHeight) { 
                if (this->lives > 0) this->lives--; 
                this->event = EventType::Death_Init; 
                this->sound->tones(Sounds::Dying);
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

bool AstarokGame::testCollision(Sprite * player, AISprite * sprite) {

    Rect rect1 = { player->getLeftX(), player->getTopY(), player->getWidth(), player->getHeight()};
    Rect rect2 = { sprite->getLeftX(), sprite->getTopY(), sprite->getWidth(), sprite->getHeight()};

    return arduboy->collide(rect1, rect2);

}

void AstarokGame::die(GameState &gameState) {

    if (this->lives > 0) {

        this->player.init(Data::Astarok, Images::SpriteImages[ObjectTypes::Player], Images::SpriteMasks[ObjectTypes::Player], 10, spawnY());
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

        uint8_t justPressed = arduboy->justPressedButtons();

        if ((justPressed & A_BUTTON) || (justPressed & B_BUTTON)) {
            gameState = GameState::HighScore_Check;
            this->event = EventType::Off;
        }

    }

}

uint8_t AstarokGame::addMob(const uint8_t *data, const uint8_t * img, const uint8_t * mask, int x, uint8_t y, uint8_t maxHeight) {

    int distances[Constants::SpriteCap];

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (!this->mobs[a].getActive()) {

            this->mobs[a].activate(data, img, mask, x, y); 

            if (maxHeight != 255) {
                this->mobs[a].maxHeight = maxHeight * Constants::TileSize;
            }

            return a; 
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

    return candidate;

}

// uint8_t AstarokGame::getSpareMobCount() {

//     uint8_t numberOfSpares = 0;

//     for (AISprite &mobileObject : this->mobs) {   

//         if (!mobileObject.getActive()) { 
//             numberOfSpares++; 
//         }

//     }

//     return numberOfSpares;

// }

void AstarokGame::playMiniGame(GameState &gameState) {

    const uint8_t increments[] = { 1, 2, 3, 3, 3, 3, 3, 3, 3, 2, 1 }; // 27
    
    uint8_t justPressed = this->arduboy->justPressedButtons();
    uint8_t pressed = this->arduboy->pressedButtons();

    uint8_t y = (this->chest.y < 20 ? this->chest.y + 15 : this->chest.y - 15);
    uint8_t x = (this->chest.x * Constants::TileSize) - 24;

    Sprites::drawExternalMask(x, y, Images::Frame, Images::Frame_Mask, 0, 0);
    Sprites::drawSelfMasked(x + this->ballX + 4, y + 5, Images::Ball, 0);


    switch (this->ballDirection) {

        case Direction::Left:
            this->ballX = this->ballX - increments[ballIdx];
            this->ballIdx--;
            if (this->ballIdx == 0) {
                this->ballDirection = Direction::Right;
            }
            break;

        case Direction::Right:
            this->ballX = this->ballX + increments[ballIdx];
            this->ballIdx++;
            if (this->ballIdx == 10) {
                this->ballDirection = Direction::Left;
            }
            break;
        
        default:
            break;

    }

    if (this->ballDelay == 0) {
            
        if (justPressed & A_BUTTON && this->ballIdx == 4 && this->ballDirection != Direction::None) {

            // if (random(0, 10) == 0) {
                this->ballDirection = Direction::None;
            // }
            // else {
            //     Serial.println("Bump 1");

            // }

        } 
        else if (pressed & A_BUTTON && this->ballDirection != Direction::None) {
            this->ballDirection = Direction::None;
        }
        else if (justPressed & A_BUTTON && this->ballDirection == Direction::None) {
            
            gameState = GameState::Game_Play;

            if (this->ballIdx >= 4 && ballIdx <= 6) {
                this->addMob(Data::Mushroom, Images::Mushroom, Images::Mushroom_Mask, this->chest.x + random(-2, 3), 4);
            }
            else {

                for (uint8_t i = 0; i < 5; i++) {

                    this->addMob(Data::Coin, Images::Coins, Images::Coins_Masks, this->chest.x + random(-1, 2), 4);//this->chest.y - 5);

                }

            }

        }

    }
    else {
        this->ballDelay--;
    }

}
