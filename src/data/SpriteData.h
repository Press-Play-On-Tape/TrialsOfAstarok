#pragma once

#include "../utils/Enums.h"

#define AI_SEEK        0b00000100
#define AI_DETECT_JUMP 0b00001000
#define AI_DETECT_WALL 0b00000001
#define AI_DETECT_GAP  0b00000010

namespace Data {

    PROGMEM const uint8_t Astarok[] {
         ObjectTypes::Player, 0, 0, 0,    // Flags, Speed, AI Setting
    };

    PROGMEM const uint8_t Spider[] {
        ObjectTypes::Spider, 
        0b10,       // Flags
        1, AI_DETECT_WALL | AI_DETECT_GAP,    // Speed, AI Setting (0b11)
    };

    PROGMEM const uint8_t Starman[] {
        ObjectTypes::Starman, 
        0b10,       // Flags
        2, AI_SEEK | AI_DETECT_JUMP | AI_DETECT_WALL | AI_DETECT_GAP,  // Speed, AI Setting (0b1111)
    };

    PROGMEM const uint8_t Skull[] {
        ObjectTypes::Skull, 
        0b10,       // Flags
        2, AI_DETECT_WALL,     // Speed, AI Setting (0b1)
    };

    PROGMEM const uint8_t Health[] {
        ObjectTypes::Health, 
        0b10,       // Flags
        1, 0,     // Speed, AI Setting (0b1)
    };

    PROGMEM const uint8_t Bolt[] {
        ObjectTypes::Bolt, 
        0b11,         // Flags
        2, 0,         // Speed, AI Setting
    };

    PROGMEM const uint8_t Fireball[] {
        ObjectTypes::Fireball, 
        0b00,         // Flags
        0, 0,         // Speed, AI Setting
    };

    PROGMEM const uint8_t Coin[] {
        ObjectTypes::Coin, 
        0b00,         // Flags
        0, 0,         // Speed, AI Setting
    };

};