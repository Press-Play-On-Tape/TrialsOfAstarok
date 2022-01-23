#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"

class SquarioGame;

class Sprite {

    protected:
        const uint8_t       * spriteData;
        const uint8_t       * spriteImg;
        const uint8_t       * spriteMask;

    public:

        void init(const uint8_t * data, const uint8_t * img, const uint8_t * mask, int tX, int tY);
        bool isFalling();
        void move();
        bool jump();
        void draw();

        uint8_t getWidth();
        uint8_t getHeight();
        int16_t getRightX();
        int16_t getBottomY();

        uint8_t getFlags();
        uint8_t getType();
        uint8_t getFrame();

        int16_t               x, y, vx, vy, xInit, yInit;
        int16_t               currentFrame;
        Direction             facing;
        SquarioGame           * game;
        Sprite                * relatedSprite;
        Arduboy2Ext           * arduboy;

    private:
        uint8_t               frame;

    protected:
        void clear();
        void applyGravity();
        uint8_t collide(int16_t tX, int16_t tY);
        bool collisionCheckX(Direction direction);
        bool collisionCheckY(Direction direction);
        void headCollision();

};