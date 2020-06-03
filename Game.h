#ifndef AZUL_GAME_H
#define AZUL_GAME_H

#include <fstream>
#include <exception>

#include "Player.h"

using std::cin;
using std::ifstream;
using std::ofstream;
using std::ios;

//Function to display the main menu and take user's input according to the valid standards 
int mainMenu();

//This function initializes the mosaic, factories with default values and then call the gamePlay function with those value
bool newGame(vector<char> &box, vector<char> &lid, int n_player, const int Bsize);

//This function loads all required fields from saved file and then calls gamePlay() function
bool loadGame(vector<char>& box, vector<char> &lid ,char* name, int n_player, const int Bsize);

//This function is used to initialize the factories with default values
void initFactories( vector<vector<char> >&factories, vector<char> &box, vector<char> &lid);

//To check if the required row of board can hold the required colour
bool isColValid(char B[][6],const int Bsize, int row, char color);

//To print the all feilds of a player
void DisplayState(vector<vector<char> >factories, Player *player, int n_player,int turn, const int Bsize);

//The following function will be called by newGame() or loadGame() after populating the fields
//according to the desire of user e.g. everything from scratch (newGame) or load state of saved game (loadGame)
bool gamePlay(vector<char>& box, vector<char>& lid, Player*& players, vector<vector<char> >& factories, int turn, int n_player, const int Bsize);

//To save the present state of the game in txt file
void saveGame(vector<char>& box, vector<char>& lid, Player* players, vector<vector<char> >& factories, int turn, char* filename, int n_player, const int Bsize);

//This function will shuffle the tiles in the box
void shuffle(vector<char> &box);

//Return true if all factories are empty
bool isEmpty(vector<vector<char> >factories);

// Return true if the required factory can have this required colour char
bool charPossible(vector<vector<char> >factories, int inidex, char colour);

//index at which the current (colour) tile is supposed to be placed
int giveIndexOfColour(char B[][6], const int Bsize, int index, char colour);

//This function asks user to chose the index where the player wants to place the tile in corresponding wall
int askIndexOfColour(char B[][6], const int Bsize, int rows, char colour, bool & okay);

//To calculate the points of a player after each round
bool calcPoint(char B[][6], const int Bsize, char** &pattern, LinkedList &broken, int &score, vector<char>& lid, string Pname);

//Function to check the the game over state (if one row is completed on the box)
bool checkForRow(char B[][5]);

//To count the final score bonuses at the end of the game
void finalScoring(char B[][5], int& score);

//To count the number of rows in a text file
int countRows(char filename[]);

//To check either both files are equal or not
bool areFilesEqual(char N1[], char N2[]);

//This function will show the instructions for playing game
void instructions();

#endif // AZUL_GAME_H