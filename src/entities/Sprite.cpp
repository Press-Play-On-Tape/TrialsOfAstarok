#include "Sprite.h"
#include "../../SquarioGame.h"

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
            if (this->game->arduboy->getFrameCount(6) == 0) {
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