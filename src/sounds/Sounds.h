#pragma once

namespace Sounds {

    PROGMEM const byte Verse [] = {
    0x90,47, 0,170, 
    0x80, 0,170, 
    0x90,47, 0,170, 
    0x80,
    0x90,54, 0,170,
    0x80, 0,170,
    0x90,54, 0,170,
    0x80,
    0x90,50, 0,170,
    0x80, 0,170,
    0x90,50, 0,170,
    0x80,
    0x90,52, 0,170,
    0x80, 0,170, 
    0x90,52, 0,170,
    0x80,
    0x90,52, 0,170,
    0x80, 0,170,
    0x90,52, 0,170,
    0x80, 0,170,
    0xf0};

    PROGMEM const byte PreChorus [] = {
    0x90,47, 0,85, 0x80, 0,85, 0x90,45, 0,170, 0x80, 0,170, 0x90,47, 0,170, 0x80, 1,84, 
    0x90,61, 0,170, 0x80, 0,170, 0x90,61, 0,170, 0x80, 0x90,61, 0,170, 0x80, 0x90,61, 0,170, 
    0x80, 0x90,61, 0,170, 0x80, 0x90,62, 0,170, 0x80, 0x90,59, 1,84, 0x80, 0xf0};

    PROGMEM const byte Chorus [] = {
    0x90,64, 0,227, 0x80, 0,227, 0x90,64, 0,227, 0x80, 0,227, 0x90,62, 3,141, 0x80, 0x90,62, 
    0,227, 0x80, 0,227, 0x90,62, 0,227, 0x80, 0,227, 0x90,61, 3,141, 0x80, 0x90,62, 0,227, 
    0x80, 0,227, 0x90,62, 0,227, 0x80, 0,227, 0x90,61, 3,141, 0x80, 0x90,61, 0,227, 0x80, 0,227, 
    0x90,61, 0,227, 0x80, 0,227, 0x90,59, 3,141, 0x80, 0xf0};

    #define nG3S         415  // 0x01
    #define nA3          440  // 0x02
    #define nB3          494  // 0x03
    #define nC4          523  // 0x04
    #define nD4          587  // 0x05
    #define nE4          659  // 0x06
    #define nG4S         831  // 0x07
    #define nA4          880  // 0x08
    #define nB4          988  // 0x09
    #define nC5          1047  // 0x0A
    #define nD5          1175  // 0x0B
    #define nE5          1319  // 0x0C
    #define nF5          1397  // 0x0D
    #define nG5          1568  // 0x0E
    #define nA5          1760  // 0x0F

    #define nA4S         932

    #define nB1          123  // 0x1
    #define nD2          147  // 0x2
    #define nF2          175  // 0x3
    #define nA2          220  // 0x4
    #define nD3          294  // 0x5
    #define nB5          1975 // 0xF
    #define nC5S         1109 // 0x9
    #define nD5S         1245 // 0xB
    #define nC6          2094 // 0xD
    #define nE6          2638 // 0xE

    PROGMEM const unsigned int SFXFrequencies [] {
    nB1, nD2, nF2,
    nA2, nD3, nA3, nD4,
    nC5, nC5S, nD5, nD5S, nE5,
    nC6, nE6, nB5
    };

    PROGMEM const byte SFX_Pipe [] = { 0, 32, 0xD1, 0xC1, 0xB1, 0xA3, 0xD1, 0xC1, 0xB1, 0xA1, 0xFF };
    PROGMEM const byte SFX_Hit [] = { 0, 16, 0xC1, 0xB1, 0xA1, 0x91, 0xFF };
    PROGMEM const byte SFX_Jump [] = { 0, 16, 0x21, 0x11, 0x31, 0x21, 0xFF };
    PROGMEM const byte SFX_Mushroom [] = { 0, 64, 0x41, 0x41, 0x51, 0x51, 0x61, 0x61, 0x71, 0x71, 0xFF };
    PROGMEM const byte SFX_Coin [] = { 0, 16, 0xF1, 0xE4, 0xFF };
    PROGMEM const byte SFX_Life [] = { 0, 32, 0xE3, 0xD3, 0xE3, 0xD3, 0xC5, 0x85, 0xFF };

};
