#pragma once

#include "../utils/Enums.h"

#define AI_SEEK        0b00000100
#define AI_DETECT_JUMP 0b00001000
#define AI_DETECT_WALL 0b00000001
#define AI_DETECT_GAP  0b00000010

namespace Data {

    PROGMEM const uint8_t Squario[] {
         ObjectTypes::STSquario, 0, 0, 0,    // Flags, Speed, AI Setting
    };

    PROGMEM const uint8_t Triangleo[] {
        ObjectTypes::STTriangleo, 
        0b10,       // Flags
        1, AI_DETECT_WALL | AI_DETECT_GAP,    // Speed, AI Setting (0b11)
    };

    PROGMEM const uint8_t Starmano[] {
        ObjectTypes::STStarmano, 
        0b10,       // Flags
        2, AI_SEEK | AI_DETECT_JUMP | AI_DETECT_WALL | AI_DETECT_GAP,  // Speed, AI Setting (0b1111)
    };

    PROGMEM const uint8_t Smileo[] {
        ObjectTypes::STSmileo, 
        0b10,       // Flags
        2, AI_DETECT_WALL,     // Speed, AI Setting (0b1)
    };

    PROGMEM const uint8_t Mushroom[] {
        ObjectTypes::STMushroom, 
        0b10,       // Flags
        1, AI_DETECT_WALL,     // Speed, AI Setting (0b1)
    };

    PROGMEM const uint8_t Bolt[] {
        ObjectTypes::STBolt, 
        0b11,         // Flags
        2, 0,         // Speed, AI Setting
    };

    PROGMEM const uint8_t Fireball[] {
        ObjectTypes::STFireball, 
        0b00,         // Flags
        0, 0,         // Speed, AI Setting
    };

    PROGMEM const uint8_t Coin[] {
        ObjectTypes::STCoin, 
        0b00,         // Flags
        0, 0,         // Speed, AI Setting
    };

};