#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Constants.h"

#include "Room.h"
#include "InteractiveObject.h"

class SquarioGame;

class Map {

    public:
        void newMap();
        void loadMap();
        void generateRoom(uint8_t roomNum);
        void addObject(uint8_t type, int x, int y);
        void handleObject (int x, int y);
        uint8_t checkObject(int x, int y);
        bool isTile(int x, int y);
        void addSign(int x, int y);
        void addExit(ObjectTypes exitType, int x, int y);

        int16_t minXPixel();
        int16_t maxXPixel();
        int16_t maxYPixel();
        int16_t minXTile();
        int16_t maxXTile();
        int16_t maxYTile();

        SquarioGame           * game;
        Room                  rooms[Constants::MapRooms];
        InteractiveObject     objects[Constants::MapObjects];
        int16_t               ObjectIndex;
        int16_t               RandomChance;
        int16_t               firstRoom, lastRoom, mapHeight, lastLoadLocation, SpawnBarrier;
};