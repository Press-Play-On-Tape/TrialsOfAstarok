#include "InteractiveObject.h"
#include "../../SquarioGame.h"

uint8_t InteractiveObject::collide(int16_t tX, int16_t tY) {

    int16_t nX = tX / Constants::TileSize;
    int16_t nY = tY / Constants::TileSize;

    if (this->game->level.isTile(nX, nY)) {
        return 0xFF;
    }

    return this->game->level.checkObject(nX, nY);

}

void InteractiveObject::deactivate() {

    this->x = -1;
    this->y = -1;

}

ObjectTypes InteractiveObject::getType() {

    return this->type;

}