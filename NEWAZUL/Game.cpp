#include "Game.h"

//-------------------------------Some basic and some extra (but important) fucntions
//Function to display the main menu and take user's input
//according to the valid standards 
int mainMenu(/*string* moves, int &index, int Size*/)
{
	int choice = 0;
	cout << "Menu\n";
	cout << "----\n";
	cout << "1. New Game\n";
	cout << "2. Load Game\n";
	cout << "3. Credits (Show student information)\n";
	cout << "4. Quit\n\n> ";
	
	string input;

	getline(cin,input);
	if (std::cin.eof())
	{
		return 4;
	}
	char temp = (char)input[0];
	choice = static_cast<int>(temp)-48;
	while((input.size() != 1 ) || !(choice >=1 && choice <= 4))
	{
		cout << "Invalid Input, Enter again\n";
		cout << "> ";
		getline(cin, input);
		if (std::cin.eof())
		{
			return 4;
		}
		char temp = (char)input[0];
		choice = static_cast<int>(temp)-48;
	}
	/*if (index >= Size)
	{
		throw "Index out of bound";
	}
	else
	{
		char temp = '\0';
		temp = moves[index][0];
		choice = static_cast<int>(temp) - 48;
		cout << temp << "\n";
		index++;

		while (!(choice >= 1 && choice <= 4) && index < Size)
		{
			cout << "Invalid Input, Enter again\n";
			cout << "> ";

			char temp = '\0';
			temp = moves[index][0];
			choice = static_cast<int>(temp) - 48;
			cout << temp << "\n";
			
			index++;
			//cin >> choice;
		}
		if (!(choice >= 1 && choice <= 4))
		{
			throw "Index out of bound";
		}
	}
	*/
	return choice;
}

// To Shuffle the box of tiles
void shuffle(vector<char> &box)
{
	char temp = '\0';
	for (size_t i = 0; i < 500; ) {
		int i1 = (rand()%box.size());
		int i2 = (rand()%box.size());
		
		if (i1 != i2) {
			//Swapping ranks of 2 random cards
			temp = box[i2];
			box[i2] = box[i1];
			box[i1]  = temp;
			i++;
		}
	}
}
int countRows(char filename[])
{

	int count = 0;
	ifstream fin;
	fin.open(filename);
	if (!fin)
	{
		cout << "Error opening the file...\n";
	}
	else
	{
		char tempp = '.';
		while (!fin.eof())
		{
			if (tempp == '\n')
			{
				count++;
			}
			fin.get(tempp);
		}
	}
	fin.close();
	return count + 1; // +1 because last line contains eof character instead of '\n'
}
bool areFilesEqual(char N1[], char N2[])
{
	ifstream f1(N1);
	bool equals = true;
	if (!f1.is_open())
	{
		cout << "Error opening the files to be compared...\n";
		return false;
	}
	else
	{
		ifstream f2(N2);
		if (f2.is_open())
		{
			if (countRows(N1) == countRows(N2))
			{
				char temp1 = '\0';
				char temp2 = '\0';
				while (!f1.eof() && !f2.eof() && equals)
				{
					f1.get(temp1);
					f2.get(temp2);
					if ((temp1 != temp2))
					{
						if (temp1 != '\n')
							equals = false;
						else
							f1.get(temp1);
					}
				}
				if (!f1.eof() || !f2.eof())
				{
					equals = false;
				}
			}
			else
			{
				equals = false;
			}
		}
		else
		{
			cout << "Error opening the files to be compared...\n";
			return false;
		}
	}
	return equals;
}

bool newGame(vector<char> &box, vector<char> &lid, /*string* moves, int& index, char* file, int Size, */int n_player)
{
	//Creating factories
	vector<vector<char> >factories;	// Vector to save the factories
	box.clear();
	// Placing 20 tiles of each design to initialize the box
	for (size_t i = 0; i < 20; i++)
	{
		box.push_back('R');
	}
	for (size_t i = 0; i < 20; i++)
	{
		box.push_back('Y');
	}
	for (size_t i = 0; i < 20; i++)
	{
		box.push_back('B');
	}
	for (size_t i = 0; i < 20; i++)
	{
		box.push_back('L');
	}
	for (size_t i = 0; i < 20; i++)
	{
		box.push_back('U');
	}
	//Shuffling the initialized box
	shuffle(box);
	//Placing the last 20 tiles from the box in all factories(except central) as 4 tiles each
	initFactories(factories, box, lid);		// initializing factories

	// Initializing players
	Player* players = new Player[n_player];
	for (int x = 0; x < n_player; x++)
	{
		cout << "Enter a name for player " << (x+1) << "\n> ";
		cin.getline(players[x].name,30);
		
		//Declaring the pattern board of both players
		/*
				 . ||
			   . . ||
			 . . . ||
		   . . . . ||
		 . . . . . ||
		*/
		//--------------------------------------------------------------------
		players[x].pattern = new char* [5];
		for (int i = 0; i < 5; i++)
		{
			players[x].pattern[i] = new char[i + 1];
			for (int j = 0; j < i + 1; j++)
			{
				players[x].pattern[i][j] = '.';
			}
		}
		//--------------------------------------------------------------------
		//Declaring and initializing the tile board
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				players[x].board[i][j] = '.';
			}
		}
	}

	cout << "\nLet's Play!\n\n";
	bool ret;

	//ret = gamePlay(box,lid, players,factories,1,moves,index,file,Size,n_player);
	ret = gamePlay(box,lid, players,factories,1, n_player);
	//delete[]file;
	if (players != nullptr)
	{
		delete[]players;
		players = nullptr;
	}
	return ret;
}
//bool loadGame(vector<char> &box, vector<char> &lid,char* name, string* moves, int& index, char *file, int Size, int n_player)
bool loadGame(vector<char> &box, vector<char> &lid,char* name, int n_player)
{
	ifstream fin;
	fin.open(name);
	if (!fin)
	{
		throw "Exception! Error opening the file";
	}
	else
	{

		if (fin.peek() == std::ifstream::traits_type::eof())
		{
			throw "Exception! No saved Game found...\n";
		}
		else
		{
			int turn = -1;
			string toBeignored = "";

			getline(fin,toBeignored);	//To read the comment line
			getline(fin,toBeignored);	//To read the comment line

			//--------------------------- Going to load bag							
			// Removing all already present tiles (if any) from the box
			//so that new tiles can be placed
			box.clear();
			// At last, loading the remaining box of tiles in the txt file
			char tempp = '\0';
			getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
			fin.get(tempp);
			while (tempp != '\n')
			{
					box.push_back(tempp);
					fin.get(tempp);
			}
			box.pop_back();
			//--------------------------- Going to load lid
			// Removing all already present tiles (if any) from the lid
			//so that new tiles can be placed
			lid.clear();

			getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign

			// Loading the tiles on the top of lid (if any)

			fin.get(tempp);
			while (tempp != '\n')
			{
				lid.push_back(tempp);
				fin.get(tempp);
			}
			lid.pop_back();
			//--------------------------- Going to load the factories

			vector<vector<char> >factories;	// Vector to save the factories
			tempp = '\0';
			for (int i = 0; i < 6; i++)
			{
				getline(fin, toBeignored, '=');	//To read the comment line till "=" sign
				vector<char> fac;
				fin.get(tempp);
				while (tempp != '\n')
				{
					fac.push_back(tempp); // Randomly generated tiles
					fin.get(tempp);
				}
				factories.push_back(fac);
			}	

			//--------------------------- Going to load the Players

			Player* players = new Player[n_player];

			getline(fin, toBeignored);	//To read the comment line
			for (int w = 0; w < n_player; w++)
			{
				getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign

				//Loading the names of players	
				fin.getline(players[w].name,30);
				int g = 0;
				while (players[w].name[g] != '\0')
				{
					g++;
				}
				players[w].name[g - 1] = '\0';
				//Now going to read the score
				getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
				fin >> players[w].score;
				fin.get(tempp);

				//Loading the factory display (Triangle)

				players[w].pattern = new char* [5];
				for (int i = 0; i < 5; i++)
				{
					getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
					players[w].pattern[i] = new char[i + 1];
					fin.get(tempp);

					if (tempp == '\n' || tempp == '-') //it means the row is empty
					{
						for (int j = 0; j < i + 1; j++)
						{
							players[w].pattern[i][j] = '.';
						}
					}
					else
					{
						int j;
						for (j = 0; j < i + 1 && tempp != '\n'; j++)
						{
							players[w].pattern[i][j] = tempp;
							fin.get(tempp);
						}
						if (j < (i + 1))
						{
							while (j < (i + 1))
							{
								players[w].pattern[i][j] = '.';
								j++;
							}
						}
					}
				}

				// Now going to read the penalty tiles(if any)
					// Now loading the broken tiles of both players
				tempp = '\0';
				getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign

				//Broken tiles of player 1
				fin.get(tempp);
				while (tempp != '\n')
				{
					players[w].broken.insert(tempp);
					fin.get(tempp);
				}

				//Loading the tile board
		
				//Board of player 
				for (int i = 0; i < 5; i++)
				{
					getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
					for (int j = 0; j < 5; j++)
					{
						fin.get(tempp);
						if (tempp == '-')
						{
							players[w].board[i][j] = '.';
						}
						else
						{
							players[w].board[i][j] = tempp;
						}
					}
					fin.get(tempp); // To ignore the end of line character in file
				}
			}
			//-----------------------------------------------------------
			getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
			fin >> turn;


			fin.close();
			cout << "Azul game successfully loaded\n";
	        cout << "< game play continues from here > \n\n";
			bool ret = true;
			//ret = gamePlay(box, lid , players, factories, turn, moves, index, file, Size, n_player);
			ret = gamePlay(box, lid , players, factories, turn, n_player);
			if (players != nullptr)
			{
				delete []players;
			}
			return ret;
		}
		return true;
	}
}
void initFactories(vector<vector<char> > &factories, vector<char> &box, vector<char> &lid)
{
	//If the box is empty/or have insufficient tiles then shift all tiles from the lid into the box
	if (box.size() < 20)
	{
		size_t lidSize = lid.size();
		for (size_t i = 0 ; i < lidSize ; i++)
		{
			box.push_back(lid[i]);
		}
		//Removing those all tiles from the lid
		lid.clear();
	}

	//The central Factory
	vector<char> center;
	center.push_back('F');		// First turn brick
	factories.push_back(center);
	center.clear();
	
	//Now going to randomly generate remaining 5 factories 
	size_t index = 1;
	//Now going to place tiles in other 5 facctories
	for (size_t i = 0; i < 5; i++)
	{
		vector<char> fac;		
		for (size_t i = 0; i < 4; i++)
		{
			fac.push_back(box[box.size() - index]); // Adding last 4 tiles from the box in factories
			index++;
		}
		factories.push_back(fac);
		fac.clear();
	}
	//for(int i = 0 ;i < 6 ; i++)
	//factories[i].erase(factories[i].begin());

	box.resize(box.size() - 20);	 // To remove the tiles from box which are moved in factory
}
void DisplayState(vector<vector<char> >factories, Player &player)
{
	//cout << "TURN FOR PLAYER: " << player << "\n";
	//printf("TURN FOR PLAYER:%s\n" , player.name );
	cout << "TURN FOR PLAYER:" <<  player.name  << "\n";
	cout << "Factories:\n";
	for (size_t i = 0 ; i < factories.size() ; i++)
	{
		//printf("%ld: ",i);
		cout << i << ": ";
		for (size_t j = 0 ; j < factories[i].size() ; j++)
		{
			if(factories[i][j] == 'F' || factories[i][j] == 'B' || factories[i][j] == 'Y' || factories[i][j] == 'R' || factories[i][j] == 'U' || factories[i][j] == 'L')
				//printf("%c ",factories[i][j]);
				cout << factories[i][j] << " ";
		}
		//printf("\n");
		cout << "\n";
	}

	//printf("\nMosaic for %s\n",player.name);
	cout << "\nMosaic for " << player.name << "\n";
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ": ";
		for (int j = 0; j < 4 - i; j++)
		{
			cout << "  ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << player.pattern[i][j] << " ";
		}

		cout << " || ";
		for (int j = 0; j < 5; j++)
		{
			cout << player.board[i][j] << " ";
		}
		cout << "\n";
	}
	//printf("broken: ");
	player.broken.print();
	cout << "\n";
}
void saveGame(vector<char> &box, vector<char> &lid, Player* players, vector<vector<char> >& factories, int turn, char* filename, int n_player)
{
	ofstream fout;
	fout.open(filename, ios::out);
	if (!fout)
	{
		cout << "Error opening the file to save the game...\n";
	}
	else
	{
		//Writing the factories
		fout << "# This is a comment line, and is optional\n";
		fout << "# Multiline comments are just multiple single line comments\n";

		fout << "BAG=";
		// Now writing the lid (tiles places on lid, if any) in tha txt file
		//Now going to remove some unwanted friends from the vector
		int v_size = static_cast<int>(box.size());
		for (int i = 0; i < v_size; i++)
		{
			if (box[i] != 'F' && box[i] != 'B' && box[i] != 'Y' && box[i] != 'R' && box[i] != 'U' && box[i] != 'L')
			{
				box.erase(box.begin() + i);
				i--;
				v_size--;
			}
		}
		for (size_t i = 0; i < box.size(); i++)
		{

			fout << box[i];
		}
		fout << "\n";

		//Now going to remove some unwanted friends from the vector
		v_size = static_cast<int>(lid.size());
		for (int i = 0; i < v_size; i++)
		{
			if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L')
			{
				lid.erase(lid.begin() + i);
				i--;
				v_size--;
			}
		}
		fout << "LID=";
		// At last, writing the remaining box of tiles in the txt file
		for (size_t i = 0; i < lid.size(); i++)
		{
			if(lid[i] != '\0' && lid[i] != '\n')
			   fout << lid[i];
		}
		fout << "\n";

		
		
		for (size_t i = 0; i < factories.size(); i++)
		{
			if (i == 0)
			{
				fout << "FACTORY_CENTRE=";
			}
			else
			{
				fout << "FACTORY_" << i << "=";
			}
			for (size_t j = 0; j < factories[i].size(); j++)
			{	
				fout << factories[i][j];
			}
			fout << "\n";
		}
	
		fout << "# Could use comments to separate sections\n";

		//Writing the information of player 1

		for (int x = 0; x < n_player; x++)
		{
			fout << "PLAYER_" << (x + 1) << "_NAME=" << players[x].name << "\n";
			fout << "PLAYER_" << (x + 1) << "_SCORE=" << players[x].score << "\n";


			for (size_t i = 0; i < 5; i++)
			{
				fout << "PLAYER_" << (x + 1) << "_PATTERN_LINE" << (i + 1) << "=";
				for (size_t j = 0; j < i + 1; j++)
				{
					fout << players[x].pattern[i][j];
				}
				fout << "\n";
			}

			fout << "PLAYER_" << (x + 1) << "_FLOOR_LINE=";
			//writing broken tiles of both players
			if (players[x].broken.Head() != nullptr)
			{
				Node* cur = players[x].broken.Head();
				while (cur != nullptr)
				{
					if (cur->data == 'F' || cur->data == 'B' || cur->data == 'Y' || cur->data == 'R' || cur->data == 'U' || cur->data == 'L')					
					fout << cur->data;

					cur = cur->next;
				}
			}
			fout << "\n";
			//Board of player 1
			for (size_t i = 0; i < 5; i++)
			{
				fout << "PLAYER_" << (x + 1) << "_MOSAIC_" << (i + 1) << "=";
				for (size_t j = 0; j < 5; j++)
				{
					fout << players[x].board[i][j];
				}
				fout << "\n";
			}
		}
		//---------------------------------------------------------------------------
		// The turn(which player will play first in next round)
		fout << "CURRENT_PLAYER="<< turn;
		

		cout << "Game successfully saved to \'" << filename << "\'\n";
		cout << "< Gameplay continues until end - of - game > " << "\n\n";
		//closing the txt file
		fout.close();
	}
}
bool isEmpty(vector<vector<char> >factories)
{
	bool empty = true;
	size_t zero = 0;
	if (factories.size() == zero)
	{
		empty = false;
	}
	else
	{
		for(size_t i = 0 ; i < factories[0].size() && empty; i++)
		{
			if (factories[0][i] != 'F' || factories[0][i] != 'B' || factories[0][i] != 'Y' || factories[0][i] != 'R' || factories[0][i] != 'U' || factories[0][i] != 'L')
			{
				empty = false;
			}

		}
		for (size_t i = 1; i < factories.size() && empty; i++)
		{
			if (factories[i].size() != 0)
			{
				empty = false;
			}
		}
	}
	return empty;
}
bool charPossible(vector<vector<char> >factories, int index , char colour)
{
	bool check = false;
	for (size_t i = 0 ;i < factories[index].size() && !check; i++)
	{
		if (factories[index][i] == colour)
		{
			check = true;
		}
	}
	return check;
}
int  giveIndexOfColour(char B[][5], int index , char colour)
{
	char row[5] = {'B','Y','R','U','L'};
	for (int i = 0 ;i < index ; i++)
	{
		char temp = row[4];
		for (int j = 4 ; j > 0 ; j--)
		{
			row[j] = row[j - 1];
		}
		row[0] = temp;
	}
	index = -1;
	bool cond = true;
	for (int i = 0; i < 5 && cond; i++)
	{
		if (row[i] == colour)
		{
			index = i;
			cond = false;
		}
	}
	return index;
}
void calcPoint(char B[][5], char** &pattern, LinkedList &broken, int &score,vector<char> &lid ,string Pname)
{
	int roundScore = 0;
	bool complete = true;
	// First things first, moving all completed rows's tile colour to the right side row of mosaic
	for (int rows = 0; rows < 5; rows++)
	{
		complete = true;
		//checking for completed line
		char first = '.';
		if (pattern[rows][0] != '.' && pattern[rows][0] != '\0' && pattern[rows][0] != '\n')
		{
			first = pattern[rows][0]; //Placed the tile type contained by this current row
			//The following loop checks either row is full with same tiles of not
			bool cond = true;
			for (int i = 0; i < rows + 1 && cond; i++)
			{
				if (pattern[rows][i] != first)
				{
					complete = false;
					cond = false;	// just to break the loop
				}
			}
			//If row is full of same tiles then should move this tile to the right side
			//of mosaic
			if (complete)
			{
				int col = -1;
				col = giveIndexOfColour(B, rows, first);

				//shifting the colour to the corresponding block at right side of the mossaic
				B[rows][col] = first;

				//Now calculating the points of this tile
				int count = 0;
				bool check1 = false;
				//Checking for adjacent tiles in the row
				for (int i = col + 1; i < 5 && B[rows][i] != '.'; i++)
				{
					check1 = true;
					count++;
				}
				for (int i = col - 1; i >= 0 && B[rows][i] != '.'; i--)
				{
					check1 = true;
					count++;
				}
				if (check1)
				{
					count++;
				}

				//Checking for adjacent tiles in the row
				bool check2 = false;
				for (int i = rows + 1; i < 5 && B[i][col] != '.'; i++)
				{
					check2 = true;
					count++;
				}
				for (int i = rows - 1; i >= 0 && B[i][col] != '.'; i--)
				{
					check2 = true;
					count++;
				}
				if (check2)
				{
					count++;
				}


				if (count == 0)// If the tile had no adjacent tiles
				{
					roundScore++;
				}
				else	//If tile had adjacent tile(s) then adding score accordingly
				{
					roundScore += count;
				}
				count = 0;

				//moving all remaining tiles to the lid
				int i;
				for (i = 0; i < rows ; i++)
				{
					lid.push_back(first);
					pattern[rows][i] = '.';
				}
				pattern[rows][i] = '.';
				//lid.pop_back();	
			}
		}
	}
	//lid.pop_back();
	int count = 0;
	int rate = -1;
	int brokenTiles = broken.getSize();
	Node* cur = broken.Head();
	while (cur != nullptr)
	{
		if(cur->data != 'F' && cur->data != 'B' && cur->data != 'Y' && cur->data != 'R' && cur->data != 'U' && cur->data != 'L')
		brokenTiles--;
		cur = cur->next;
	}

	for (int i = 1; i <= brokenTiles; i++)
	{
		if (i == 3)
		{
			rate = -2;
		}
		else if (i == 6)
		{
			rate = -3;
		}
		count += rate;
	}
	if (brokenTiles > 0)
	{
		broken.removeAll(lid, true);
	}
	roundScore += count;
	score += roundScore;
	cout << "***** Score board of player " << Pname << "\n\n";
	cout << "Total points deducted for broken tiles: " << count << ".\n";
	cout << "Score of this round: " << roundScore << ".\n";
	cout << "Total score of after this round: " << score << ".\n\n";
}
bool checkForRow(char B[][5])
{
	bool check = false;
	for (size_t i = 0 ; i < 5 && !check ; i++)	//if check is true then it means we have found a complete row
	{
		size_t j = 0;
		for (j = 0; j < 5 && !check; j++)
		{
			if (B[i][j] == '.')
			{
				check = true;	//TO break the loop
			}
		}
		check = false;	// So if
		if (j == 5)	// If above row had no vacant space, it means it is completed 
		{
			check = true;	//a complete row is found
		}
	}
	return check;
}
void finalScoring(char B[][5] , int &score)
{
	bool cond = true; // This bool is just to break the the loops if some condition(s) are meet 
	//Checking for all complete rows 
	for (int i = 0; i < 5 ; i++)
	{
		int j = 0;
		cond = true;
		for (j = 0; j < 5 && cond; j++)
		{
			if (B[i][j] == '.')
			{
				cond = false;
				j--;
			}
		}
		if (j == 5)	// If above row had no vacant space, it means it is complete
		{
			score += 2;	//So here are the extra 2 points for each complete row
		}
	}

	cond = true;
	//Checking for all complete columns
	for (int i = 0; i < 5 ; i++)
	{
		int j = 0;
		for (j = 0; j < 5 && cond; j++)
		{
			if (B[j][i] == '.')
			{
				cond = false;
				j--;
			}
		}
		if (j == 5)	// If the current column had no vacant space, it means it is complete 
		{
			score += 7;	//So here are the extra 7 points for each complete column
		}
	}

	//now going to calculate that how many times thiss player 
	//managed to fill in all five tiles for one colour

	//This array will contain the count of each colour tile in the final board
	//at indiviual index
	/*
	
	[0] holds count for Red (R)
	[1] holds count for Yellow (Y)
	[2] holds count for Dark blue (B)
	[3] holds count for Light Blue (L)
	[4] holds count for Black (U)

	*/
	int colourCount[5] = {0};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (B[i][j] == 'R')
			{
				colourCount[0]++;
			}
			else if (B[i][j] == 'Y')
			{
				colourCount[1]++;
			}
			else if(B[i][j] == 'B')
			{
				colourCount[2]++;
			}
			else if (B[i][j] == 'L')
			{
				colourCount[3]++;
			}
			else if (B[i][j] == 'U')
			{
				colourCount[4]++;
			}
		}
	}
	//At this point we have count of occurunces of each colour
	
	// Now we will find the minimum number for which each colour occured
	int min = 9999999;
	for (int i = 0 ; i < 5 ; i++) // Finding the minimum number of occurence of a tile
	{
		if (colourCount[i] < min)
		{
			min = colourCount[i];
		}
	}
	//now going to check if all colours have occurred minimum for min times (Note: the min can be 0 so
	// if a tiles has occurred not even once then even tat condition get covered under this)
	int i;
	cond = true;
	for (i = 0; i < 5 && cond; i++) // Finding the minimum number of occurence of a tile
	{
		if (min > colourCount[i])
		{
			cond = false;
		}
	}

	if (cond)	//this means that min contains the number of times for which all colours occurred at least
	{
		//10 points for each time, all colours occureds.
		//if all colours occured not even once then min will be 0, hence no effect on scoring 
		score += (min * 10);
	}
}
//bool gamePlay(vector<char>& box, vector<char>& lid, Player*& players , vector<vector<char> >& factories, int turn, string* moves, int& index, char* file, int Size, int n_player)
bool gamePlay(vector<char>& box, vector<char>& lid, Player*& players , vector<vector<char> >& factories, int turn, int n_player)
{
	bool loop = true;
	bool round = true;
	bool endGame = true;
	bool quit = false;
	bool firstTileFirstCheck = false;
	bool isShow = true;
	cout << "\t\t\t *INSTRUCTIONS*\n\n";
	cout << "\t\t\tInput formats: <type> <factory> <colour> <storage row>\n\n";
	cout << "\t\t\t1. First you will type the command name e.g. turn, save or -1.\n";
	cout << "\t\t\t   only these 3 are valid command names\n\n";
	cout << "\t\t\t2. Then with a SPACE you will write the number of factory from which you\n";
	cout << "\t\t	   want to pick tiles. (This MUST be an integer (range 0 - 5) )\n\n";
	cout << "\t\t\t3. Then with a SPACE you will write the colour of tile you want to pick\n";
	cout << "\t\t\t   from that specified factory. (Valid colours: R, Y, B, L, U) all other inputs are invalid.\n\n";
	cout << "\t\t\t4. Then at last, with a SPACE you will write the numebr of storage row.\n";
	cout << "\t\t\t   (This MUST be an integer (range 1 - 5) )\n\n";
	cout << "\t\t\t5. At any moment a player can enter -1 to exit the game and terminate \n";
	cout << "\t\t\t   the program. (CAUTION: All unsaved progress will be lost)\n\n";
	while (endGame && round)	// This loop controls the rounds
	{
		cout << "\t=== Start Round ===\n";
		string input = "";
		bool check = true; 
		bool ifFirstTileGained = false; 
		bool isFirst = false;
		while (loop && round)	// This loop is responsible for back to back turns of players in one round
		{
				DisplayState(factories, players[turn - 1]);

				check = true;
				while (check)
				{
					cout << "> ";
					getline(cin,input);
					isShow = true;
					/*if (index >= Size)
					{
						cout << "Test file out of commands!\n";
						input = "-1";
					}
					else
					{
						int i;
						input = "";
						for (i = 0; moves[index][i] != '\0'; i++)
						{
							input += moves[index][i];
						}
						input.pop_back();

						cout << input << endl;
						index++;
					}*/
					if (input.substr(0, 5) == "turn " && input.size() == 10)
					{
						char _f_ = input[5];
						int _f = static_cast<int>(_f_) - 48;

						char _colour = (char)input[7];

						char _row = input[9];
						int _r = static_cast<int>(_row) - 48;


						if ((_f >= 0 && _f <= 5) && (_colour == 'R' || _colour == 'Y' || _colour == 'B' || _colour == 'L' || _colour == 'U') && (_r >= 1 && _r <= 5))
						{
							_r--; //As rows in array start from 0 not 1

							if (charPossible(factories, _f, _colour))
							{
								//Checking if the corresponding tiles board already have the required colour or not
								bool valid = true;

								int INDEX = -1;
								INDEX = giveIndexOfColour(players[turn - 1].board, _r, _colour);
								if (players[turn - 1].board[_r][INDEX] == _colour)
								{
									valid = false;
								}
								//Now going to check if the required row of mosaic pattern board can hold the required colour
								int possibleTiles = 0;
								if (valid)
								{
									bool _cond = true; // Just to break the loop if specific condition meets
									for (int i = 0; i < _r + 1 && _cond; i++)
									{
										if (players[turn - 1].pattern[_r][i] != '.' && players[turn - 1].pattern[_r][i] != _colour)
										{
											valid = false;
											_cond = false;
										}
										else
										{
											if (players[turn - 1].pattern[_r][i] == '.')
												possibleTiles++;
										}
									}
								}
								if (possibleTiles == 0)
								{
									cout << "Required row is full, can not place more tiles in it\n";
									valid = false;
									isShow = false;
								}
									//At this moment we know that the location is alright to place the tiles in mosaic
								if (valid)
								{
									//checking for First turn tile in central factory
									if (!isFirst && _f == 0)
									{
										bool _cond = true; // Just to break the loop if specific condition meets
										for (size_t i = 0; i < factories[_f].size() && _cond; i++)
										{

											if (factories[_f][i] == 'F')
											{
												isFirst = true;
												_cond = false;
											}
										}
										if (isFirst && !firstTileFirstCheck)
										{
											firstTileFirstCheck = true;
											cout << players[turn - 1].name << " got the first player tile.\n";
										}
									}
									int actual = 0;
									vector<char> temp_central_F;
									vector<char> temp_central_F0;
									ifFirstTileGained = false;
									for (size_t i = 0; i < factories[_f].size(); i++)
									{
										if (factories[_f][i] == 'F') // if we are in central factory and firstplayer tile is still there
										{							 // then it moves to the broken tiles of respective player
											if (factories[_f][i] == 'F' || factories[_f][i] == 'B' || factories[_f][i] == 'Y' || factories[_f][i] == 'R' || factories[_f][i] == 'U' || factories[_f][i] == 'L') {
												players[turn - 1].broken.insert(factories[_f][i]);
												ifFirstTileGained = true;
											}
										}
										else if (factories[_f][i] == _colour)//counting the same colur tiles
										{
											actual++;
										}
										else	//All other tiles will be moved to the central factory
										{
											//	if (_f != 0)
											if (factories[_f][i] == 'F' || factories[_f][i] == 'B' || factories[_f][i] == 'Y' || factories[_f][i] == 'R' || factories[_f][i] == 'U' || factories[_f][i] == 'L')
												temp_central_F.push_back(factories[_f][i]);
										}
									}
									if (_f != 0)
									{
										if (!ifFirstTileGained)
										{
											for (size_t i = 0; i < factories[0].size(); i++)
											{
												if (factories[0][i] == 'F' || factories[0][i] == 'B' || factories[0][i] == 'Y' || factories[0][i] == 'R' || factories[0][i] == 'U' || factories[0][i] == 'L')
													temp_central_F0.push_back(factories[0][i]);
											}
										}
										else
										{
											for (size_t i = 1; i < factories[0].size(); i++)	// Skipping the first player tile
											{
												if (factories[0][i] == 'F' || factories[0][i] == 'B' || factories[0][i] == 'Y' || factories[0][i] == 'R' || factories[0][i] == 'U' || factories[0][i] == 'L')
													temp_central_F0.push_back(factories[0][i]);
											}
										}
									}	//This process is to update the central factory
									factories[0].clear();
									for (size_t i = 0; i < temp_central_F0.size(); i++)
									{
										factories[0].push_back(temp_central_F0[i]);
									}
									for (size_t i = 0; i < temp_central_F.size(); i++)
									{
										factories[0].push_back(temp_central_F[i]);
									}

									// Now "possibleTiles" shows the number of tiles we can place in out left mosaic's selected row
									// and "actual" shows the actual number of tiles we have

									// So now we can remmove all tiles from the factory
									if (_f != 0)
										factories[_f].clear();


									//Now placing the tiles in left side of mosaic
									int i = 0;
									while (players[turn - 1].pattern[_r][i] != '.' && i < (_r + 1))
										i++;

									int j;
									for (j = 0; j < actual && i < (_r + 1) && players[turn - 1].pattern[_r][i] == '.'; j++, i++)
									{
										players[turn - 1].pattern[_r][i] = _colour;
									}

									int x = 0;
									if (actual - possibleTiles >= 0)
									{
										for (x = 0; x < actual - possibleTiles; x++)	// Adding the remaining tiles(if any) to the bottom of the mat
										{
											if (_colour == 'F' || _colour == 'B' || _colour == 'Y' || _colour == 'R' || _colour == 'U' || _colour == 'L')
											players[turn - 1].broken.insert(_colour);
										}
									}
									cout << "Turn successful.\n\n";
									if (turn == 1)
									{
										turn = 2;
									}
									else if (turn == 2)
									{
										turn = 1;
									}
									check = false;
									if (isEmpty(factories))
									{
										factories[0].clear();
										round = false;
									}
								}
								else
								{
									if(isShow)
									cout << "The required row cannot hold " << _colour << " colour as it is already in right side in required row\n";
								}
							}
							else
							{
								cout << "The Required Factory is Empty Or do not have the required colour. Please enter turn again.\n";
							}
						}
						else
						{
							cout << "Invalid turn, please input again.\n";
						}
					}
					else if (input.substr(0, 5) == "save ")
					{
						char* name = new char[30];
						size_t i = 0;
						for (size_t j = 5; j < input.size(); i++, j++)
						{
							name[i] = (char)input[j];
						}
						name[i] = '\0';
						//Now going to remove some unwanted friends from the vector
						int v_size = static_cast<int>(lid.size());
						for (int i = 0; i < v_size; i++)
						{
							if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L')
							{
								lid.erase(lid.begin() + i);
								i--;
								v_size--;
							}
						}
						//Saving the present state of game
						saveGame(box, lid, players, factories, turn, name, n_player);
						delete[] name;
						cout << "Now Enter you turn:\n";
						//turn = 2;
					}
					else if (input == "-1")
					{
						quit = true;
						check = false;
						endGame = false;
						loop = false;
						round = false;
					}
					else if (std::cin.eof())
					{
						std::cout << "Goodbye." << std::endl;
						input = "-1";
					}
					else
					{
						cout << "Invalid command! please input again.\n";
					}
				}
			}
		//------------------------------------------------------------
		if (!quit)
		{
			cout << "\t=== END OF ROUND ===\n\n";

			// Refilling the factories
			factories.clear();
			initFactories(factories, box, lid);

			//Setting the turn according to the first tile position
			if (players[0].broken.Head() != nullptr)
			{
				Node* cur = players[0].broken.Head();
				bool cond = true;
				while (cur != nullptr && cond)
				{
					if (cur->data == 'F')
					{
						turn = 1;
						cond = false;
					}
					cur = cur->next;
				}
				if (cond)	//If 'F' tile is not present in floor of player 1
				{
					turn = 2;
				}
			}
			else	//If player 1 does not have the F tile then player 2 must have
			{
				turn = 2;
			}
			//Now going to remove some unwanted friends from the vector
			int v_size = static_cast<int>(lid.size());
			for (int i = 0; i < v_size; i++)
			{
				if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L')
				{
					lid.erase(lid.begin() + i);
					i--;
					v_size--;
				}
			}
			/*     Implement score calculations and end of game logic here   */
			//Calculating the scores by shifting the tiles from left side of mosaic to right side (if all conditions meet)
			for (int i = 0 ;i < n_player ; i++ )
			{
			calcPoint(players[i].board, players[i].pattern, players[i].broken, players[i].score, lid, players[i].name);
			}
			
			//Checking end of the Match condition (a row has completed of any player)
			if (checkForRow(players[0].board) || checkForRow(players[1].board))
			{
				endGame = false;
			}
			else
			{
				round = true;
			}
		}
	}
	/* implementing the logics for final bounus scoring and declare the winner */
	if (!quit)
	{
		//Now going to remove some unwanted friends from the vector
		int v_size = static_cast<int>(lid.size());
		for (int i = 0; i < v_size; i++)
		{
			if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L')
			{
				lid.erase(lid.begin() + i);
				i--;
				v_size--;
			}
		}
		//Calculating the end-of-the-game-final-scoring
		for (int i = 0 ;i < n_player ; i++)
		{
			finalScoring(players[i].board, players[i].score);
		}

		cout << "=== GAME OVER ===\n\n";
		
		//Now announcing the winner;
		if (players[0].score > players[1].score)	//Player1 has won
		{
			cout << "\nPlayer " << players[0].name << " Wins!\n\n";
			for (int i = 0 ; i < n_player ; i++)
			{
				cout << "Score of " << players[i].name << " = " << players[i].score << "\n";
			}
			//printf("Score of %s = %d\n", players[0].name, players[0].score);
			//printf("Score of %s = %d\n\n", players[1].name, players[1].score);
		}
		else if (players[0].score < players[1].score)	// Player2 has won
		{

			//printf("Player %s wins!\n\n", players[1].name);
			cout << "\nPlayer " << players[1].name << " Wins!\n\n";
			for (int i = 0; i < n_player; i++)
			{
				cout << "Score of " << players[i].name << " = " << players[i].score << "\n";
			}
			//printf("Score of %s = %d\n", players[0].name, players[0].score);
			//printf("Score of %s = %d\n\n", players[1].name, players[1].score);
	
		}
		else	// The match is draw
		{
			cout << "It's a draw\n\n";
			for (int i = 0; i < n_player; i++)
			{
				cout << "Score of " << players[i].name << " = " << players[i].score << "\n";
			}
			//printf("Score of %s = %d\n", players[0].name, players[0].score);
			//printf("Score of %s = %d\n\n", players[1].name, players[1].score);
		}
		/*
		//Now going to remove some unwanted friends from the vector
		v_size = static_cast<int>(lid.size());
		for (int i = 0; i < v_size; i++)
		{
			if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L')
			{
				cout << "Removed2 this: " << lid[i] << "\n";
				lid.erase(lid.begin() + i);
				i--;
				v_size--;
			}
		}
		//Going to save the end game state to compare it with the actual expected state of the game
		char name[] = "result.txt";
		saveGame(box, lid, players, factories, turn, name, n_player);
		if (areFilesEqual(file, name))
		{
			cout << "The Resulting file is equal to the expected file.\n";
		}
		else
		{
			cout << "The Resulting file is NOT equal to the expected file.\n";
		}
		*/
		delete []players;
		players = nullptr;
		//printf("\n ***** Moving towards the main menu *****\n");
		cout << "\n ***** Moving towards the main menu *****\n";
		return true;
	}
	else
	{
		return false;
	}
}