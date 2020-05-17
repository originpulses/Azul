#ifndef AZUL_PLAYER_H
#define AZUL_PLAYER_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Player {
    
public:
    Player(std::string name);
    ~Player();
    void setPoints(int points);
    int getPoints();
    void print();
    std::string getName();
    
private:
    std::string name;
    int pt;
};

#endif // AZUL_PLAYER_H