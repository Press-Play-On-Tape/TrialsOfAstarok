#include "Map.h"
#include "../../SquarioGame.h"



void Map::generateRoom(uint8_t roomNum) {
   
    randomSeed(this->game->seeds[(this->game->mapNumber + roomNum) % Constants::GameSeeds] * this->game->mapNumber + roomNum);
    rooms[roomNum % Constants::MapRooms].clearRoom();
    uint8_t floor = random(Constants::RoomHeight - 3, Constants::RoomHeight);

    uint8_t upperPlatform_X = Constants::NoPlatform;
    uint8_t upperPlatform_Row = 0;
    uint8_t upperPlatform_Floor = 0;
    int8_t gap = 0;
    int tSpawnBarrier = roomNum * Constants::RoomWidth;


    // If this is the first room on a level, add the sign ..

    if (roomNum == 0) {
        addSign(1, floor - 1);
    }

    for (int x = 0; x < Constants::RoomWidth; x++) {

        // Should we launch an upper platform?

        if (upperPlatform_X == Constants::NoPlatform) {

            if (x >= 3 && x < 9 && random(0, 8) == 0) {
                upperPlatform_X = 0;
                upperPlatform_Floor = floor;
                upperPlatform_Row = random(0, 3);
            }

        }

        if (upperPlatform_X != Constants::NoPlatform) {

            if (Constants::UpperPlatform[(upperPlatform_Row * 4) + upperPlatform_X] > 0) {
                rooms[roomNum % Constants::MapRooms].setTile(x, upperPlatform_Floor - Constants::UpperPlatform[(upperPlatform_Row * 4) + upperPlatform_X]);
            }

        }

        if (gap == 0) {


            // Fill the map data from the current floor to the bottom of the map ..

            for (int b = floor; b < Constants::RoomHeight; b++) {
                rooms[roomNum % Constants::MapRooms].setTile(x, b);
            }

            if (roomNum && (roomNum < this->lastRoom)) {

                if (upperPlatform_X == Constants::NoPlatform) {
                        
                    if (random(10) == 0) { 
                        gap = random(2,5);
                    }
                    else if (random(5) == 0) {
                        if (!random(1) && floor < Constants::RoomHeight - 1) floor++;
                        else floor--;
                    }

                }

                if (tSpawnBarrier > SpawnBarrier) {

                    if (!random(8)) {

                        uint8_t yLocation = floor - 2;

                        if (upperPlatform_X > 0 && upperPlatform_X < 3 && random(0, 2) == 0) {

                            yLocation = upperPlatform_Floor - Constants::UpperPlatform[(upperPlatform_Row * 4) + upperPlatform_X] - 1;
                            this->game->addMob(Data::Triangleo, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, yLocation);

                        }
                        else {

                            switch (random(28)) {

                                case 0 ... 9:
                                    this->game->addMob(Data::Triangleo, Images::SpriteImages[ObjectTypes::STTriangleo], Images::SpriteMasks[ObjectTypes::STTriangleo], tSpawnBarrier + x, yLocation);
                                    break;

                                case 10 ... 15:
                                    this->game->addMob(Data::Smileo, Images::SpriteImages[ObjectTypes::STSmileo], Images::SpriteMasks[ObjectTypes::STSmileo], tSpawnBarrier + x, yLocation);
                                    break;

                                case 16 ... 18:
                                    if (roomNum > 8) {
                                        this->game->addMob(Data::Starmano, Images::SpriteImages[ObjectTypes::STStarmano], Images::SpriteMasks[ObjectTypes::STStarmano], tSpawnBarrier + x, yLocation);
                                    }
                                    break;

                                case 19 ... 25:
                                    this->addObject(ObjectTypes::STCoin, tSpawnBarrier + x, floor - 1);
                                    break;

                                default:
                                    if (roomNum > 8) {
                                        this->game->addMob(Data::Bolt, Images::SpriteImages[ObjectTypes::STBolt], Images::SpriteMasks[ObjectTypes::STBolt], tSpawnBarrier + x, 2);
                                    }
                                    break;

                            }

                        }

                    }

                    #ifdef ORIG_GAME_MUSHROOM
                    if (!random(16) && !gap && floor > ceiling + 5 && x != Constants::RoomWidth - 1) {

                        int y = random(max(floor - 7, ceiling + 2), floor - 3);

                        if (!random(4)) {
                            addObject (STMushBlock, tSpawnBarrier + x, y);
                        }
                        else {
                            addObject(STQBlock, tSpawnBarrier + x, y);
                        }

                    }
                    #endif

                }

            }

        }
        else {
            
            gap--;


            if (random(0, 5) == 0) {

                this->game->addMob(Data::Fireball, Images::Fireball, Images::Fireball_Mask, tSpawnBarrier + x, 16, floor - random(1, 4));

            }

        }


        // Increase upper platform counter if a platform is being rendered ..

        if (upperPlatform_X != Constants::NoPlatform) {

            upperPlatform_X++;

            if (upperPlatform_X == 4) {
                upperPlatform_X = Constants::NoPlatform;
            }

        }

    }


    // If this is the last room in a map, then add a pipe so we can leave ..

    if (roomNum == this->lastRoom) {

        addExit(this->game->mapNumber % 2 == MapLevel::AboveGround ? ObjectTypes::STAboveGroundExit : ObjectTypes::STUnderGroundExit, maxXTile() - 2, floor - 1);

    }

    if (tSpawnBarrier > SpawnBarrier) SpawnBarrier = tSpawnBarrier;

}

void Map::addExit(ObjectTypes exitType, int x, int y) {

  addObject(exitType, x, y);

}

void Map::addSign(int x, int y) {

  addObject(ObjectTypes::STSign,  x,   y);

}

void Map::addObject(ObjectTypes type, int tX, int tY) {

  if (checkObject(tX, tY)) {
    return;
  }
  else {
   
    objects[this->objectIndex].x = tX;
    objects[this->objectIndex].y = tY;
    objects[this->objectIndex].type = type;
    this->objectIndex++;

    if (this->objectIndex == Constants::MapObjects) this->objectIndex = 0;

  }

}

void Map::handleObject(int x, int y) {

    for (int a = 0; a < Constants::MapObjects; a++) {

        if (objects[a].x == x && objects[a].y == y) {

            switch (objects[a].type) {

                case STQBlock: 
                    this->game->coins++;
                    if (!(this->game->coins % 20)) {
                        this->game->lives++;
                        this->game->SFX = Sounds::SFX_Life;
                    }
                    else {
                        this->game->SFX = Sounds::SFX_Coin;
                    }
                    objects[a].type = STBQBlock;
                    break;

            // case STMushBlock:
            //   this->game->addMob(Data::Mushroom, Images::SpriteImages[ObjectTypes::STMushroom], Images::SpriteMasks[ObjectTypes::STMushroom], x, y - 1);
            //   objects[a].type = STBQBlock; break;

            default:
                break;

            }

        }

    }

}


void Map::newMap() {

    // Reset Variables

    this->objectIndex = 0; 
    this->lastLoadLocation = 0; 
    this->firstRoom = 0; 
    SpawnBarrier = 0;

    for (uint8_t a = 0; a < Constants::MapObjects; a++) objects[a].deactivate();
    for (uint8_t a = 0; a < Constants::SpriteCap; a++) this->game->mobs[a].deactivate();

    // Seed for level length

    randomSeed(this->game->seeds[ this->game->mapNumber % Constants::GameSeeds ] * this->game->mapNumber);
    int lowEnd = Constants::MinLevelWidth + random(this->game->mapNumber);
    int highEnd = random(lowEnd, lowEnd + this->game->mapNumber);
    this->lastRoom = random(lowEnd, highEnd);

    for (uint8_t a = 0; a < Constants::MapRooms; a++) {
        generateRoom(a);
    }

}

void Map::loadMap() {

    int roomBeforePlayerIsIn = (this->game->player.x / (Constants::RoomWidth*Constants::TileSize)) - 1;

    if (roomBeforePlayerIsIn < 0) roomBeforePlayerIsIn = 0;

    if (roomBeforePlayerIsIn > this->firstRoom) {
        this->firstRoom = roomBeforePlayerIsIn;
        generateRoom(roomBeforePlayerIsIn + Constants::MapRooms - 1);
    }

}

bool Map::isTile(int x, int y) {

  int room = (x / Constants::RoomWidth) % Constants::MapRooms;
  return rooms[room].readTile(x % Constants::RoomWidth, y);

}


// Return first object found at coordinates x, y ..

uint8_t Map::checkObject(int x, int y) {

    if (y < 0) return 0;

    for (InteractiveObject &obj : this->objects) {
        if ((obj.x == x) && (obj.y == y)) return obj.type;
    }

    return 0;
}

int16_t Map::minXPixel() { return this->firstRoom * Constants::RoomWidth * Constants::TileSize; }
int16_t Map::maxXPixel() { return ((this->lastRoom + 1) * Constants::RoomWidth * Constants::TileSize) - 1; }
int16_t Map::maxYPixel() { return ((this->mapHeight + 1) * Constants::RoomHeight * Constants::TileSize) - 1; }
int16_t Map::minXTile() { return this->firstRoom * Constants::RoomWidth; }
int16_t Map::maxXTile() { return ((this->lastRoom + 1) * Constants::RoomWidth) - 1; }
int16_t Map::maxYTile() { return ((this->mapHeight + 1) * Constants::RoomHeight) - 1; }
