#include "Tile.h"

Tile::Tile() {

    this->colour = ' ';
}

Tile::Tile(Colour co) {

    this->colour = co;
}

void Tile::setColour(Colour co) {

    this->colour = co;
}

Colour Tile::getColour() {

    return this->colour;
}

bool Tile::isSameColour(Tile* tile) {

    if(tile->getColour() == this->colour) {

        return true;
    }

    return false;
}