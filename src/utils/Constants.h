#pragma once

#include "Arduboy2Ext.h"

#define _DEBUG
#define _NO_DEATH
#define _ORIG_GAME_MUSHROOM

namespace Constants {

    constexpr uint8_t TileSize          = 12;
    constexpr uint8_t GameSeeds         = 4;
    constexpr uint8_t MinLevelWidth     = 12;

    constexpr uint8_t RoomWidth         = 16;
    constexpr uint8_t RoomHeight        = 16;
    
    constexpr uint8_t RoomBytes         = RoomWidth;

    constexpr uint8_t MapRooms          = 3; // SJH was 3
    constexpr uint8_t MapObjects        = 30;
    constexpr uint8_t SpriteCap         = 10;

    constexpr uint8_t Points_Mushroom    = 100;
    constexpr uint8_t Points_Skill       = 20;
    constexpr uint8_t Points_Coin        = 20;

    constexpr uint16_t EEPROM_Start_C1   = EEPROM_STORAGE_SPACE_START + 500;
    constexpr uint16_t EEPROM_Start_C2   = EEPROM_Start_C1 + 1;
    constexpr uint16_t EEPROM_Sounds     = EEPROM_Start_C2 + 1;
    constexpr uint16_t EEPROM_Seeds      = EEPROM_Sounds + 1;
    constexpr uint16_t EEPROM_Scores     = EEPROM_Seeds + 5;
    constexpr uint8_t  EEPROM_No_Slot    = 255;
    constexpr uint8_t NumberOfScores     = 3;

    constexpr uint8_t Fireball_NotMoving = 127;
    constexpr int8_t Fireball_StartPos = -20;

    constexpr uint8_t EventCounter_Death = 50;
    constexpr uint8_t EventCounter_LevelStart = 28;

    constexpr uint8_t NoPlatform = 255;

    // constexpr uint8_t UpperPlatform[] = { 3, 3, 3, 3, 3, 3,
    //                                       3, 4, 4, 0, 0, 0,                                             
    //                                       3, 4, 4, 3, 0, 0, 
    //                                       3, 3, 4, 4, 0, 0,
    //                                       };

    constexpr uint8_t UpperPlatform[] = { 3, 3, 3, 3, 3, 3,  
                                          3, 3, 3, 3, 3, 3,  
                                          3, 3, 3, 3, 3, 3,  
                                          3, 3, 3, 3, 3, 3, 
                                          };
    

}
