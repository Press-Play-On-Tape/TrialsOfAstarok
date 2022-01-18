#pragma once

#include "../utils/Enums.h"

namespace Data {

    PROGMEM const uint8_t SmallSquario[] {
         ObjectTypes::STSquario, 0, 0, 0,    // Flags, Speed, AI Setting
    };

    PROGMEM const uint8_t STBigSquario[] {
        ObjectTypes::STSquario, 0, 0, 0,     // Flags, Speed, AI Setting
    };

    PROGMEM const uint8_t Triangleo[] {
        ObjectTypes::STTriangleo, 
        0b10,       // Flags
        1, 0b11,    // Speed, AI Setting
    };

    PROGMEM const uint8_t Starmano[] {
        ObjectTypes::STStarmano, 
        0b10,       // Flags
        2, 0b1111,  // Speed, AI Setting
    };

    PROGMEM const uint8_t Smileo[] {
        ObjectTypes::STSmileo, 
        0b10,       // Flags
        2, 0b1,     // Speed, AI Setting
    };

    PROGMEM const uint8_t Mushroom[] {
        ObjectTypes::STMushroom, 
        0b10,       // Flags
        1, 0b1,     // Speed, AI Setting
    };

    PROGMEM const uint8_t Bolt[] {
        ObjectTypes::STBolt, 
        0b11,         // Flags
        2, 0,         // Speed, AI Setting
    };

};