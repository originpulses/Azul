#ifndef AZUL_FACTORY_H
#define AZUL_FACTORY_H

#include <iostream>

#include "ColourSymbol.h"
#include "LinkedList.h"

using std::cout;
using std::endl;

class Factory {
    
    public:
        Factory(int noOfPlayer, int seed);
        ~Factory();
        int takeTile(Colour c, int factory);
        void addRemainder(Tile* tile);
        void printFactory();
        bool containColour(Colour c, int factory);
        bool isEmpty();
        void removeFirst();
        bool isFirst();
        void setUp(int seed);
        
        void setTileBag(LinkedList* tileBag);
        void setBoxLid(LinkedList* boxLid);
        void setNumOfFactory(int numOfFactory);
        void setFactories(Tile** factories);
        
        LinkedList* getTileBag();
        LinkedList* getBoxLid();
        int getNumOfFactory();
        Tile** getFactory();
        
    private: 
        LinkedList* tileBag;
        LinkedList* boxLid;
        int numOfFactory;
        Tile** factories;
        int leftover = 1;
        bool first;
        int size = 0;
        bool shuffled = false;
    };

#endif // AZUL_FACTORY_H