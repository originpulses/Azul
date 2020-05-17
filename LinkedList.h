#ifndef AZUL_LINKEDLIST_H
#define AZUL_LINKEDLIST_H

#include "Node.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

// LinkedList
class LinkedList {

public:
   LinkedList();
   ~LinkedList();

// ADT's
   int getSize();
   Tile* get();
   bool remove(Tile* tile);
   void clear();

   void addFront(Tile* tile);
   void addBack(Tile* tile);
   
   void shuffle(int seed);
   void printAll();

private:
   int size;
   Node* head;
};

#endif // AZUL_LINKEDLIST_H