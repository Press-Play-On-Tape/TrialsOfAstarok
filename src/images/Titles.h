#pragma once

#include "../utils/Constants.h"

namespace Images {

    #ifndef DEBUG
    const uint8_t PROGMEM Title[] = {
        79, 56, // 79x53 px image

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0xa0, 0x50, 0x28, 0xd4, 0xea, 0x72, 0x3a, 0x9a, 0x9a, 0x12, 0x32, 0xf5, 0xe1, 0x91, 0xe1, 0xf2, 0x34, 0x12, 0x9a, 0x9a, 0x3a, 0x72, 0xea, 0xd4, 0x28, 0x50, 0xa0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0xc0, 0x80, 0x00, 0x00, 0x0c, 0x04, 0xfc, 0x04, 0x0c, 0x04, 0xfc, 0x84, 0x84, 0xfc, 0x04, 0x04, 0xfc, 0x85, 0xc4, 0x0c, 0x01, 0x00, 0x01, 0x0d, 0x04, 0xfd, 0x04, 0x0c, 0x05, 0xfc, 0x84, 0x85, 0x78, 0x01, 0x04, 0xfc, 0x05, 0x00, 0xf8, 0x85, 0x84, 0xf9, 0x01, 0xfc, 0x01, 0x00, 0x78, 0xc5, 0x1c, 0x00, 0x00, 0x00, 0xf8, 0x04, 0x04, 0xf8, 0x00, 0x04, 0xfc, 0x84, 0xc4, 0x0c, 0x00, 0x00, 0x80, 0x40, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x80, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83, 0x81, 0x80, 0x80, 0x80, 0x90, 0x9f, 0x90, 0x80, 0x90, 0x9f, 0x90, 0x90, 0x9f, 0x90, 0x90, 0x9f, 0x90, 0x91, 0x9c, 0x80, 0x80, 0x80, 0x80, 0x90, 0x9f, 0x90, 0x80, 0x90, 0x9f, 0x90, 0x80, 0x8f, 0x90, 0x90, 0x9f, 0x90, 0x80, 0x9f, 0x80, 0x80, 0x9f, 0x80, 0x9f, 0x90, 0x90, 0x98, 0x90, 0x8f, 0x80, 0x80, 0x80, 0x8f, 0x90, 0x90, 0x8f, 0x80, 0x90, 0x9f, 0x90, 0x81, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83, 0x81, 0x80, 0x80, 0x80, 0x00, 
        0x01, 0x00, 0x00, 0xf8, 0xfc, 0x7c, 0x1c, 0x3c, 0xfc, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x8c, 0x1c, 0x1c, 0x1c, 0x14, 0x74, 0xe4, 0xe4, 0xc4, 0x00, 0x04, 0x04, 0x0c, 0xfc, 0xfc, 0xfc, 0x0c, 0x04, 0x04, 0x00, 0x00, 0xf4, 0xfc, 0x3c, 0x1c, 0x1c, 0x7c, 0xfc, 0xfc, 0xc4, 0x00, 0x04, 0xfc, 0xfc, 0x1c, 0x1c, 0x1c, 0xfc, 0xf8, 0x30, 0x00, 0x00, 0xf8, 0xfc, 0x3c, 0x1c, 0x1c, 0x7c, 0xfc, 0xf8, 0x00, 0x00, 0x04, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x84, 0xfc, 0xfc, 0x04, 0x00, 0x00, 0x01, 
        0x00, 0x00, 0x00, 0xff, 0x07, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x3f, 0x63, 0xc3, 0x02, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x31, 0xc3, 0x03, 0x03, 0x01, 0x7f, 0x0f, 0x07, 0x00, 0x00, 0x01, 0xff, 0x00, 0x0c, 0x3f, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x40, 0xc0, 0x40, 0x20, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x18, 0x7e, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x00, 0x00, 0x80, 0x7f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x1f, 0x78, 0xc0, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x15, 0x09, 0x00, 0x02, 0x0f, 0x12, 0x00, 0x0c, 0x12, 0x1e, 0x00, 0x1e, 0x02, 0x06, 0x00, 0x02, 0x0f, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x15, 0x09, 0x00, 0x0c, 0x12, 0x12, 0x00, 0x1e, 0x12, 0x1e, 0x00, 0x1e, 0x02, 0x06, 0x00, 0x0c, 0x1a, 0x14, 0x00, 0x14, 0x12, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
    };
    #else
    const uint8_t PROGMEM Title[] = {
        1, 1,
        0x01
    };
    #endif

    const uint8_t PROGMEM Title_Highlight[] = {
        28, 8, // 28x4 px image
        0x01,  // ▓▓▓▓▓▓▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x04,  // ▓▓▓▓▓░▓▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x06,  // ▓▓▓▓▓░░▓
        0x0D,  // ▓▓▓▓░░▓░
        0x0F,  // ▓▓▓▓░░░░
        0x06,  // ▓▓▓▓▓░░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x04,  // ▓▓▓▓▓░▓▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x01,  // ▓▓▓▓▓▓▓░
    };

    #ifndef DEBUG
    const uint8_t PROGMEM EnterRunes_Text[] = {
        // ⢹⠉⠋⡷⡀⢹⠙⢹⠙⢹⠉⠋⡏⢱⠀⠀⠈⡏⢱⢹⠀⡏⡷⡀⢹⢹⠉⢳⠉⠇
        // ⢸⠺⠀⡇⠱⣸⠀⢸⠀⢸⠺⠀⡗⢪⠀⠀⠀⡗⢪⢸⠀⡇⡇⠱⣸⢸⠺⠀⠑⡄
        // ⠼⠤⠧⠇⠀⠽⠄⠼⠄⠼⠤⠧⠧⠘⠄⠀⠠⠧⠘⠜⠤⠣⠇⠀⠽⠼⠤⠖⠤⠃
        // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        59, 16, // 59x11 px image 
        0x01, 0xff, 0x21, 0x71, 0x03, 0x01, 0xff, 0x06, 0x18, 0x60, 0x81, 0xff, 0x01, 0x03, 0x01, 0xff, 0x01, 0x03, 0x01, 0xff, 0x21, 0x71, 0x03, 0x01, 0xff, 0x21, 0x21, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x21, 0x21, 0xde, 0x01, 0xff, 0x00, 0x00, 0xff, 0x01, 0xff, 0x06, 0x18, 0x60, 0x81, 0xff, 0x01, 0xff, 0x21, 0x71, 0x03, 0x0e, 0x11, 0x21, 0xc7, 
        0x04, 0x07, 0x04, 0x04, 0x07, 0x04, 0x07, 0x00, 0x00, 0x00, 0x05, 0x07, 0x04, 0x00, 0x04, 0x07, 0x04, 0x00, 0x04, 0x07, 0x04, 0x04, 0x07, 0x04, 0x07, 0x04, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x04, 0x00, 0x03, 0x04, 0x03, 0x04, 0x04, 0x03, 0x04, 0x07, 0x00, 0x00, 0x00, 0x05, 0x07, 0x04, 0x07, 0x04, 0x04, 0x06, 0x02, 0x04, 0x04, 0x03
    };
    #else
    const uint8_t PROGMEM EnterRunes_Text[] = {
        1, 1,
        0x01
    };
    #endif

    const uint8_t PROGMEM EnterRunes_Frame[] = {
        7, 8,   // 7x8 px image 
    
        // Frame 0
        0xFF,  // ░░░░░░░░
        0x01,  // ▓▓▓▓▓▓▓░
        0x55,  // ▓░▓░▓░▓░
        0x11,  // ▓▓▓░▓▓▓░
        0x0D,  // ▓▓▓▓░░▓░
        0x01,  // ▓▓▓▓▓▓▓░
        0x05,  // ▓▓▓▓▓░▓░

        // Frame 1
        0x05,  // ▓▓▓▓▓░▓░
        0x01,  // ▓▓▓▓▓▓▓░
        0x0D,  // ▓▓▓▓░░▓░
        0x11,  // ▓▓▓░▓▓▓░
        0x55,  // ▓░▓░▓░▓░
        0x01,  // ▓▓▓▓▓▓▓░
        0xFF,  // ░░░░░░░░

        // Frame 2
        0xFF,  // ░░░░░░░░
        0x80,  // ░▓▓▓▓▓▓▓
        0xAA,  // ░▓░▓░▓░▓
        0x88,  // ░▓▓▓░▓▓▓
        0xB0,  // ░▓░░▓▓▓▓
        0x80,  // ░▓▓▓▓▓▓▓
        0xA0,  // ░▓░▓▓▓▓▓

        // Frame 3
        0xA0,  // ░▓░▓▓▓▓▓
        0x80,  // ░▓▓▓▓▓▓▓
        0xB0,  // ░▓░░▓▓▓▓
        0x88,  // ░▓▓▓░▓▓▓
        0xAA,  // ░▓░▓░▓░▓
        0x80,  // ░▓▓▓▓▓▓▓
        0xFF   // ░░░░░░░░
    };

    const uint8_t PROGMEM SoundToggle[] = {
        9, 8, // 9x8 px image 
        
        // Frame 0 - Sound off
        0x00,  // ▓▓▓▓▓▓▓▓
        0x38,  // ▓▓░░░▓▓▓
        0x28,  // ▓▓░▓░▓▓▓
        0x44,  // ▓░▓▓▓░▓▓
        0xFE,  // ░░░░░░░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x00,  // ▓▓▓▓▓▓▓▓

        // Frame 1 - Sound on
        0x00,  // ▓▓▓▓▓▓▓▓
        0x38,  // ▓▓░░░▓▓▓
        0x38,  // ▓▓░░░▓▓▓
        0x7C,  // ▓░░░░░▓▓
        0xFE,  // ░░░░░░░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x54,  // ▓░▓░▓░▓▓
        0x92,  // ░▓▓░▓▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
    };


    const uint8_t PROGMEM Arrows[] = {
        7, 8,  // 7x3 px image
        
        // Frame 0 - Arrow up
        0x04,  // ▓▓▓▓▓░▓▓
        0x06,  // ▓▓▓▓▓░░▓
        0x07,  // ▓▓▓▓▓░░░
        0x06,  // ▓▓▓▓▓░░▓
        0x05,  // ▓▓▓▓▓░▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x04,  // ▓▓▓▓▓░▓▓
    
        // Frame 1 - Arrow down
        0x01,  // ▓▓▓▓▓▓▓░
        0x03,  // ▓▓▓▓▓▓░░
        0x07,  // ▓▓▓▓▓░░░
        0x03,  // ▓▓▓▓▓▓░░
        0x05,  // ▓▓▓▓▓░▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x01,  // ▓▓▓▓▓▓▓░
    };


    const uint8_t PROGMEM Heart[] = {
        7, 8,  // 7x6 px image

        // Frame 0 - Full
        0x06,  // ▓▓▓▓▓░░▓
        0x0F,  // ▓▓▓▓░░░░
        0x1F,  // ▓▓▓░░░░░
        0x3E,  // ▓▓░░░░░▓
        0x1F,  // ▓▓▓░░░░░
        0x0F,  // ▓▓▓▓░░░░
        0x06,  // ▓▓▓▓▓░░▓

        // Frame 1 - Empty
        0x06,  // ▓▓▓▓▓░░▓
        0x09,  // ▓▓▓▓░▓▓░
        0x11,  // ▓▓▓░▓▓▓░
        0x22,  // ▓▓░▓▓▓░▓
        0x11,  // ▓▓▓░▓▓▓░
        0x09,  // ▓▓▓▓░▓▓░
        0x06,  // ▓▓▓▓▓░░▓
    };

    const uint8_t PROGMEM Numbers[] = {
        4, 8,   // 4x6 px glyphs 

        // 0 - #048 Number '0' (U+0030 Digit Zero)
        0x1E,  // ▓▓▓░░░░▓
        0x3F,  // ▓▓░░░░░░
        0x21,  // ▓▓░▓▓▓▓░
        0x1E,  // ▓▓▓░░░░▓
        
        // 1 - #049 Number '1' (U+0031 Digit One)
        0x22,  // ▓▓░▓▓▓░▓
        0x3E,  // ▓▓░░░░░▓
        0x3F,  // ▓▓░░░░░░
        0x20,  // ▓▓░▓▓▓▓▓

        // 2 - #050 Number '2' (U+0032 Digit Two)
        0x32,  // ▓▓░░▓▓░▓
        0x29,  // ▓▓░▓░▓▓░
        0x25,  // ▓▓░▓▓░▓░
        0x32,  // ▓▓░░▓▓░▓

        // 3 - #051 Number '3' (U+0033 Digit Three)
        0x12,  // ▓▓▓░▓▓░▓
        0x25,  // ▓▓░▓▓░▓░
        0x3F,  // ▓▓░░░░░░
        0x1A,  // ▓▓▓░░▓░▓

        // 4 - #052 Number '4' (U+0034 Digit Four)
        0x0C,  // ▓▓▓▓░░▓▓
        0x2A,  // ▓▓░▓░▓░▓
        0x3F,  // ▓▓░░░░░░
        0x2C,  // ▓▓░▓░░▓▓

        // 5 - #053 Number '5' (U+0035 Digit Five)
        0x17,  // ▓▓▓░▓░░░
        0x25,  // ▓▓░▓▓░▓░
        0x3D,  // ▓▓░░░░▓░
        0x18,  // ▓▓▓░░▓▓▓

        // 6 - #054 Number '6' (U+0036 Digit Six)
        0x1E,  // ▓▓▓░░░░▓
        0x3F,  // ▓▓░░░░░░
        0x25,  // ▓▓░▓▓░▓░
        0x18,  // ▓▓▓░░▓▓▓

        // 7 - #055 Number '7' (U+0037 Digit Seven)
        0x23,  // ▓▓░▓▓▓░░
        0x39,  // ▓▓░░░▓▓░
        0x3D,  // ▓▓░░░░▓░
        0x23,  // ▓▓░▓▓▓░░

        // 8 - #056 Number '8' (U+0038 Digit Eight)
        0x1A,  // ▓▓▓░░▓░▓
        0x25,  // ▓▓░▓▓░▓░
        0x2D,  // ▓▓░▓░░▓░
        0x1A,  // ▓▓▓░░▓░▓

        // 9 - #057 Number '9' (U+0039 Digit Nine)
        0x06,  // ▓▓▓▓▓░░▓
        0x2F,  // ▓▓░▓░░░░
        0x29,  // ▓▓░▓░▓▓░
        0x1E   // ▓▓▓░░░░▓
    };


    #ifndef DEBUG
    const uint8_t PROGMEM GameOver[] = {
        98, 40, // 98x37 px image
        // ⠀⠀⠀⢠⢢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        // ⢀⠤⠤⠇⠈⠦⠤⠤⠤⠤⠤⢄⢠⠤⢤⠤⠤⠤⠤⢄⡠⠤⠤⡀⠀⠀⡠⠤⠤⠤⠤⠤⣀⠤⠤⢄⠤⠤⢄⠤⠤⠤⠤⣀⠤⠤⠤⠤⡀⠀
        // ⠀⠣⠤⡄⠀⡤⠔⢹⠀⢠⢄⠀⣿⠀⢸⠃⢠⢢⠀⢸⡜⠀⡸⠀⠀⠀⡇⠀⡤⠤⡄⠀⣷⠁⠀⡎⡆⠀⢻⠀⢠⠤⠤⠃⡇⠀⣤⠀⢸⠀
        // ⠀⠀⠀⡇⢀⠇⠀⢸⠀⢸⠊⡠⢻⠀⢸⠀⡓⠒⡃⠀⡇⠀⡇⠀⠀⠀⡇⠀⡇⠀⡇⠀⣿⠀⢸⠀⢸⠀⢸⡀⠈⡭⠭⠂⡇⠀⡟⢀⠜⠀
        // ⠀⠀⠀⡇⢸⠀⠀⠈⡆⡾⡀⡇⠘⡄⡸⡄⢏⠉⡇⡸⠱⡀⢣⠀⠀⠀⢣⠀⡇⠀⡇⢠⠃⢆⠘⢄⠜⢠⠃⠱⡀⢣⠀⠀⢱⢰⢇⢸⠀⠀
        // ⠀⠀⠀⡇⢸⠀⠀⠀⡇⡇⠱⡱⡀⡇⡇⠈⠪⣚⠜⠀⠀⠱⡈⢆⠀⠀⠸⡀⢇⢀⠇⡜⠀⠀⠑⢄⠔⠁⠀⠀⠈⠢⢕⠄⢸⢸⠈⢎⢆⠀
        // ⠀⠀⠀⢸⢸⠀⠀⠀⠣⠃⠀⠈⠀⡇⡇⠀⠀⠀⠀⠀⠀⠀⠈⠪⡂⠄⠀⢣⢸⢸⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠜⠀⠀⠁⠀
        // ⠀⠀⠀⢸⢸⠀⠀⠀⠀⠀⠀⠀⠀⢇⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢇⢇⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        // ⠀⠀⠀⠸⡸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    
        0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x70, 0x0c, 0x02, 0x1c, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0xc0, 0x40, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 
        0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0xfc, 0x00, 0x00, 0x80, 0x7c, 0x04, 0x04, 0x02, 0x01, 0xff, 0x00, 0x00, 0x00, 0xfc, 0x24, 0x18, 0x80, 0x40, 0x3f, 0xff, 0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0xb0, 0x2c, 0x22, 0x2c, 0xb0, 0x00, 0x00, 0x0f, 0xfc, 0x03, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xfc, 0x04, 0x04, 0x04, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x01, 0x00, 0x00, 0xf0, 0x0e, 0x01, 0x0e, 0xf0, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x1c, 0xd4, 0x54, 0x54, 0x54, 0x23, 0x00, 0xff, 0x00, 0x00, 0x00, 0xfc, 0x3c, 0x00, 0x80, 0x40, 0x3f, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0xfe, 0x07, 0x18, 0x60, 0x9f, 0x60, 0x80, 0x03, 0xfc, 0x00, 0xf8, 0x07, 0x0c, 0x10, 0x27, 0x59, 0xa1, 0xb1, 0x4f, 0x30, 0x08, 0x07, 0x01, 0x06, 0x18, 0x60, 0x83, 0x1c, 0x60, 0x80, 0x00, 0x00, 0x00, 0x03, 0x7c, 0x80, 0x00, 0x7f, 0x80, 0x00, 0x80, 0x7f, 0x00, 0xc0, 0x3c, 0x03, 0x00, 0x06, 0x08, 0x10, 0x23, 0x44, 0x88, 0x44, 0x23, 0x10, 0x0c, 0x03, 0x00, 0x01, 0x06, 0x08, 0x10, 0x23, 0x4c, 0x50, 0xa0, 0x40, 0x00, 0x01, 0xfe, 0x00, 0xfe, 0x07, 0x18, 0x60, 0x9f, 0x60, 0x80, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x7f, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x05, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x70, 0x8f, 0x70, 0x8f, 0x70, 0x0e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };
    #else
    const uint8_t PROGMEM GameOver[] = {
        1, 1,
        0x01
    };
    #endif

    #ifndef DEBUG
    const uint8_t PROGMEM GameOver_Mask[] = {
        0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 
        0x00, 0x03, 0x07, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x07, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0xe0, 0x80, 0x00, 0x03, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xfe, 0xf0, 0xe0, 0x41, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x01, 0x03, 0x01, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x0e, 0x04, 0x00, 0x03, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    };
    #else
    const uint8_t PROGMEM GameOver_Mask[] = {
        0x01
    };
    #endif

    #ifndef DEBUG
    const uint8_t PROGMEM TopThree[] = {
        51, 16, // 51x11 px image
        // ⠋⡏⢳⠉⡎⡏⢱⠀⠐⠉⢱⠀⠘⢹⠙⢹⠉⡆⢹⠁⡎⢱⢸⠀⡎⠇
        // ⠀⡇⢸⠀⡇⡗⠊⠀⠀⠐⢪⠀⠀⢸⠀⢸⠒⡅⢸⠀⡗⢺⢸⠀⠙⡄
        // ⠠⠧⠘⠤⠣⠧⠀⠀⠐⠤⠜⠀⠀⠼⠄⠼⠄⠣⠼⠄⠇⠸⠸⠤⠦⠃
        // ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        0x03, 0x01, 0xff, 0x01, 0x03, 0xfe, 0x01, 0x01, 0xfe, 0x01, 0xff, 0x21, 0x21, 0x1e, 0x00, 0x00, 0x00, 0x02, 0x01, 0x21, 0x21, 0xde, 0x00, 0x00, 0x00, 0x03, 0x01, 0xff, 0x01, 0x03, 0x01, 0xff, 0x21, 0x21, 0xde, 0x00, 0x01, 0xff, 0x01, 0x00, 0xfe, 0x21, 0x21, 0xfe, 0x00, 0xff, 0x00, 0x00, 0x1e, 0x31, 0xc7, 
        0x00, 0x04, 0x07, 0x04, 0x00, 0x03, 0x04, 0x04, 0x03, 0x04, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x04, 0x00, 0x04, 0x07, 0x04, 0x00, 0x03, 0x04, 0x04, 0x07, 0x04, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x07, 0x04, 0x04, 0x06, 0x04, 0x03
    };
    #else
    const uint8_t PROGMEM TopThree[] = {
        0x01
    };
    #endif

    const uint8_t PROGMEM HighScore_Pattern[] = {
        3, 8,  // 3x5 px image
        0x11,  // ▓▓▓░▓▓▓░
        0x00,  // ▓▓▓▓▓▓▓▓
        0x05,  // ▓▓▓▓▓░▓░
    };

    const uint8_t PROGMEM HighScore_Pattern_2[] = {
        20, 16, // 20x11 px image
        0x07,  // ▓▓▓▓▓░░░
        0x03,  // ▓▓▓▓▓▓░░
        0x87,  // ░▓▓▓▓░░░
        0xC3,  // ░░▓▓▓▓░░
        0xE2,  // ░░░▓▓▓░▓
        0x44,  // ▓░▓▓▓░▓▓
        0xA3,  // ░▓░▓▓▓░░
        0x47,  // ▓░▓▓▓░░░
        0xA3,  // ░▓░▓▓▓░░
        0x47,  // ▓░▓▓▓░░░
        0xA7,  // ░▓░▓▓░░░
        0x03,  // ▓▓▓▓▓▓░░
        0x07,  // ▓▓▓▓▓░░░
        0x03,  // ▓▓▓▓▓▓░░
        0x87,  // ░▓▓▓▓░░░
        0xC3,  // ░░▓▓▓▓░░
        0xE2,  // ░░░▓▓▓░▓
        0x44,  // ▓░▓▓▓░▓▓
        0xA3,  // ░▓░▓▓▓░░
        0x47,  // ▓░▓▓▓░░░

        0x05,  // ▓▓▓▓▓░▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x04,  // ▓▓▓▓▓░▓▓
        0x01,  // ▓▓▓▓▓▓▓░
        0x00,  // ▓▓▓▓▓▓▓▓
        0x04,  // ▓▓▓▓▓░▓▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x05,  // ▓▓▓▓▓░▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x05,  // ▓▓▓▓▓░▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x05,  // ▓▓▓▓▓░▓░
        0x02,  // ▓▓▓▓▓▓░▓
        0x04,  // ▓▓▓▓▓░▓▓
        0x01,  // ▓▓▓▓▓▓▓░
        0x00,  // ▓▓▓▓▓▓▓▓
        0x04,  // ▓▓▓▓▓░▓▓
        0x02,  // ▓▓▓▓▓▓░▓
        0x05,  // ▓▓▓▓▓░▓░
    };

    const uint8_t PROGMEM Torch[] = {
        6, 16, // 6x12 px image

        // Frame 0
        0x40,  // ▓░▓▓▓▓▓▓
        0x90,  // ░▓▓░▓▓▓▓
        0xBA,  // ░▓░░░▓░▓
        0x9C,  // ░▓▓░░░▓▓
        0x90,  // ░▓▓░▓▓▓▓
        0x40,  // ▓░▓▓▓▓▓▓

        0x04,  // ▓▓▓▓▓░▓▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x04,  // ▓▓▓▓▓░▓▓

        // Frame 1 
        0x40,  // ▓░▓▓▓▓▓▓
        0x98,  // ░▓▓░░▓▓▓
        0xB8,  // ░▓░░░▓▓▓
        0xB5,  // ░▓░░▓░▓░
        0x98,  // ░▓▓░░▓▓▓
        0x40,  // ▓░▓▓▓▓▓▓

        0x04,  // ▓▓▓▓▓░▓▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x04,  // ▓▓▓▓▓░▓▓

        // Frame 2
        0x40,  // ▓░▓▓▓▓▓▓
        0x90,  // ░▓▓░▓▓▓▓
        0x9C,  // ░▓▓░░░▓▓
        0xBA,  // ░▓░░░▓░▓
        0x90,  // ░▓▓░▓▓▓▓
        0x40,  // ▓░▓▓▓▓▓▓

        0x04,  // ▓▓▓▓▓░▓▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x04,  // ▓▓▓▓▓░▓▓

        // Frame 3
        0x40,  // ▓░▓▓▓▓▓▓
        0x98,  // ░▓▓░░▓▓▓
        0xB5,  // ░▓░░▓░▓░
        0xB8,  // ░▓░░░▓▓▓
        0x98,  // ░▓▓░░▓▓▓
        0x40,  // ▓░▓▓▓▓▓▓

        0x04,  // ▓▓▓▓▓░▓▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x0A,  // ▓▓▓▓░▓░▓
        0x00,  // ▓▓▓▓▓▓▓▓
        0x04,  // ▓▓▓▓▓░▓▓
    };


    const uint8_t PROGMEM Pause[] = {
        61, 32, // 61x32 px image (+mask)
        
        // ⠠⡒⠒⠒⠒⠒⢤⡒⠒⠒⠒⢢⢔⠒⠒⡔⠒⢒⠤⡒⠒⠒⠒⢢⡔⠒⠒⠒⠒⡢⠀
        // ⠀⢱⠀⢰⢲⠀⢸⠁⢠⢲⠀⢸⡇⠀⡜⠸⡀⠈⣶⠁⢠⠒⣢⡊⡇⠀⡖⡆⢠⠃⠀
        // ⠀⢸⠀⡇⡸⠀⣼⠀⣜⢄⡇⠘⣇⠀⡇⠀⡇⢠⢻⠀⣊⣩⠀⢸⢇⠀⣇⢧⡃⠀⠀
        // ⠀⢸⠀⡧⢃⠔⢹⠀⡦⡠⡅⢠⠋⢆⠱⡸⢀⠎⠀⠉⠀⡜⡠⠃⠸⡀⢠⡠⠬⠂⠀
        // ⠀⢸⠀⡖⠁⠀⠈⡆⡇⠀⡇⢸⠀⠀⠑⠒⠁⠀⠀⠀⠪⠊⠀⠀⠀⢣⠘⡄⠀⠀⠀
        // ⠀⠈⡆⡇⠀⠀⠀⢱⢱⠀⡇⡜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⢱⠀⠀⠀
        // ⠀⠀⡇⡇⠀⠀⠀⠀⠁⢀⢇⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠣⡣⠀⠀
        // ⠀⠀⠣⠃⠀⠀⠀⠀⠀⠘⠜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

        0x00,0x04, 0x04,0x1E, 0x1A,0xFF, 0xE2,0xFF, 0x02,0xFF, 0x02,0xFF, 0x02,0xFF, 0xE2,0xFF, 0x22,0xFF, 0xE2,0xFF, 0x02,0xFF, 0x02,0xFF, 0x04,0xFE, 0xFC,0xFE, 0x1A,0xFF, 0x02,0xFF, 0x02,0xFF, 0xC2,0xFF, 0x22,0xFF, 0xE2,0xFF, 0x02,0xFF, 0x02,0xFF, 0x02,0xFF, 0xFC,0xFE, 0xF4,0xFE, 0x0A,0xFF, 0x02,0xFF, 0x02,0xFF, 0xC2,0xFF, 0x32,0xFF, 0x0C,0x7E, 0x72,0xFF, 0x82,0xFF, 0x02,0xFF, 0x02,0xFF, 0x1A,0xFF, 0xE4,0xFE, 0xE4,0xFE, 0x1A,0xFF, 0x02,0xFF, 0x02,0xFF, 0xC2,0xFF, 0x22,0xFF, 0x22,0xFF, 0xA2,0xFF, 0xC2,0xFF, 0xA2,0xFF, 0x1C,0xFE, 0xFC,0xFE, 0x02,0xFF, 0x02,0xFF, 0x02,0xFF, 0xE2,0xFF, 0x22,0xFF, 0xE2,0xFF, 0x02,0xFF, 0x02,0xFF, 0xC2,0xFF, 0x3A,0xFF, 0x04,0x3E, 0x00,0x04, 0x00,0x00, 0x00,0x00, 0x00,0xFF, 0xFF,0xFF, 0x00,0xFF, 0x00,0xFF, 0xFF,0xFF, 0x40,0xFF, 0x38,0xFF, 0x87,0xFF, 0x40,0xFF, 0x20,0x7F, 0x1C,0xFF, 0xFF,0xFF, 0x00,0xFF, 0x00,0xFF, 0xEC,0xFF, 0x4B,0xFF, 0x84,0xFF, 0x48,0xFF, 0xDF,0xFF, 0x00,0xFF, 0x00,0xFF, 0xC3,0xFF, 0x3F,0xFF, 0x18,0x7F, 0x60,0xFF, 0x80,0xFF, 0x1F,0xFF, 0x60,0xFF, 0x80,0xF0, 0x70,0xFF, 0x0F,0xFF, 0x80,0xFF, 0x60,0xFF, 0x1C,0x7F, 0x03,0x1F, 0x0F,0x1F, 0x10,0x3F, 0x10,0x3F, 0x0A,0x1F, 0x09,0xDF, 0xC9,0xFF, 0x3D,0xFF, 0x80,0xFF, 0x40,0xFF, 0x30,0x7F, 0x0F,0x3F, 0x07,0x7F, 0x78,0xFF, 0x80,0xFF, 0x00,0xFF, 0x0F,0xFF, 0xC8,0xFF, 0x87,0xFF, 0x4C,0xFF, 0x4B,0xFF, 0x50,0xFB, 0x20,0x70, 0x00,0x20, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x1F, 0x1F,0xFF, 0xE0,0xFF, 0x00,0xFF, 0xFE,0xFF, 0x02,0xFF, 0x01,0x03, 0x00,0x01, 0x00,0x00, 0x00,0x00, 0x00,0x01, 0x01,0x1F, 0x1E,0xFF, 0xE0,0xFF, 0x1F,0xFF, 0xE0,0xFF, 0x00,0xFF, 0x00,0xFF, 0xFF,0xFF, 0x00,0xFF, 0xC0,0xFF, 0x3F,0xFF, 0x00,0x3F, 0x00,0x00, 0x00,0x00, 0x00,0x01, 0x01,0x03, 0x02,0x07, 0x02,0x07, 0x02,0x07, 0x01,0x03, 0x00,0x01, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x02, 0x02,0x07, 0x05,0x0F, 0x02,0x07, 0x01,0x03, 0x00,0x01, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x03, 0x03,0x0F, 0x0C,0x3F, 0x30,0xFF, 0xC3,0xFF, 0x1C,0xFF, 0xE0,0xFC, 0x00,0xE0, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x3F, 0x3F,0x7F, 0x40,0xFF, 0x3F,0x7F, 0x00,0x3F, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x01, 0x01,0x03, 0x00,0x01, 0x00,0x38, 0x38,0x7F, 0x47,0xFF, 0x38,0x7F, 0x07,0x3F, 0x00,0x07, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x03, 0x03,0x07, 0x04,0x0F, 0x0B,0x1F, 0x04,0x0F, 0x00,0x04, 0x00,0x00, 0x00,0x00
    };

};