#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Constants.h"
#include "../../SquarioGame.h"

class InteractiveObject {

    public:
        int16_t             x, y;
        uint8_t             type;
        SquarioGame         * game;
        Arduboy2Ext         * arduboy;

        uint8_t collide(int16_t tX, int16_t tY);
        void deactivate();
};