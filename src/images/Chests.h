#pragma once

namespace Images {

    const uint8_t PROGMEM Chest_Closed[] = {
    20, 15,
    0xc0, 0x30, 0xc8, 0xf4, 0x1a, 0x65, 0x6d, 0x6a, 0x6a, 0x2a, 0xca, 0xf2, 0x3a, 0x05, 0x05, 0x32, 0xc4, 0x08, 0x30, 0xc0, 
    0x1f, 0x60, 0x1d, 0x61, 0x07, 0x2f, 0x29, 0x2f, 0x27, 0x21, 0x01, 0x3d, 0x60, 0x00, 0x01, 0x61, 0x1d, 0x00, 0x60, 0x1f, 
    };

    const uint8_t PROGMEM Chest_Closed_Mask[] = {
    0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xc0, 
    0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1f, 
    };

    const uint8_t PROGMEM Chest_Open[] = {
    24, 14,
    0x80, 0x40, 0xa0, 0xa0, 0xa0, 0xa0, 0x90, 0xa8, 0x94, 0x8a, 0x8a, 0x8a, 0x05, 0x85, 0x85, 0x85, 0x4a, 0x6a, 0x3a, 0x1a, 0x0a, 0xc4, 0x18, 0xe0, 
    0x0f, 0x30, 0x0e, 0x30, 0x03, 0x17, 0x14, 0x17, 0x13, 0x10, 0x00, 0x1e, 0x30, 0x00, 0x00, 0x30, 0x0e, 0x00, 0x32, 0x12, 0x11, 0x08, 0x04, 0x03, 
    };

    const uint8_t PROGMEM Chest_Open_Mask[] = {
    0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0xe0, 
    0x0f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 
    };

};