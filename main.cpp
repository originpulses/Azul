#include "main.h"

int main(int argn, char** argl) {

	//Number of players
	int n_player = 2;
	const int Bsize = 6; //this is the size of mosaic
	//If recieve any value from command line then 
	//it will be set to the seed otherwise the default value for seed is 1
	int seed = 1;
	if (argn > 1) {

		if(argn > 1)
		seed = static_cast<int>(argl[1][0])-48;

		//Seeding the random number generator
		srand(seed);

		// Creating the box with 100 tiles(20 of each design)
		vector<char> box;

		// Creating the lid to place the extra tiles at the end of each round
		vector<char> lid;

		int choice = 0;
		bool valid = true;

		while (valid) {

				choice = mainMenu();

			if (choice == 1) {
				cout << "\nStarting a New Game\n";
				valid = newGame(box, lid, n_player, Bsize);
			}
			else if (choice == 2) {

				cout << "Enter the filename from which you want to load a game\n";
				cout << "> ";
				
				//Reading the name of file from to load the saved game
				char* name = new char[30];
				cin.getline(name, 30);
				try {

					valid = loadGame(box, lid, name, n_player, Bsize);
				}
				catch (const char* msg) {

					cout << msg << "\n";
					choice = 0;
				}
				delete[]name;
				name = nullptr;
			}
			else if (choice == 3) {

				Credits();
			}
			else if (choice == 4) {

				valid = false;
			}
		}
		cout << "\n\nGoodbye\n";
	}
	else {
		cout << "\nToo few command line parameters passed...\nYou need to at least pass Seed for random number generator\n\n";
	}	
	return 0;
}

//Function to show the Credits of the student
void Credits()
{
	cout << "\t\033[48;2;0;255;34;30m ================================\033[m\n\n";
	cout << "\t\033[1;37;41mDeveloped By: Syed Sabih Ali\033[m\n\n";
	cout << "\t\033[1;37;41mStudent ID: s3528350\033[m\n\n";
	cout << "\t\033[48;2;0;255;34;30m ================================\033[m\n\n";
}