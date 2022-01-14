#pragma once

struct HighScoreVars {

    char initials[3];
    int8_t index = 0;
    char text[16];

    void reset() {

        initials[0] = 'A';
        initials[1] = 'A';
        initials[2] = 'A';
        index = 0;

        for (uint8_t i = 0; i < 16; i++) {

            text[i] = ' ';

        }
        
    }

};
