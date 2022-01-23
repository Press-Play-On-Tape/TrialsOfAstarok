#include "Room.h"

void Room::clearRoom() {
    for (int a = 0; a < Constants::RoomBytes; a++) data[a] = 0;
}

void Room::setTile(uint8_t x, uint8_t y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return;

    #ifdef NEW_ROOM
    data[x]     |= 1 << y;
    #else

    int index = (Constants::RoomHeight / 8) * x;
    if (y < 8) data[index]     |= 1 << y;
    else       data[index + 1] |= 1 << (y - 8);

    #endif
}

void Room::clearTile(uint8_t x, uint8_t y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return;

    #ifdef NEW_ROOM
    data[x]     &= ~(1 << y);
    #else

    int index = (Constants::RoomHeight / 8) * x;
    if (y < 8) data[index]     &= ~(1 << y);
    else       data[index + 1] &= ~(1 << (y - 8));

    #endif

}

bool Room::readTile(uint8_t x, uint8_t y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return false;

    #ifdef NEW_ROOM
    return (data[x] & (1 << y)) > 0;
    #else

    int index = (Constants::RoomHeight/8) * x;
    if (y < 8) {
        uint8_t mask = 1 << y;
        if (data[index] & mask) return true;
    }
    else {
        uint8_t mask = 1 << (y - 8);
        if (data[index + 1] & mask) return true;
    }
    return false;

    #endif

}
