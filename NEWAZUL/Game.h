#ifndef AZUL_GAME_H
#define AZUL_GAME_H

#include <fstream>

#include "Player.h"

using std::cin;
using std::ifstream;
using std::ofstream;
using std::ios;

// This function initializes the mosaic, factories with default values
//and then call the gamePlay function with those values
bool newGame(vector<char> &box, vector<char> &lid/*, string* moves, int& index, char* file, int Size*/, int n_player );

//This function loads all required fields from saved file and then calls gamePlay() function
//bool loadGame(vector<char>& box, vector<char> &lid ,char* name, string* moves, int &index, char* file, int Size, int n_player);
bool loadGame(vector<char>& box, vector<char> &lid ,char* name, int n_player);

//This function is used to initialize the factories with default values
void initFactories( vector<vector<char> >&factories, vector<char> &box, vector<char> &lid);

//To print the all feilds of a player
void DisplayState(vector<vector<char> >factories, Player &player);

//The following function will be called by newGame() or loadGame() after populating the fields
// according to the desire of user e.g. everything from scratch (newGame) or load state of saved game (loadGame)
bool gamePlay(vector<char>& box, vector<char>& lid, Player*& players, vector<vector<char> >& factories, int turn, int n_player);
//bool gamePlay(vector<char>& box, vector<char>& lid, Player*& players, vector<vector<char> >& factories, int turn, string* moves, int& index, char* file, int Size, int n_player);

//To save the present state of the game in txt file
void saveGame(vector<char>& box, vector<char>& lid, Player* players, vector<vector<char> >& factories, int turn, char* filename, int n_player);

//This function will shuffle the tiles in the box
void shuffle(vector<char> &box);

//Return true if all factories are empty
bool isEmpty(vector<vector<char> >factories);
// Return true if the required factory can have this required colour char
bool charPossible(vector<vector<char> >factories, int inidex, char colour);

//Gives the index of tile in the row in required required row
//As in each row of 5x5 board, tiles are nore placed randomly
//They are palces in a specific sequence, This function simply returns the 
//index at which the current (coluor) tile is supposed to be placed
int giveIndexOfColour(char B[][5], int index, char colour);
//To calculate the points of a player after each round
void calcPoint(char B[][5], char** &pattern, LinkedList &broken, int &score, vector<char>& lid, string Pname);
//Function to check the the game over state (if one row is completed on the box)
bool checkForRow(char B[][5]);

//To count the final score bonuses at the end of the game
void finalScoring(char B[][5], int& score);

//To count the number of rows in a text file
int countRows(char filename[]);

//To check either both files are equal or not
bool areFilesEqual(char N1[], char N2[]);

#endif // AZUL_GAME_H