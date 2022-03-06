#pragma once

#include "../utils/Constants.h"

namespace Images {

    const uint8_t PROGMEM Health[] = {
        12, 16,  // 12x12 px image 
        
        0x7C, 0x7C,  // ▓░░░░░▓▓ Image  ▓░░░░░▓▓ +Mask  ·░░░░░·· Sprite
        0x82, 0xFE,  // ░▓▓▓▓▓░▓        ░░░░░░░▓        ░▓▓▓▓▓░·
        0x01, 0xFF,  // ▓▓▓▓▓▓▓░        ░░░░░░░░        ▓▓▓▓▓▓▓░
        0x11, 0xFF,  // ▓▓▓░▓▓▓░        ░░░░░░░░        ▓▓▓░▓▓▓░
        0x09, 0xFF,  // ▓▓▓▓░▓▓░        ░░░░░░░░        ▓▓▓▓░▓▓░
        0x02, 0xFE,  // ▓▓▓▓▓▓░▓        ░░░░░░░▓        ▓▓▓▓▓▓░·
        0x02, 0xFE,  // ▓▓▓▓▓▓░▓        ░░░░░░░▓        ▓▓▓▓▓▓░·
        0x01, 0xFF,  // ▓▓▓▓▓▓▓░        ░░░░░░░░        ▓▓▓▓▓▓▓░
        0x01, 0xFF,  // ▓▓▓▓▓▓▓░        ░░░░░░░░        ▓▓▓▓▓▓▓░
        0x01, 0xFF,  // ▓▓▓▓▓▓▓░        ░░░░░░░░        ▓▓▓▓▓▓▓░
        0x82, 0xFE,  // ░▓▓▓▓▓░▓        ░░░░░░░▓        ░▓▓▓▓▓░·
        0x7C, 0x7C,  // ▓░░░░░▓▓        ▓░░░░░▓▓        ·░░░░░··
        
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓        ········
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓        ········
        0x01, 0x01,  // ▓▓▓▓▓▓▓░        ▓▓▓▓▓▓▓░        ·······░
        0x02, 0x03,  // ▓▓▓▓▓▓░▓        ▓▓▓▓▓▓░░        ······░▓
        0x04, 0x07,  // ▓▓▓▓▓░▓▓        ▓▓▓▓▓░░░        ·····░▓▓
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x04, 0x07,  // ▓▓▓▓▓░▓▓        ▓▓▓▓▓░░░        ·····░▓▓
        0x02, 0x03,  // ▓▓▓▓▓▓░▓        ▓▓▓▓▓▓░░        ······░▓
        0x01, 0x01,  // ▓▓▓▓▓▓▓░        ▓▓▓▓▓▓▓░        ·······░
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓        ········
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓        ········ 
    };

    const uint8_t PROGMEM Skull[] = {
        12, 16, // 12x12 px image 

        // Frame 0 - Left facing
        0xF8, 0xF8,  // ░░░░░▓▓▓ Image  ░░░░░▓▓▓ +Mask  ░░░░░··· Sprite
        0x04, 0xFC,  // ▓▓▓▓▓░▓▓        ░░░░░░▓▓        ▓▓▓▓▓░··
        0xFA, 0xFE,  // ░░░░░▓░▓        ░░░░░░░▓        ░░░░░▓░·
        0xCD, 0xFF,  // ░░▓▓░░▓░        ░░░░░░░░        ░░▓▓░░▓░
        0xBD, 0xFF,  // ░▓░░░░▓░        ░░░░░░░░        ░▓░░░░▓░
        0xCD, 0xFF,  // ░░▓▓░░▓░        ░░░░░░░░        ░░▓▓░░▓░
        0xFD, 0xFF,  // ░░░░░░▓░        ░░░░░░░░        ░░░░░░▓░
        0x7D, 0xFF,  // ▓░░░░░▓░        ░░░░░░░░        ▓░░░░░▓░
        0x7D, 0xFF,  // ▓░░░░░▓░        ░░░░░░░░        ▓░░░░░▓░
        0x3A, 0xFE,  // ▓▓░░░▓░▓        ░░░░░░░▓        ▓▓░░░▓░·
        0x04, 0xFC,  // ▓▓▓▓▓░▓▓        ░░░░░░▓▓        ▓▓▓▓▓░··
        0xF8, 0xF8,  // ░░░░░▓▓▓        ░░░░░▓▓▓        ░░░░░···
        
        0x01, 0x01,  // ▓▓▓▓▓▓▓░        ▓▓▓▓▓▓▓░        ·······░
        0x02, 0x03,  // ▓▓▓▓▓▓░▓        ▓▓▓▓▓▓░░        ······░▓
        0x05, 0x07,  // ▓▓▓▓▓░▓░        ▓▓▓▓▓░░░        ·····░▓░
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x0A, 0x0F,  // ▓▓▓▓░▓░▓        ▓▓▓▓░░░░        ····░▓░▓
        0x05, 0x07,  // ▓▓▓▓▓░▓░        ▓▓▓▓▓░░░        ·····░▓░
        0x02, 0x03,  // ▓▓▓▓▓▓░▓        ▓▓▓▓▓▓░░        ······░▓
        0x01, 0x01,  // ▓▓▓▓▓▓▓░        ▓▓▓▓▓▓▓░        ·······░

        // Frame 1 - Right facing
        0xF8, 0xF8,  // ░░░░░▓▓▓ Image  ░░░░░▓▓▓ +Mask  ░░░░░··· Sprite
        0x04, 0xFC,  // ▓▓▓▓▓░▓▓        ░░░░░░▓▓        ▓▓▓▓▓░··
        0x3A, 0xFE,  // ▓▓░░░▓░▓        ░░░░░░░▓        ▓▓░░░▓░·
        0x7D, 0xFF,  // ▓░░░░░▓░        ░░░░░░░░        ▓░░░░░▓░
        0x7D, 0xFF,  // ▓░░░░░▓░        ░░░░░░░░        ▓░░░░░▓░
        0xFD, 0xFF,  // ░░░░░░▓░        ░░░░░░░░        ░░░░░░▓░
        0xCD, 0xFF,  // ░░▓▓░░▓░        ░░░░░░░░        ░░▓▓░░▓░
        0xBD, 0xFF,  // ░▓░░░░▓░        ░░░░░░░░        ░▓░░░░▓░
        0xCD, 0xFF,  // ░░▓▓░░▓░        ░░░░░░░░        ░░▓▓░░▓░
        0xFA, 0xFE,  // ░░░░░▓░▓        ░░░░░░░▓        ░░░░░▓░·
        0x04, 0xFC,  // ▓▓▓▓▓░▓▓        ░░░░░░▓▓        ▓▓▓▓▓░··
        0xF8, 0xF8,  // ░░░░░▓▓▓        ░░░░░▓▓▓        ░░░░░···

        0x01, 0x01,  // ▓▓▓▓▓▓▓░        ▓▓▓▓▓▓▓░        ·······░
        0x02, 0x03,  // ▓▓▓▓▓▓░▓        ▓▓▓▓▓▓░░        ······░▓
        0x05, 0x07,  // ▓▓▓▓▓░▓░        ▓▓▓▓▓░░░        ·····░▓░
        0x0A, 0x0F,  // ▓▓▓▓░▓░▓        ▓▓▓▓░░░░        ····░▓░▓
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x08, 0x0F,  // ▓▓▓▓░▓▓▓        ▓▓▓▓░░░░        ····░▓▓▓
        0x05, 0x07,  // ▓▓▓▓▓░▓░        ▓▓▓▓▓░░░        ·····░▓░
        0x02, 0x03,  // ▓▓▓▓▓▓░▓        ▓▓▓▓▓▓░░        ······░▓
        0x01, 0x01   // ▓▓▓▓▓▓▓░        ▓▓▓▓▓▓▓░        ·······░
    };


    const uint8_t PROGMEM Starman[] = {
    12, 12,
    0x00, 0x4c, 0x90, 0x4c, 0xb6, 0x9e, 0x9e, 0xb6, 0x4c, 0x90, 0x4c, 0x00, 
    0x00, 0x00, 0x04, 0x03, 0x00, 0x02, 0x02, 0x00, 0x03, 0x04, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Starman_Mask[] = {
    0x4c, 0xfe, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfe, 0x4c, 
    0x00, 0x0c, 0x0f, 0x07, 0x03, 0x07, 0x07, 0x03, 0x07, 0x0f, 0x0c, 0x00, 
    };


const uint8_t PROGMEM Spider[] = {
        12, 16, // 12x12 px image 

        // Frame 0 - Left facing
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓ Image  ▓▓▓▓▓▓▓▓ +Mask  ········ Sprite
        0x00, 0xC0,  // ▓▓▓▓▓▓▓▓        ░░▓▓▓▓▓▓        ▓▓······
        0xC0, 0xF8,  // ░░▓▓▓▓▓▓        ░░░░░▓▓▓        ░░▓▓▓···
        0x98, 0xFC,  // ░▓▓░░▓▓▓        ░░░░░░▓▓        ░▓▓░░▓··
        0x6C, 0xFE,  // ▓░░▓░░▓▓        ░░░░░░░▓        ▓░░▓░░▓·
        0x5C, 0xFE,  // ▓░▓░░░▓▓        ░░░░░░░▓        ▓░▓░░░▓·
        0x6C, 0xFE,  // ▓░░▓░░▓▓        ░░░░░░░▓        ▓░░▓░░▓·
        0xBC, 0xFE,  // ░▓░░░░▓▓        ░░░░░░░▓        ░▓░░░░▓·
        0xD8, 0xFC,  // ░░▓░░▓▓▓        ░░░░░░▓▓        ░░▓░░▓··
        0xC0, 0xF8,  // ░░▓▓▓▓▓▓        ░░░░░▓▓▓        ░░▓▓▓···
        0x00, 0xC0,  // ▓▓▓▓▓▓▓▓        ░░▓▓▓▓▓▓        ▓▓······
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓        ········

        0x00, 0x07,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓░░░        ·····▓▓▓
        0x07, 0x0F,  // ▓▓▓▓▓░░░        ▓▓▓▓░░░░        ····▓░░░
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x06, 0x0F,  // ▓▓▓▓▓░░▓        ▓▓▓▓░░░░        ····▓░░▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x01, 0x0F,  // ▓▓▓▓▓▓▓░        ▓▓▓▓░░░░        ····▓▓▓░
        0x03, 0x0F,  // ▓▓▓▓▓▓░░        ▓▓▓▓░░░░        ····▓▓░░
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x06, 0x0F,  // ▓▓▓▓▓░░▓        ▓▓▓▓░░░░        ····▓░░▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x07, 0x0F,  // ▓▓▓▓▓░░░        ▓▓▓▓░░░░        ····▓░░░
        0x00, 0x07,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓░░░        ·····▓▓▓

        // Frame 1 - Right facing
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓ Image  ▓▓▓▓▓▓▓▓ +Mask  ········ Sprite
        0x00, 0xC0,  // ▓▓▓▓▓▓▓▓        ░░▓▓▓▓▓▓        ▓▓······
        0xC0, 0xF8,  // ░░▓▓▓▓▓▓        ░░░░░▓▓▓        ░░▓▓▓···
        0xD8, 0xFC,  // ░░▓░░▓▓▓        ░░░░░░▓▓        ░░▓░░▓··
        0xBC, 0xFE,  // ░▓░░░░▓▓        ░░░░░░░▓        ░▓░░░░▓·
        0x6C, 0xFE,  // ▓░░▓░░▓▓        ░░░░░░░▓        ▓░░▓░░▓·
        0x5C, 0xFE,  // ▓░▓░░░▓▓        ░░░░░░░▓        ▓░▓░░░▓·
        0x6C, 0xFE,  // ▓░░▓░░▓▓        ░░░░░░░▓        ▓░░▓░░▓·
        0x98, 0xFC,  // ░▓▓░░▓▓▓        ░░░░░░▓▓        ░▓▓░░▓··
        0xC0, 0xF8,  // ░░▓▓▓▓▓▓        ░░░░░▓▓▓        ░░▓▓▓···
        0x00, 0xC0,  // ▓▓▓▓▓▓▓▓        ░░▓▓▓▓▓▓        ▓▓······
        0x00, 0x00,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓▓▓        ········

        0x00, 0x07,  // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓░░░        ·····▓▓▓
        0x07, 0x0F,  // ▓▓▓▓▓░░░        ▓▓▓▓░░░░        ····▓░░░
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x06, 0x0F,  // ▓▓▓▓▓░░▓        ▓▓▓▓░░░░        ····▓░░▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x03, 0x0F,  // ▓▓▓▓▓▓░░        ▓▓▓▓░░░░        ····▓▓░░
        0x01, 0x0F,  // ▓▓▓▓▓▓▓░        ▓▓▓▓░░░░        ····▓▓▓░
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x06, 0x0F,  // ▓▓▓▓▓░░▓        ▓▓▓▓░░░░        ····▓░░▓
        0x09, 0x0F,  // ▓▓▓▓░▓▓░        ▓▓▓▓░░░░        ····░▓▓░
        0x07, 0x0F,  // ▓▓▓▓▓░░░        ▓▓▓▓░░░░        ····▓░░░
        0x00, 0x07   // ▓▓▓▓▓▓▓▓        ▓▓▓▓▓░░░        ·····▓▓▓
    };

    const uint8_t PROGMEM Bolt[] = {
    16, 16,
    0x00, 0x00, 0xc0, 0x20, 0x10, 0x90, 0x08, 0x08, 0x10, 0x08, 0x04, 0x94, 0x44, 0x38, 0x02, 0x00, 
    0x00, 0x1e, 0x21, 0x4c, 0x56, 0x5e, 0x4c, 0x21, 0x24, 0x20, 0x10, 0x0c, 0x03, 0x00, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Bolt_Mask[] = {
    0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0x7e, 0x3f, 0x02, 
    0x1e, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 
    };

    const uint8_t PROGMEM Tile_Brick[] = {
    12, 12,
    0x04, 0x8e, 0x46, 0xa2, 0x42, 0x86, 0x42, 0xa2, 0x46, 0x8e, 0x42, 0x84, 
    0x00, 0x02, 0x07, 0x07, 0x05, 0x06, 0x03, 0x07, 0x05, 0x06, 0x07, 0x02, 

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
        Spider,                  // 0 - not used
        Spider,                  // 1
        Starman,                   // 2
        Skull,                     // 3
        Bolt,                       // 4
        Health,                   // 5
        Tile_QBlock,                // 6
        Tile_BQBlock,               // 7
        Tile_QBlock,                // 8
        Tile_Brick,                 // 9
    };

    const uint8_t * const SpriteMasks[] PROGMEM =  { 
        Spider, 
        Spider, 
        Starman_Mask, 
        Skull, 
        Bolt_Mask, 
        Health,
        Tile_Mask, 
        Tile_Mask, 
        Tile_Mask, 
        Tile_Mask, 
    };

    const uint8_t PROGMEM Pirahna_Up[] = {
    12, 16,
    0xf8, 0x04, 0xfa, 0xad, 0x8d, 0x43, 0x71, 0xfd, 0xf5, 0xfa, 0x04, 0xf8, 
    0x00, 0x63, 0x94, 0xab, 0xb6, 0xbf, 0xbf, 0xb6, 0xab, 0x94, 0x63, 0x00, 

    0xf8, 0x04, 0xfa, 0xad, 0x8b, 0x46, 0x73, 0xfd, 0xf5, 0xfa, 0x04, 0xf8, 
    0x00, 0x63, 0x94, 0xab, 0xb6, 0xbf, 0xbf, 0xb6, 0xab, 0x94, 0x63, 0x00, 
    };

    const uint8_t PROGMEM Pirahna_Up_Mask[] = {
    0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 
    0x00, 0x63, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x63, 0x00, 
    };

    const uint8_t PROGMEM Pirahna_Down[] = {
    12, 16,
    0x00, 0xc6, 0x29, 0xd5, 0x6d, 0xfd, 0xfd, 0x6d, 0xd5, 0x29, 0xc6, 0x00, 
    0x1f, 0x20, 0x5f, 0xb5, 0xb1, 0xc2, 0x8e, 0xbf, 0xaf, 0x5f, 0x20, 0x1f, 

    0x00, 0xc6, 0x29, 0xd5, 0x6d, 0xfd, 0xfd, 0x6d, 0xd5, 0x29, 0xc6, 0x00, 
    0x1f, 0x20, 0x5f, 0xb5, 0xd1, 0x62, 0xce, 0xbf, 0xaf, 0x5f, 0x20, 0x1f, 
    };

    const uint8_t PROGMEM Pirahna_Down_Mask[] = {
    0x00, 0xc6, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xc6, 0x00, 
    0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 
    };

};
