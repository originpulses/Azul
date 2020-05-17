#ifndef AZUL_NODE_H
#define AZUL_NODE_H

#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next);
   Node(Node& other);

   Tile* tile;
   Node* next;
};

#endif // AZUL_NODE_H