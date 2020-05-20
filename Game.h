#ifndef AZUL_GAME_H
#define AZUL_GAME_H
#include "Database.cpp"
#include "Factory.cpp"

class Game {
    
public:
    Game();
    void loadFactory(Factory* factory);
    void play();
};

#endif // AZUL_GAME_H