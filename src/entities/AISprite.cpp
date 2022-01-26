#include "AISprite.h"

#include "../data/SpriteData.h"
#include "../../AstarokGame.h"

uint8_t AISprite::getSpeed()            { return pgm_read_byte(this->spriteData + SpriteSpeed); }
uint8_t AISprite::getIntelligence()     { return pgm_read_byte(this->spriteData + SpriteIntelligence); }

void AISprite::activate(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY) {

    this->active = true;
    this->facing = Direction::Left;

    init(data, img, mask, tX * Constants::TileSize, tY * Constants::TileSize);

    if (this->getType() == ObjectTypes::Bolt) {
        vx = -4;
        vy = 2;
    }

    if (this->getType() == ObjectTypes::Fireball) {
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

    if (this->getIntelligence() & AI_SEEK) {
        this->seek();
        if (this->getIntelligence() & AI_DETECT_JUMP) this->detectJump();
    }
    else {
        if (this->getIntelligence() & AI_DETECT_WALL) this->detectWall();
        if (this->getIntelligence() & AI_DETECT_GAP) this->detectGap();
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
            this->facing = Direction::Right; 
            vx = 0; 
            return; 
        }
        else {
            vx = this->getSpeed() * -1;
        }

    }

    if (this->facing == Direction::Right) {

        if (this->collisionCheckX(Direction::Right)) { 
            this->facing = Direction::Left; 
            vx = 0; 
            return; 
        }
        else {
            vx = this->getSpeed();
        }

    }

}

void AISprite::detectGap() {

    if (this->facing == Direction::Left) {

        if (!this->collide(x - 1, this->getBottomY() + 1)) { 
            this->facing = Direction::Right; 
            vx = 0; 
            return; 
        }
        else {
            vx = this->getSpeed() * -1;
        }

    }

    if (this->facing == Direction::Right) {

        if (!this->collide(this->getRightX() + 1, this->getBottomY() + 1)) { 
            this->facing = Direction::Left; 
            vx = 0; 
            return; 
        }
        else {
            vx = this->getSpeed();
        }

    }

}
