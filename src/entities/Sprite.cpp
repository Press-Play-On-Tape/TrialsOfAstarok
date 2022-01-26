#include "Sprite.h"
#include "../../AstarokGame.h"

uint8_t Sprite::getFlags()      { return pgm_read_byte(this->spriteData + SpriteFlags); }
uint8_t Sprite::getType()       { return pgm_read_byte(this->spriteData + SpriteType); }

int16_t Sprite::getRightX()     { return this->x + this->getWidth() - 1; }
int16_t Sprite::getTopY()       { return this->y; }
int16_t Sprite::getBottomY()    { return this->y + this->getHeight() - 1; }
int16_t Sprite::getLeftX()      { return this->x; }


uint8_t Sprite::getWidth() { 

    if (this->getType() == ObjectTypes::Player) {
        return 12; 
    }
    else {
        return pgm_read_byte(&this->spriteImg[0]); 
    }

}

uint8_t Sprite::getHeight() { 

    if (this->getType() == ObjectTypes::Player) {
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
    this->facing = Direction::Right;

}

void Sprite::clear() {

    this->spriteData = nullptr;
    this->x = -1;
    this->y = -1;
    this->vx = 0;
    this->vy = 0;

}

uint8_t Sprite::collide(int16_t tX, int16_t tY) {

    int16_t nX = tX / Constants::TileSize;
    int16_t nY = tY / Constants::TileSize;

    // if (this->getLeftX() + this->getWidth() >= (tX / Constants::TileSize) * Constants::TileSize) {

        if (this->game->level.isTile(nX, nY)) return 0xFF;  

    //}

    uint8_t object = this->game->level.checkObject(nX, nY);

    switch (object) {

        case ObjectTypes::Triangleo ... ObjectTypes::UnderGroundExit:
        case ObjectTypes::Fireball:
            return object;

        case ObjectTypes::Sign:
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
                if (this->collide(x - 1, y + (tY * Constants::TileSize)) || this->collide(x - 1, y + ((tY + 1) * Constants::TileSize) - 1)) {
                    return true;
                }
                break;

            case Right:
                if (this->collide(x + this->getWidth(), y + (tY * Constants::TileSize)) || this->collide(x + this->getWidth(), y + ((tY + 1) * Constants::TileSize) - 1)) {
                    return true;
                }
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

    if (this->getType() == ObjectTypes::Player) {

        if (this->vx == 0 && this->vy == 0) {
            if (this->game->arduboy->getFrameCount(6) == 0) {
               this->frame = (this->frame + 1) % 3;
            }
         }

    }
 
    switch (this->getType()) {

        case ObjectTypes::Fireball:

            if (this->vy == Constants::Fireball_NotMoving && random(0, 40) == 0) {
                this->vy = Constants::Fireball_StartPos;
            }

            if (this->vy != Constants::Fireball_NotMoving) {

                if (this->y - 32 > this->maxHeight) {

                    this->y = this->y + (this->vy / 4);

                }
                else {
                
                    this->y = this->y + (this->vy / 4);                
                    this->vy++;

                }
            }

            if (this->y > this->yInit) {
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
// Serial.println("Down");
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
                    if (this->collisionCheckY(Direction::Up)) { 
                        headCollision(); 
                        vy = 0; 
// Serial.println("Not going Up");
                        break; 
                    }
                    else {
// Serial.println("Going Up");
                        y--;
                    }
                }
            }

            if (vx > 0) { // Right

                for (int a = 0; a < vx; a++) {

                    if (this->getRightX() > this->game->level.maxXPixel()) break;

                    if (this->collisionCheckX(Direction::Right)) {
                        vx = 0;
// Serial.println("No Right");
                        break;
                    }
                    else { 

// Serial.println("Right");
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
                        vx = 0;
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
        this->vy = -5; 
        this->jumpBoost = 0;
        return true; 
    }

    return false;

}

void Sprite::headCollision() {

  if (this->getFlags() & 0b10) return;

  byte leftCheck = this->collide(x, y - 1);
  byte rightCheck = this->collide(this->getRightX(), y - 1);

  if (leftCheck == ObjectTypes::QBlock || leftCheck == ObjectTypes::MushBlock) {
    this->game->level.handleObject(x / Constants::TileSize, (y - 1) / Constants::TileSize);
  }
  if (rightCheck == ObjectTypes::QBlock || rightCheck == ObjectTypes::MushBlock) {
    this->game->level.handleObject(this->getRightX() / Constants::TileSize, (y - 1) / Constants::TileSize);
  }
  
}

void Sprite::draw() {

    switch (this->getType()) {

       case ObjectTypes::Player:

            if (this->isFalling()) {
                Sprites::drawExternalMask(x - this->game->camera.x - 2, y - 1 - this->game->camera.y, Images::Player_Jumping, Images::Player_Jumping_Mask, this->facing == Direction::Right, this->facing == Direction::Right);
            }
            else if (this->vx == 0 && this->vy == 0) {
                Sprites::drawExternalMask(x - this->game->camera.x - 2, y - 1 - this->game->camera.y, pgm_read_word_near(&Images::Player_Idle[this->getFrame()]), pgm_read_word_near(&Images::Player_Idle_Masks[this->getFrame()]), this->facing == Direction::Right, this->facing == Direction::Right);
            }
            else {
                Sprites::drawExternalMask(x - this->game->camera.x - 2, y - 1 - this->game->camera.y, pgm_read_word_near(&Images::Player_Images[this->getFrame()]), pgm_read_word_near(&Images::Player_Masks[this->getFrame()]), this->facing == Direction::Right, this->facing == Direction::Right);
            }
            break;

        case ObjectTypes::Smileo:
        case ObjectTypes::Triangleo:
            Sprites::drawExternalMask(x - this->game->camera.x, y - this->game->camera.y, this->spriteImg, this->spriteMask, this->facing == Direction::Right, this->facing == Direction::Right);
            break;

        case ObjectTypes::Fireball:
            Sprites::drawExternalMask(x - this->game->camera.x, y - this->game->camera.y, this->spriteImg, this->spriteMask, this->vy > 0, this->vy > 0);
            break;

        default:

            if (this->game->mapNumber % 2 == MapLevel::AboveGround) {
                Sprites::drawErase(x - this->game->camera.x, y -  this->game->camera.y, this->spriteImg, 0);
            }
            else {
                Sprites::drawExternalMask(x - this->game->camera.x, y - this->game->camera.y, this->spriteImg, this->spriteMask, 0, 0);
            }

            break;
    }

}

uint8_t Sprite::getFrame() {

    if (this->vx == 0 && this->vy == 0 && this->frame >= 3) this->frame = 0;
    return this->frame;

}