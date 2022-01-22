#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Constants.h"

class Room {

    public:
        void clearRoom();
        void setTile(int x, int y);
        void clearTile(int x, int y);
        bool readTile(int x, int y);

        uint8_t data[Constants::RoomBytes];

};