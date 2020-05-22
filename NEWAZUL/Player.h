#ifndef AZUL_PLAYER_H
#define AZUL_PLAYER_H

#include "LinkedList.h"

using std::string;

class Player
{
public:
	char name[30];
	int score;
	char** pattern;
	char board[5][5];
	LinkedList broken;
	//Constructor
	Player();
	//setter
	void setPlayer(string n, int score, char** p, char B[][5], LinkedList floor);
	//Destructor
	~Player();
};

#endif // AZUL_PLAYER_H