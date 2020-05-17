#ifndef AZUL_TILE_H
#define AZUL_TILE_H

#include "ColourSymbol.h"

class Tile {
    
public:
    Tile();
    Tile(Colour co);
    void setColour(Colour co);
    Colour getColour();
    bool isSameColour(Tile* tile);
    
private:
    Colour colour;
};

#endif // AZUL_TILE_H