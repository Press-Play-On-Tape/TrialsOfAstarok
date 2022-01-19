#pragma once

#include "Constants.h"

struct HighScoreVars {

    char initials[3];
    int8_t index = 0;

    void reset() {

        initials[0] = 'A';
        initials[1] = 'A';
        initials[2] = 'A';
        index = 0;

    }

};

struct SeedVars {

    uint8_t seed[5];
    uint8_t index;
    uint8_t arrowUp;
    uint8_t arrowDown;

    void incValue() {

        if (this->seed[this->index] == 5) {

            this->seed[this->index] = 0;
            
        }
        else {

            this->seed[this->index]++;

        }

        EEPROM.update(Constants::EEPROM_Seeds + this->index, this->seed[this->index]);
        
    }

    void decValue() {

        if (this->seed[this->index] == 0) {

            this->seed[this->index] = 5;
            
        }
        else {

            this->seed[this->index]--;

        }

        EEPROM.update(Constants::EEPROM_Seeds + this->index, this->seed[this->index]);
        
    }

    void incIndex() {

        if (this->index < 4) {

            this->index++;

        }
        
    }

    void decIndex() {

        if (this->index > 0) {

            this->index--;
            
        }
        
    }

    void reset() {

        for (uint8_t i = 0; i < 5; i++) {
            this->seed[i] = static_cast<uint8_t>(EEPROM.read(Constants::EEPROM_Seeds + i));
        }

        this->arrowDown = 0;
        this->arrowUp = 0;
        this->index = 0;
        
    }

    uint16_t getSeedValue() {

        return this->seed[0] * 1296 + 
               this->seed[1] * 216 +
               this->seed[2] * 36 +
               this->seed[3] * 6 +
               this->seed[4];
               
    }

};