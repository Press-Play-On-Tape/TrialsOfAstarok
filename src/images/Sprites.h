#pragma once

#include "../utils/Constants.h"

namespace Images {

    const uint8_t PROGMEM Mushroom[] = {
    12, 12,
    0x7c, 0x82, 0x01, 0x11, 0x09, 0x02, 0x02, 0x01, 0x01, 0x01, 0x82, 0x7c, 
    0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Mushroom_Mask[] = {
    0x7c, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0x7c, 
    0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Smileo[] = {
    12, 12,
    0xf8, 0x04, 0xfa, 0xcd, 0xbd, 0xcd, 0xfd, 0x7d, 0x7d, 0x3a, 0x04, 0xf8, 
    0x01, 0x02, 0x05, 0x08, 0x09, 0x08, 0x09, 0x08, 0x0a, 0x05, 0x02, 0x01, 

    0xf8, 0x04, 0x3a, 0x7d, 0x7d, 0xfd, 0xcd, 0xbd, 0xcd, 0xfa, 0x04, 0xf8, 
    0x01, 0x02, 0x05, 0x0a, 0x08, 0x09, 0x08, 0x09, 0x08, 0x05, 0x02, 0x01, 
    };

    const uint8_t PROGMEM Smileo_Mask[] = {
    0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 
    0x01, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x01, 

    0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 
    0x01, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x01, 
    };

    const uint8_t PROGMEM Starmano[] = {
    12, 12,
    0x80, 0xd0, 0x70, 0x6e, 0x9b, 0x4f, 0x4f, 0x9b, 0x6e, 0x70, 0xd0, 0xc0, 
    0x01, 0x00, 0x08, 0x06, 0x01, 0x07, 0x07, 0x01, 0x06, 0x08, 0x00, 0x01, 
    };

    const uint8_t PROGMEM Starmano_Mask[] = {
    0x80, 0xd0, 0x70, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x70, 0xd0, 0xc0, 
    0x01, 0x00, 0x08, 0x06, 0x01, 0x07, 0x07, 0x01, 0x06, 0x08, 0x00, 0x01, 
    };

    const uint8_t PROGMEM Triangleo[] = {
    12, 12,
    0x00, 0x00, 0xc0, 0x98, 0x6c, 0x5c, 0x6c, 0xbc, 0xd8, 0xc0, 0x00, 0x00, 
    0x00, 0x07, 0x09, 0x06, 0x09, 0x01, 0x03, 0x09, 0x06, 0x09, 0x07, 0x00, 

    0x00, 0x00, 0xc0, 0xd8, 0xbc, 0x6c, 0x5c, 0x6c, 0x98, 0xc0, 0x00, 0x00, 
    0x00, 0x07, 0x09, 0x06, 0x09, 0x03, 0x01, 0x09, 0x06, 0x09, 0x07, 0x00, 
    };

    const uint8_t PROGMEM Triangleo_Mask[] = {
    0x00, 0xc0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0xc0, 0x00, 
    0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 

    0x00, 0xc0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0xc0, 0x00, 
    0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 
    };

    const uint8_t PROGMEM Bolt[] = {
    16, 16,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x50, 0x28, 0x06, 0x01, 0x41, 0xe2, 0x22, 0x14, 0x0c, 0x08, 
    0x80, 0x40, 0x70, 0x28, 0x25, 0x12, 0x08, 0x0e, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Bolt_Mask[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xd0, 0xf8, 0xfe, 0xff, 0xff, 0xfe, 0x3e, 0x1c, 0x0c, 0x08, 
    0x80, 0x40, 0x70, 0x38, 0x3d, 0x1f, 0x0f, 0x0f, 0x07, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Tile_Brick[] = {
    12, 12,
    0x07, 0x03, 0x87, 0xc3, 0xe2, 0x44, 0xa3, 0x47, 0xa3, 0x47, 0xa7, 0x03, // Underground
    0x05, 0x02, 0x04, 0x01, 0x00, 0x04, 0x02, 0x05, 0x02, 0x05, 0x02, 0x00, 

    0x19, 0xa6, 0xbe, 0x5e, 0x3e, 0xfe, 0x7e, 0x7e, 0x6e, 0x76, 0xee, 0x01,  // Outside
    0x04, 0x02, 0x02, 0x04, 0x04, 0x08, 0x05, 0x0d, 0x05, 0x0d, 0x04, 0x00, 
    };

    const uint8_t PROGMEM Tile_QBlock[] = {
    8, 8,
    0xff, 0x81, 0x85, 0xb5, 0x95, 0x9d, 0x81, 0xff, 
    };

    const uint8_t PROGMEM Tile_BQBlock[] = {
    8, 8,
    0xff, 0x81, 0xa5, 0x81, 0x81, 0xa5, 0x81, 0xff, 
    };

    const uint8_t PROGMEM Tile_Mask[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
    };

    const uint8_t PROGMEM Fireball[] = {
    12, 14,
    0x00, 0x70, 0x8c, 0x02, 0x09, 0x1d, 0x1d, 0x09, 0x02, 0x8c, 0x70, 0x00,  // Up
    0x00, 0x00, 0x01, 0x0a, 0x01, 0x16, 0x02, 0x01, 0x0a, 0x01, 0x00, 0x00, 

    0x00, 0x80, 0x60, 0x14, 0x20, 0x1a, 0x10, 0x20, 0x14, 0x60, 0x80, 0x00,  // Down
    0x00, 0x03, 0x0c, 0x10, 0x24, 0x2e, 0x2e, 0x24, 0x10, 0x0c, 0x03, 0x00, 
    };

    const uint8_t PROGMEM Fireball_Mask[] = {
    0x00, 0x70, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x70, 0x00, 
    0x00, 0x00, 0x01, 0x0b, 0x01, 0x17, 0x03, 0x01, 0x0b, 0x01, 0x00, 0x00, 

    0x00, 0x80, 0xe0, 0xf4, 0xe0, 0xfa, 0xf0, 0xe0, 0xf4, 0xe0, 0x80, 0x00, 
    0x00, 0x03, 0x0f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 
    };

    const uint8_t * const SpriteImages[] PROGMEM = { 
        Triangleo,                  // 0 - not used
        Triangleo,                  // 1
        Starmano,                   // 2
        Smileo,                     // 3
        Bolt,                       // 4
        Mushroom,                   // 5
        Tile_QBlock,                // 6
        Tile_BQBlock,               // 7
        Tile_QBlock,                // 8
        Tile_Brick,                 // 9
    };

    const uint8_t * const SpriteMasks[] PROGMEM =  { 
        Triangleo_Mask, 
        Triangleo_Mask, 
        Starmano_Mask, 
        Smileo_Mask, 
        Bolt_Mask, 
        Mushroom_Mask,
        Tile_Mask, 
        Tile_Mask, 
        Tile_Mask, 
        Tile_Mask, 
    };

// enum ObjectTypes {
//   Player = 0,  // Sprites
//   STTriangleo,
//   STStarmano,
//   STSmileo,
//   STBolt,

//   STMushroom = 5,

//   STQBlock,  // Interactive Tiles
//   STBQBlock,
//   STMushBlock,
//   STBricks = 9,
//   STAboveGroundExit,
//   STUnderGroundExit,
//   STSign,
//   STFireball,
// };

};
