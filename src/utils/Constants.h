#pragma once

#include "Arduboy2Ext.h"

#define _DEBUG

#define _ORIG_GAME_MUSHROOM

namespace Constants {

    constexpr uint8_t TileSize          = 12;
    constexpr uint8_t GameSeeds         = 4;
    constexpr uint8_t MinLevelWidth     = 12;

    constexpr uint8_t RoomWidth         = 8;//16;
    constexpr uint8_t RoomHeight        = 16;
    constexpr uint8_t RoomBytes         = (RoomHeight/8) * RoomWidth;

    constexpr uint8_t MapRooms          = 3; // SJH was 3
    constexpr uint8_t MapObjects        = 30;
    constexpr uint8_t SpriteCap         = 10;

    constexpr uint8_t Points_Mushroom    = 100;
    constexpr uint8_t Points_Skill       = 20;

    constexpr uint16_t EEPROM_Start_C1   = EEPROM_STORAGE_SPACE_START + 500;
    constexpr uint16_t EEPROM_Start_C2   = EEPROM_Start_C1 + 1;
    constexpr uint16_t EEPROM_Seeds      = EEPROM_Start_C2 + 1;
    constexpr uint16_t EEPROM_Scores     = EEPROM_Seeds + 5;
    constexpr uint8_t  EEPROM_No_Slot    = 255;
    constexpr uint8_t NumberOfScores     = 3;

}
