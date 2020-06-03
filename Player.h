#ifndef AZUL_PLAYER_H
#define AZUL_PLAYER_H

#include "LinkedList.h"

using std::string;

class Player {

public:
	char name[30];
	int score;
	char** pattern;
	char board[6][6];
	LinkedList broken;
	//Constructor, Destructor
	Player();
	~Player();
	//setter
	void setPlayer(string n, int score, char** p, char B[][6], LinkedList floor);
};

#endif // AZUL_PLAYER_H