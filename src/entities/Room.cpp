#include "Room.h"

void Room::clearRoom() {
    for (int a = 0; a < Constants::RoomBytes; a++) data[a] = 0;
}

void Room::setTile(int x, int y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return;

    int index = (Constants::RoomHeight / 8) * x;
    if (y < 8) data[index]     |= 1 << y;
    else       data[index + 1] |= 1 << (y - 8);

}

void Room::clearTile(int x, int y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return;

    int index = (Constants::RoomHeight / 8) * x;

    if (y < 8) data[index]     &= ~(1 << y);
    else       data[index + 1] &= ~(1 << (y - 8));

}

bool Room::readTile(int x, int y) {

    if (x > Constants::RoomWidth || y > Constants::RoomHeight) return false;

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
}