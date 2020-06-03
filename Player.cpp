#include "Player.h"

//Constructor
Player::Player() {}

//Destructor
Player::~Player() {

	for (int i = 0; i < 6; i++) {

		delete[]pattern[i];
	}
	delete[] pattern;
	std::vector<char> b;
	broken.removeAll(b, false);
}

//setter
void Player::setPlayer(string n, int score, char** p, char B[][6], LinkedList floor) {

	const int Bsize = 6;
	//Initializing the name of player
	int _i;
	for (_i = 0; n[_i] != '\0'; _i++) {

		name[_i] = n[_i];
	}
	name[_i - 1] = '\0';

	//initializing the score
	this->score = score;

	//Initializing the pattern board of player
	pattern = new char* [Bsize];
	for (int i = 0; i < Bsize; i++) {

		pattern[i] = new char[i + 1];
		for (int j = 0; j < (i + 1); j++) {

			pattern[i][j] = p[i][j];
		}
	}

	//Initializing the main tile board of player
	for (int i = 0; i < Bsize; i++) {

		for (int j = 0; j < Bsize; j++) {

			board[i][j] = B[i][j];
		}
	}

	//Initializing the broken tiles/floor of player
	Node* cur = floor.Head();
	while (cur != nullptr) {
		
		broken.insert(cur->data);
		cur = cur->next;
	}
}
