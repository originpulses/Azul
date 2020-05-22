#include "main.h"

int main(int argn, char** argl)
{
	//Number of players
	int n_player = 2;
	//If recieve any value from command line then 
	//it will be set to the seed otherwise the default value for seed is 1
	int seed = 1;
	if (argn > 1)
	{
		if(argn > 1)
		seed = static_cast<int>(argl[1][0])-48;
		/*
		char _file[30];
		int _i = 0;
		for (; argl[2][_i] != '\0'; _i++)
		{
			_file[_i] = argl[2][_i];
		}
		_file[_i] = '\0';

		int Size = countRows(_file); // TO get the number of inputs written in test file
		string* moves = new string[Size]; // Declaring a string of "Size" size to hold all moves/inputs
		int Index = 0;	// This shows the index of next executable move sent by test file
		
		//reading the name of test file
		char file[30];
		for (_i = 0; argl[3][_i] != '\0'; _i++)
		{
			file[_i] = argl[3][_i];
		}
		file[_i] = '\0';

		//opening the test file to read all commands/moves/inputs
		fstream fin;
		fin.open(_file);
		if (!fin)
		{
			cout << "Error opening the test file...\n";
		}
		else
		{
			for (int i = 0 ; i < Size ; i++ )
			{
				getline(fin,moves[i]);		// Reading all commands in out "moves" string
			}
			fin.close();
		}
		*/
		//Seeding the random number generator
		srand(seed);

		// Creating the box with 100 tiles(20 of each design)
		vector<char> box;
		// Creating the lid to place the extra tiles at the end of each round
		vector<char> lid;

		int choice = 0;
		bool valid = true;

		while (valid)
		{			
			//try
			//{
				choice = mainMenu(/*moves, Index, Size*/);
			/*}
			catch (char msg[])
			{
				cout << "Exception ";
				char _ff[] ="Index out of bound";
				char _ff2[] = "Invalid Input";
				if (msg == _ff)
				{
					cout << "Index out of bound, end of test file.\n";
					cout << "Terminating the program...\n";
					valid = false;
				}
				else if(msg == _ff2)
				{
					cout << msg << "\n";
				}
				choice = 0;
			}
			*/
			if (choice == 1)
			{
				cout << "\nStarting a New Game\n";
				valid = newGame(box, lid, n_player);
				//valid = newGame(box, lid, moves, Index, file, Size, n_player); // This was for testing
			}
			else if (choice == 2)
			{
				cout << "Enter the filename from which you want to load a game\n";
				cout << "> ";
				
				//Reading the name of file from to load the saved game
				char* name = new char[30];
				/*int i;
				for (i = 0 ;  moves[Index][i] != '\0' ; i++ )
				{
					name[i] = (char)moves[Index][i];
				}
				name[i-1] = '\0';
				//name[i] = '\0';
				cout << name << endl;
				Index++;
				//cin.ignore();
				*/
				cin.getline(name, 30);
				try
				{
					valid = loadGame(box, lid, name, n_player);
					//valid = loadGame(box, lid, name, moves, Index, file, Size, n_player);  // This was for testing
				}
				catch (const char* msg)
				{
					cout << msg << "\n";
					choice = 0;
				}
				delete[]name;
				name = nullptr;
			}
			else if (choice == 3)
			{
				Credits();
			}
			else if (choice == 4)
			{
				valid = false;
			}
		}
		//delete[] moves;
		//moves = nullptr;
		cout << "\n\nGoodbye\n";
	}
	else
	{
		cout << "\nToo few command line parameters passed...\nYou need to at least pass Seed for random number generator\n\n";
	}	
	return 0;
}

//Function to show the Credits of the team
void Credits()
{
	cout<<"=========================="<<endl;
	cout<< " Team Name: AZUL UNITED" <<endl;
	cout<<"==========================\n\n";
	cout<< "----------------------------------" <<endl;
	cout<< "Student 1:\n\n";
	cout<< "Name: Syed Sabih Ali" <<endl;
	cout<< "Student ID: s3528350" <<endl;
	cout<< "Email: s3528350@student.rmit.edu.au" <<endl;
	cout<< "----------------------------------\n\n";
	cout<< "----------------------------------" <<endl;
	cout<< "Student 2:\n\n";
	cout<< "Name: Carlo Manfredi" <<endl;
	cout<< "Student ID: s3545832" <<endl;
	cout<< "Email: s3545832@student.rmit.edu.au" <<endl;
	cout<< "----------------------------------\n\n";
	cout<< "----------------------------------" <<endl;
}