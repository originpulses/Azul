#ifndef AZUL_MOSAIC_H
#define AZUL_MOSAIC_H

#include <iostream>

#include "ColourSymbol.h"
#include "LinkedList.h"
#include "Player.h"

using std::cout;
using std::endl;

class Mosaic {

    public:
        Mosaic(Player* player);
        ~Mosaic();
        bool tilePlacing(int row, Colour c, int number);
        void checkTurn();
        bool checkWin();
        void printMosaic();
        bool isFirstPlayer();
        bool isPlayerTurn();
        LinkedList* returnTile();
        
        Player* getPlayer();
        Tile** getPointsBoard();
        Tile** getTurnsBoard();
        LinkedList* getRemaining();
        Tile* getBroken(int index);
        char** getPointCalculator();
        
        void setPlayer(Player* player);
        void setPointsBoard(Tile** pointBoard);
        void setTurnsBoard(Tile** turnBoard);
        void setRemaining(LinkedList* remaining);
        void setBroken(Tile* tile, int location);
        void setPointCalculator(char** pointCalculator);
        void setTurn(bool turn);
        void setFirst(bool first);
        
    private:
        
        void pointCalculation();
        
        Player* player;
        Tile** pointBoard;
        Tile** turnBoard;
        LinkedList* remaining;
        Tile* broken[BROKEN_LEN];
        char** pointCalculator;
        bool* colourCounting;
        
        bool currentTurn = false;
        bool containFirst = false;
        int brokenPts = 0;
};


#endif // AZUL_MOSAIC_H