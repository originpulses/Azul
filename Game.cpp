#include "Game.h"

//Function to display the main menu and take user's input
int mainMenu() {

	int choice = 0;
	cout << "Menu\n";
	cout << "----\n";
	cout << "1. New Game\n";
	cout << "2. Load Game\n";
	cout << "3. Credits\n";
	cout << "4. Quit\n\n> ";

	string input;

	getline(cin, input);
	if (std::cin.eof()) {

		return 4;
	}
	char temp = (char)input[0];
	choice = static_cast<int>(temp) - 48;
	while ((input.size() != 1) || !(choice >= 1 && choice <= 4)) {

		cout << "Invalid Input, Enter again\n";
		cout << "> ";
		getline(cin, input);
		if (std::cin.eof()) {

			return 4;
		}
		char temp = (char)input[0];
		choice = static_cast<int>(temp) - 48;
	}
	return choice;
}

// To Shuffle the box of tiles
void shuffle(vector<char>& box) {

	char temp = '\0';
	for (size_t i = 0; i < 500; ) {
		int i1 = (rand() % box.size());
		int i2 = (rand() % box.size());

		if (i1 != i2) {
			//Swapping ranks of 2 random cards
			temp = box[i2];
			box[i2] = box[i1];
			box[i1] = temp;
			i++;
		}
	}
}

int countRows(char filename[]) {

	int count = 0;
	ifstream fin;
	fin.open(filename);
	if (!fin) {

		cout << "Error opening the file...\n";
	}
	else {

		char tempp = '.';
		while (!fin.eof()) {

			if (tempp == '\n') {

				count++;
			}
			fin.get(tempp);
		}
	}
	fin.close();
	return count + 1; // +1 because last line contains eof character instead of '\n'
}

bool areFilesEqual(char N1[], char N2[]) {

	ifstream f1(N1);
	bool equals = true;
	if (!f1.is_open()) {

		cout << "Error opening the files to be compared...\n";
		return false;
	}
	else {
		ifstream f2(N2);
		if (f2.is_open()) {

			if (countRows(N1) == countRows(N2)) {

				char temp1 = '\0';
				char temp2 = '\0';
				while (!f1.eof() && !f2.eof() && equals) {

					f1.get(temp1);
					f2.get(temp2);
					if ((temp1 != temp2)) {

						if (temp1 != '\n')
							equals = false;
						else
							f1.get(temp1);
					}
				}
				if (!f1.eof() || !f2.eof()) {

					equals = false;
				}
			}
			else {

				equals = false;
			}
		}
		else {

			cout << "Error opening the files to be compared...\n";
			return false;
		}
	}
	return equals;
}

bool newGame(vector<char>& box, vector<char>& lid, int n_player, const int Bsize) {
	//Creating factories
	vector<vector<char> >factories;	// Vector to save the factories
	box.clear();
	// Placing 20 tiles of each design/color to initialize the box
	for (size_t i = 0; i < 20; i++) {

		box.push_back('R');	//Red Tiles
	}
	for (size_t i = 0; i < 20; i++) {

		box.push_back('Y'); //Yellow tiles
	}
	for (size_t i = 0; i < 20; i++) {

		box.push_back('B'); //Blue tiles
	}
	for (size_t i = 0; i < 20; i++) {

		box.push_back('L'); //Light blue tiles
	}
	for (size_t i = 0; i < 20; i++) {

		box.push_back('U'); //Black tiles
	}
	for (size_t i = 0; i < 20; i++) {

		box.push_back('O'); // Orange tiles
	}
	//Shuffling the initialized box
	shuffle(box);

	initFactories(factories, box, lid);		// initializing factories

	// Initializing players
	Player* players = new Player[n_player];
	for (int x = 0; x < n_player; x++) {

		cout << "Enter a name for player " << (x + 1) << "\n> ";
		cin.getline(players[x].name, 30);
		if (std::cin.eof()) {

			return false;
		}

		//Declaring the pattern board of both players
		/*
				 . ||
			   . . ||
			 . . . ||
		   . . . . ||
		 . . . . . ||
		*/
		//--------------------------------------------------------------------
		players[x].pattern = new char* [Bsize];
		for (int i = 0; i < Bsize; i++) {

			players[x].pattern[i] = new char[i + 1];
			for (int j = 0; j < i + 1; j++) {

				players[x].pattern[i][j] = '.';
			}
		}
		//--------------------------------------------------------------------
		//Declaring and initializing the tile board
		for (int i = 0; i < Bsize; i++) {

			for (int j = 0; j < Bsize; j++) {

				players[x].board[i][j] = '.';
			}
		}
	}

	cout << "\nLet's Play!\n\n";
	bool ret;

	ret = gamePlay(box, lid, players, factories, 1, n_player, Bsize);
	if (players != nullptr) {

		delete[]players;
		players = nullptr;
	}
	return ret;
}

bool loadGame(vector<char>& box, vector<char>& lid, char* name, int n_player, const int Bsize) {

	ifstream fin;
	fin.open(name);
	if (!fin) {

		throw "Exception! Error opening the file";
	}
	else {

		if (fin.peek() == std::ifstream::traits_type::eof()) {

			throw "Exception! No saved Game found...\n";
		}
		else {

			int turn = -1;
			string toBeignored = "";

			getline(fin, toBeignored);	//To read the comment line
			getline(fin, toBeignored);	//To read the comment line

			//--------------------------- Going to load bag							
			// Removing all already present tiles (if any) from the box
			//so that new tiles can be placed
			box.clear();
			// At last, loading the remaining box of tiles in the txt file
			char tempp = '\0';
			getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
			fin.get(tempp);
			while (tempp != '\n') {

				box.push_back(tempp);
				fin.get(tempp);
			}
			//box.pop_back();
			//--------------------------- Going to load lid
			// Removing all already present tiles (if any) from the lid
			//so that new tiles can be placed
			lid.clear();

			getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign

			// Loading the tiles on the top of lid (if any)

			fin.get(tempp);
			while (tempp != '\n') {

				lid.push_back(tempp);
				fin.get(tempp);
			}
			//lid.pop_back();
			//--------------------------- Going to load the factories

			vector<vector<char> >factories;	// Vector to save the factories
			tempp = '\0';
			for (int i = 0; i < 6; i++) {

				getline(fin, toBeignored, '=');	//To read the comment line till "=" sign
				vector<char> fac;
				fin.get(tempp);
				while (tempp != '\n') {
					
					fac.push_back(tempp); // Randomly generated tiles
					fin.get(tempp);
				}
				factories.push_back(fac);
			}

			//--------------------------- Going to load the Players

			Player* players = new Player[n_player];

			getline(fin, toBeignored);	//To read the comment line
			for (int w = 0; w < n_player; w++) {

				getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign

				//Loading the names of players	
				fin.getline(players[w].name, 30);
				int g = 0;
				while (players[w].name[g] != '\0') {

					g++;
				}
				//players[w].name[g - 1] = '\0';
				players[w].name[g] = '\0';
				
				//Now going to read the score
				getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
				fin >> players[w].score;
				fin.get(tempp);

				//Loading the factory display (Triangle)

				players[w].pattern = new char* [Bsize];
				for (int i = 0; i < Bsize; i++) {

					getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
					players[w].pattern[i] = new char[i + 1];
					fin.get(tempp);

					//it means the row is empty
					if (tempp == '\n' || tempp == '-') {

						for (int j = 0; j < i + 1; j++) {
							
							players[w].pattern[i][j] = '.';
						}
					}
					else {
						int j;
						for (j = 0; j < i + 1 && tempp != '\n'; j++) {

							players[w].pattern[i][j] = tempp;
							fin.get(tempp);
						}
						if (j < (i + 1)) {

							while (j < (i + 1)) {

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
				while (tempp != '\n') {

					players[w].broken.insert(tempp);
					fin.get(tempp);
				}

				//Loading the tile board

				//Board of player 
				for (int i = 0; i < Bsize; i++) {

					getline(fin, toBeignored, '=');	//To read the comment line till the "=" sign
					for (int j = 0; j < Bsize; j++) {

						fin.get(tempp);
						if (tempp == '-') {

							players[w].board[i][j] = '.';
						}
						else{
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
			ret = gamePlay(box, lid, players, factories, turn, n_player, Bsize);
			if (players != nullptr) {

				delete[]players;
			}
			return ret;
		}
		return true;
	}
}

void initFactories(vector<vector<char> >& factories, vector<char>& box, vector<char>& lid) {

	//Removing any null element(if any) from the factories
	for (size_t i = 0 ; i < factories.size() ; i++) {

		for (size_t j = 0 ; j < factories[i].size() ; j++) {

			factories[j].clear();
		}
	}
	//If the box is empty/or have insufficient tiles then shift all tiles from the lid into the box
	//according to the rules of AZUL
	if (box.size() < 20) {

		size_t lidSize = lid.size();
		for (size_t i = 0; i < lidSize; i++) {

			box.push_back(lid[i]);
		}

		//Removing those all tiles from the lid
		lid.clear();
		//Now shuffling the box once again as tiles from lid can in in order.
		shuffle(box);
	}
	//The central Factory
	vector<char> center;
	center.push_back('F');		// First turn brick
	factories.push_back(center);
	center.clear();

	size_t index = 1;
	//Now going to place tiles in other 5 facctories
	for (size_t i = 0; i < 5; i++) {

		vector<char> fac;
		for (int j = 0; j < 4; j++) {

			if (box[box.size() - index] == 'F' || box[box.size() - index] == 'B' || box[box.size() - index] == 'Y' || box[box.size() - index] == 'R' || box[box.size() - index] == 'U' || box[box.size() - index] == 'L' || box[box.size() - index] == 'O') {

				fac.push_back(box[box.size() - index]); // Adding last 4 tiles from the box in factories
			}
			else {
				j--;
			}
			index++;
		}
		factories.push_back(fac);
		fac.clear();
	}
	box.resize(box.size() - 20);	 // To remove the tiles from box which are moved in factory
}
void DisplayState(vector<vector<char> >factories, Player* player,int n_player,int turn, const int Bsize) {

	cout << "TURN FOR PLAYER:" << player[turn-1].name << "\n";
	cout << "Factories:\n";
	for (size_t i = 0; i < factories.size(); i++) {

		cout << i << ": ";
		for (size_t j = 0; j < factories[i].size(); j++) {

			if (factories[i][j] == 'F') {

				cout << "\033[48;2;255;255;255;30m" << "F" << "\033[m "; // First player tile
			}
			else if (factories[i][j] == 'B') {

				cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
			}
			else if (factories[i][j] == 'L') {

				cout << "\033[48;2;101;136;233m" << "L" << "\033[m ";//Light Blue
			}
			else if (factories[i][j] == 'R') {
			
				cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; //Red
			}
			else if (factories[i][j] == 'U') {

				cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; //Black
			}
			else if (factories[i][j] == 'O') {

				cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
			}
			else if (factories[i][j] == 'Y') {

				cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
			}
		}
		cout << "\n";
	}

	int P2 = 0;
	if (turn == 1) {

		P2 = 1;
	}
	else if(turn == 2) {

		P2 = 0;
	}
	int var = turn - 1;
	cout << "\nMosaic for " << player[turn - 1].name << "\t\t\tMosaic for " << player[P2].name <<"\n";
	for (int i = 0; i < Bsize; i++) {

		cout << i + 1 << ": ";
		var = turn - 1;
		for (int g = 0; g < 2; g++) {

			for (int j = 0; j < Bsize - 1 - i; j++){
				cout << "  ";
			}
			for (int j = 0; j < i + 1; j++) {

				if (player[var].pattern[i][j] == 'B') {

					cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
				}
				else if (player[var].pattern[i][j] == 'L') {

					cout << "\033[48;2;101;136;233m" << "L" << "\033[m ";//Light Blue
				}
				else if (player[var].pattern[i][j] == 'R') {

					cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; //Red
				}
				else if (player[var].pattern[i][j] == 'U') {

					cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; //Black
				}
				else if (player[var].pattern[i][j] == 'O') {

					cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
				}
				else if (player[var].pattern[i][j] == 'Y') {

					cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
				}
				else {
					cout << ". ";
				}

			}

			cout << " || ";
			for (int j = 0; j < Bsize; j++) {

				if (player[var].board[i][j] == 'B') {

					cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
				}
				else if (player[var].board[i][j] == 'L') {

					cout << "\033[48;2;101;136;233m" << "L" << "\033[m ";//Light Blue
				}
				else if (player[var].board[i][j] == 'R') {

					cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; //Red
				}
				else if (player[var].board[i][j] == 'U') {

					cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; //Black
				}
				else if (player[var].board[i][j] == 'O') {

					cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
				}
				else if (player[var].board[i][j] == 'Y') {

					cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
				}
				else {

					cout << ". ";
				}
			}
			cout << "\t\t";
			var = P2;
		}

		cout << "\n";
	}
	player[turn-1].broken.print();
	cout << "\t\t\t\t";
	player[P2].broken.print();
	cout << "\n";
}

void saveGame(vector<char>& box, vector<char>& lid, Player* players, vector<vector<char> >& factories, int turn, char* filename, int n_player, const int Bsize) {
	ofstream fout;
	fout.open(filename, ios::out);
	if (!fout) {

		cout << "Error opening the file to save the game...\n";
	}
	else {
		//Writing the factories
		fout << "# This is a comment line, and is optional\n";
		fout << "# Multiline comments are just multiple single line comments\n";

		fout << "BAG=";
		// Now writing the lid (tiles places on lid, if any) in tha txt file
		for (size_t i = 0; i < box.size(); i++) {

			if (box[i] == 'B') {

				fout << "B";
			}
			else if (box[i] == 'L') {
				fout << "L";
			}
			else if (box[i] == 'R') {

				fout << "R";
			}
			else if (box[i] == 'U') {

				fout << "U";
			}
			else if (box[i] == 'O') {

				fout << "O";
			}
			else if (box[i] == 'Y') {

				fout << "Y";
			}
			else if (box[i] == 'F') {

				fout << "F";
			}
		}
		fout << "\n";

		fout << "LID=";
		// At last, writing the remaining box of tiles in the txt file
		for (size_t i = 0; i < lid.size(); i++) {

			if (lid[i] == 'B') {

				fout << "B";
			}
			else if (lid[i] == 'L') {

				fout << "L";
			}
			else if (lid[i] == 'R') {

				fout << "R";
			}
			else if (lid[i] == 'U') {

				fout << "U";
			}
			else if (lid[i] == 'O') {

				fout << "O";
			}
			else if (lid[i] == 'Y') {

				fout << "Y";
			}
			else if (lid[i] == 'F') {

				fout << "F";
			}
		}
		fout << "\n";

		for (size_t i = 0; i < factories.size(); i++) {

			if (i == 0) {

				fout << "FACTORY_CENTRE=";
			}
			else {

				fout << "FACTORY_" << i << "=";
			}
			for (size_t j = 0; j < factories[i].size(); j++) {

				fout << factories[i][j];
			}
			fout << "\n";
		}

		fout << "# Could use comments to separate sections\n";

		//Writing the information of player 1

		for (int x = 0; x < n_player; x++) {

			fout << "PLAYER_" << (x + 1) << "_NAME=" << players[x].name << "\n";
			fout << "PLAYER_" << (x + 1) << "_SCORE=" << players[x].score << "\n";

			for (int i = 0; i < Bsize; i++) {

				fout << "PLAYER_" << (x + 1) << "_PATTERN_LINE" << (i + 1) << "=";
				for (int j = 0; j < i + 1; j++) {

					fout << players[x].pattern[i][j];
				}
				fout << "\n";
			}

			fout << "PLAYER_" << (x + 1) << "_FLOOR_LINE=";
			//writing broken tiles of both players
			if (players[x].broken.Head() != nullptr) {

				Node* cur = players[x].broken.Head();
				while (cur != nullptr) {

					if (cur->data == 'F' || cur->data == 'B' || cur->data == 'Y' || cur->data == 'R' || cur->data == 'U' || cur->data == 'L' || cur->data == 'O')
						fout << cur->data;

					cur = cur->next;
				}
			}

			fout << "\n";
			//Board of player 1
			for (int i = 0; i < Bsize; i++) {

				fout << "PLAYER_" << (x + 1) << "_MOSAIC_" << (i + 1) << "=";
				for (int j = 0; j < Bsize; j++) {

					fout << players[x].board[i][j];
				}
				fout << "\n";
			}
		}
		//---------------------------------------------------------------------------
		// The turn(which player will play first in next round)
		fout << "CURRENT_PLAYER=" << turn;

		cout << "Game successfully saved to \'" << filename << "\'\n";
		cout << "< Gameplay continues until end - of - game > " << "\n\n";
		//closing the txt file
		fout.close();
	}
}

bool isEmpty(vector<vector<char> >factories) {

	bool empty = true;
	size_t zero = 0;
	if (factories.size() == zero) {

		empty = false;
	}
	else {

		for (size_t i = 0; i < factories.size() && empty; i++) {

			for (size_t j = 0; j < factories[i].size(); j++) {

				if (factories[i][j] != 'F' || factories[i][j] != 'B' || factories[i][j] != 'Y' || factories[i][j] != 'R' || factories[i][j] != 'U' || factories[i][j] != 'L' || factories[i][j] != 'O') {

					empty = false;
				}
			}
		}
	}
	return empty;
}

bool isColValid(char B[][6], const int Bsize, int row, char color) {

	bool check = true;
	for (int i = 0 ; i < Bsize && check ; i++) {

		if (B[row][i] == color ) {

			check = false;
		}
	}
	return check;
}

bool charPossible(vector<vector<char> >factories, int index, char colour) {

	bool check = false;
	for (size_t i = 0; i < factories[index].size() && !check; i++) {

		if (factories[index][i] == colour) {
			check = true;
		}
	}
	return check;
}

int  giveIndexOfColour(char B[][6], const int Bsize, int index, char colour) {

	char row[6] = { 'B','Y','R','U','L','O' };
	for (int i = 0; i < index; i++) {

		char temp = row[Bsize - 1];
		for (int j = Bsize - 1; j > 0; j--) {

			row[j] = row[j - 1];
		}
		row[0] = temp;
	}
	index = -1;
	bool cond = true;
	for (int i = 0; i < Bsize && cond; i++) {

		if (row[i] == colour) {

			index = i;
			cond = false;
		}
	}
	return index;
}

int askIndexOfColour(char B[][6], const int Bsize, int rows, char colour, bool& okay) {

	int col = 0;
	cout << "Enter the column number against row " << (rows+1) << " in which you wish to place tile ";
	if (colour == 'B') {

		cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
	}
	else if (colour == 'L') {

		cout << "\033[48;2;101;136;233m" << "L" << "\033[m ";//Light Blue
	}
	else if (colour == 'R') {

		cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; //Red
	}
	else if (colour == 'U') {

		cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; //Black
	}
	else if (colour == 'O') {

		cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
	}
	else if (colour == 'Y') {

		cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
	}
	cout << "\n";
	cout << ">";
	string input = "";
	getline(cin,input);
	char II = input[0];

	col = static_cast<int>(II)-48;
	if (std::cin.eof()) {

		okay = false;
		return -1;
	}
	while (!(col >= 1 && col <= 6) || (!isColValid(B, Bsize, rows, colour) && input.size() == 1)) {

		if(col >= 1 && col <= 6)
		    cout << "Invalid column! The required place already has a tile, please enter again.\n>";
		else
			cout << "Invalid column! Valid Range is (1 - 6), please enter again.\n>";

		getline(cin, input);
		II = input[0];
		col = static_cast<int>(II)-48;
		if (std::cin.eof()) {

			okay = false;
			return -1;
		}
	}
	col--;
	return col;
}

bool calcPoint(char B[][6], const int Bsize, char**& pattern, LinkedList& broken, int& score, vector<char>& lid, string Pname) {

	bool okay = true; // Just to handle the EOF character situation
	int roundScore = 0;
	bool complete = true;
	cout << "Placing tiles in wall/board of player: " << Pname << "\n";
	cout << "Wall/Board of player: " << Pname << "\n\n";
	cout << "  1 2 3 4 5 6\n";
	for (int i = 0 ; i < Bsize ; i++ ) {

		cout << (i + 1) << " ";
		for (int j = 0 ;j < Bsize ; j++) {

			cout << B[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	// First things first, moving all completed rows's tile colour to the right side row of mosaic
	for (int rows = 0; rows < Bsize; rows++) {

		complete = true;
		//checking for completed line
		char first = '.';
		if (pattern[rows][0] != '.' && pattern[rows][0] != '\0' && pattern[rows][0] != '\n') {

			first = pattern[rows][0]; //Placed the tile type contained by this current row
			//The following loop checks either row is full with same tiles of not
			bool cond = true;
			for (int i = 0; i < rows + 1 && cond; i++) {

				if (pattern[rows][i] != first) {

					complete = false;
					cond = false;	// just to break the loop
				}
			}
			//If row is full of same tiles then should move this tile to the right side
			//of mosaic
			if (complete) {

				int col = -1;
				col = askIndexOfColour(B, Bsize, rows, first, okay);

				// Player entered EOF
				if (!okay) {

					return okay;
				}
				//shifting the colour to the corresponding block at right side of the mosaic
				B[rows][col] = first;

				//Now calculating the points of this tile
				int count = 0;
				bool check1 = false;
				//Checking for adjacent tiles in the row
				for (int i = col + 1; i < Bsize && B[rows][i] != '.'; i++) {

					check1 = true;
					count++;
				}
				for (int i = col - 1; i >= 0 && B[rows][i] != '.'; i--) {

					check1 = true;
					count++;
				}
				if (check1) {

					count++;
				}

				//Checking for adjacent tiles in the row
				bool check2 = false;
				for (int i = rows + 1; i < Bsize && B[i][col] != '.'; i++) {

					check2 = true;
					count++;
				}
				for (int i = rows - 1; i >= 0 && B[i][col] != '.'; i--) {

					check2 = true;
					count++;
				}
				if (check2) {

					count++;
				}

				// If the tile had no adjacent tiles
				if (count == 0) {

					roundScore++;
				}

				//If tile had adjacent tile(s) then adding score accordingly
				else {
					roundScore += count;
				}
				count = 0;

				//moving all remaining tiles to the lid
				int i;
				for (i = 0; i < rows; i++) {

					lid.push_back(first);
					pattern[rows][i] = '.';
				}
				pattern[rows][i] = '.';
			}
		}
	}

	int count = 0;
	int rate = -1;
	int brokenTiles = broken.getSize();
	Node* cur = broken.Head();
	while (cur != nullptr) {

		if (cur->data != 'F' && cur->data != 'B' && cur->data != 'Y' && cur->data != 'R' && cur->data != 'U' && cur->data != 'L')
			brokenTiles--;
		cur = cur->next;
	}

	for (int i = 1; i <= brokenTiles; i++) {

		if (i == 3) {

			rate = -2;
		}
		else if (i == 6) {

			rate = -3;
		}
		else if (i == 8) {

			rate = -4;
		}
		count += rate;
	}

	if (brokenTiles > 0) {

		broken.removeAll(lid, true);
	}
	roundScore += count;
	score += roundScore;
	cout << "***** Score board of player " << Pname << "\n\n";
	cout << "Total points deducted for broken tiles: " << count << ".\n";
	cout << "Score of this round: " << roundScore << ".\n";
	cout << "Total score after this round: " << score << ".\n\n";
	return true;
}

bool checkForRow(char B[][6]) {

	bool check = false;
	//if check is true then it means we have found an incomplete row
	for (size_t i = 0; i < 6 && !check; i++) {

		size_t j = 0;
		for (j = 0; j < 6 && !check; j++) {

			if (B[i][j] == '.') {
				check = true;	//TO break the loop
			}
		}
		// If above row had no vacant space, it means it is completed 
		if (j == 6 && !check) {

			check = true;	//a complete row is found
		}
		else {
			check = false;
		}
	}
	return check;
}

void finalScoring(char B[][6], int& score) {

	bool cond = true; // This bool is just to break the the loops if some condition(s) are meet 
	//Checking for all complete rows 
	for (int i = 0; i < 6; i++) {

		int j = 0;
		cond = true;
		for (j = 0; j < 6 && cond; j++) {

			if (B[i][j] == '.') {

				cond = false;
				j--;
			}
		}
		// If above row had no vacant space, it means it is complete
		if (j == 6) {

			score += 2;	//So here are the extra 2 points for each complete row
		}
	}

	cond = true;
	//Checking for all complete columns
	for (int i = 0; i < 6; i++) {

		int j = 0;
		for (j = 0; j < 6 && cond; j++) {

			if (B[j][i] == '.') {

				cond = false;
				j--;
			}
		}
		// If the current column had no vacant space, it means it is complete 
		if (j == 6) {

			score += 7;	//So here are the extra 7 points for each complete column
		}
	}

	//now going to calculate that how many times this player 
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

	int colourCount[6] = { 0 };
	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 6; j++) {

			if (B[i][j] == 'R') {

				colourCount[0]++;
			}
			else if (B[i][j] == 'Y') {

				colourCount[1]++;
			}
			else if (B[i][j] == 'B') {

				colourCount[2]++;
			}
			else if (B[i][j] == 'L') {

				colourCount[3]++;
			}
			else if (B[i][j] == 'U') {

				colourCount[4]++;
			}
			else if (B[i][j] == 'O') {

				colourCount[5]++;
			}
		}
	}
	//At this point we have count of occurunces of each colour

	// Now we will find the minimum number for which each colour occured
	int min = 9999999;

	// Finding the minimum number of occurence of a tile
	for (int i = 0; i < 6; i++) {

		if (colourCount[i] < min) {

			min = colourCount[i];
		}
	}
	//now going to check if all colours have occurred minimum for min times (Note: the min can be 0 so
	// if a tiles has occurred not even once then even tat condition get covered under this)
	int i;
	cond = true;

	// Finding the minimum number of occurence of a tile
	for (i = 0; i < 6 && cond; i++) {

		if (min > colourCount[i]) {

			cond = false;
		}
	}

	//this means that min contains the number of times for which all colours occurred at least
	if (cond) {

		//10 points for each time, all colours occureds.
		//if all colours occured not even once then min will be 0, hence no effect on scoring 
		score += (min * 10);
	}
}

void instructions() {

	cout << "\t\t\t\t\t\t\033[48;2;0;255;34;30m *INSTRUCTIONS*\033[m\n\n";
	cout << "\t\t\t\033[48;2;0;255;34;30mInput formats: <type> <factory> <colour> <storage row>\033[m\n\n";

	cout << "\t\t\t\033[48;2;255;0;0m1.\033[48;2;0;9;255m First you will type the command name e.g. turn, save.\033[m\n";
	cout << "\t\t\t\033[48;2;0;9;255m   only these 2 are valid commands\033[m\n\n";
	cout << "\t\t\t\033[48;2;255;0;0m2.\033[48;2;0;9;255m Then with a SPACE you will write the number of factory from which you\033[m\n";
	cout << "\t\t\033[48;2;0;9;255m	   want to pick tiles. (This MUST be an integer (range 0 - 5) )\033[m\n\n";
	cout << "\t\t\t\033[48;2;255;0;0m3.\033[48;2;0;9;255m Then with a SPACE you will write the colour of tile you want to pick\033[m\n";
	cout << "\t\t\t\033[48;2;0;9;255m   from that specified factory. (Valid colours: R, Y, B, L, U, O) all other inputs are invalid.\033[m\n\n";
	cout << "\t\t\t\033[48;2;255;0;0m4.\033[48;2;0;9;255m Then at last, with a SPACE you will write the numebr of storage row.\033[m\n";
	cout << "\t\t\t\033[48;2;0;9;255m   (This MUST be an integer (range 1 - 6) )\033[m\n\n";
	cout << "\t\t\t\033[48;2;255;0;0m5.\033[48;2;0;9;255m At any moment a player can enter EOF to exit the game and terminate\033[m\n";
	cout << "\t\t\t\033[48;2;0;9;255m   the program. (CAUTION: All unsaved progress will be lost)\033[m\n\n";
	cout << "\t\t\t\033[48;2;255;0;0m6.\033[48;2;0;9;255m A player can enter \"turn n A F\" to move all tiles of nth factory (0 <= n <= 6)\033[m\n";
	cout << "\t\t\t\033[48;2;0;9;255m   to his/her floor.\033[m\n\n";

}

bool gamePlay(vector<char>& box, vector<char>& lid, Player*& players, vector<vector<char> >& factories, int turn, int n_player, const int Bsize) {

	bool loop = true;
	bool round = true;
	bool endGame = true;
	bool quit = false;
	bool firstTileFirstCheck = false;
	bool isShow = true;

	// This loop controls the rounds
	while (endGame && round) {

		cout << "\t\033[48;2;0;255;34;30m=== Start Round ===\033[m\n\n";
		string input = "";
		bool check = true;
		bool ifFirstTileGained = false;
		bool isFirst = false;

		// This loop is responsible for back to back turns of players in one round
		while (loop && round) {

			DisplayState(factories, players ,n_player,turn, Bsize);

			check = true;
			while (check) {

				cout << "> ";
				getline(cin, input);
				isShow = true;
				
				if (input.substr(0, 5) == "turn " && input.size() == 10) {

					char _f_ = input[5];
					int _f = static_cast<int>(_f_) - 48;

					char _colour = (char)input[7];

					char _row = input[9];
					int _r = static_cast<int>(_row) - 48;

					//just checking if input command is valid or not
					if ((_f >= 0 && _f <= 5) && (_colour == 'R' || _colour == 'Y' || _colour == 'B' || _colour == 'L' || _colour == 'U' || _colour == 'O' || _colour == 'A') && ((_r >= 1 && _r <= Bsize) || _r == 22 )) {

						// if player wants to move all tiles from selected factory into his/her floor
						if (_r == 22 && _colour == 'A' ) {

							if (factories[_f].size() > 0) {

								//checking for First-turn tile in central factory
								if (!isFirst && _f == 0) {

									bool _cond = true; // Just to break the loop if specific condition meets
									for (size_t i = 0; i < factories[_f].size() && _cond; i++) {


										if (factories[_f][i] == 'F') {

											isFirst = true;
											_cond = false;
										}
									}
									if (isFirst && !firstTileFirstCheck) {

										firstTileFirstCheck = true;
										cout << "\033[48;2;0;255;34;30m"  << players[turn - 1].name << " got the first player tile.\033[m\n\n";
									}
								}


								//Moving all tiles from the selected factory to the floor of current player
								for (size_t i = 0; i < factories[_f].size(); i++) {

									if (factories[_f][i] == 'F' || factories[_f][i] == 'B' || factories[_f][i] == 'Y' || factories[_f][i] == 'R' || factories[_f][i] == 'U' || factories[_f][i] == 'L' || factories[_f][i] == 'O') {
										players[turn - 1].broken.insert(factories[_f][i]);
									}
								}
								factories[_f].clear();
								cout << "\033[48;2;0;255;34;30mTurn Successful.\033[m\n\n";
								if (turn == 1) {

									turn = 2;
								}
								else if (turn == 2) {

									turn = 1;
								}
								check = false;
								if (isEmpty(factories)) {

									factories[0].clear();
									round = false;
								}
							}
							else {

								cout << "\033[48;2;0;255;0;0mThe required factory is empty!, please enter a Valid turn.\033[m\n\n";
							}


						}
						//if player does not want to move all tiles from selected factory to his/her floor
						else {
							_r--; //As rows in array start from 0 not 1
							bool justDoIt = true;
							if (_r == 21 || _colour == 'A') {

								justDoIt = false;
							}


							if (charPossible(factories, _f, _colour) && justDoIt) {

								//Checking if the corresponding tiles board already have the required colour or not
								bool valid = isColValid(players[turn - 1].board, Bsize, _r, _colour);

								//Now going to check if the required row of mosaic pattern board can hold the required colour
								int possibleTiles = 0;
								if (valid) {

									bool _cond = true; // Just to break the loop if specific condition meets
									for (int i = 0; i < _r + 1 && _cond; i++) {

										if (players[turn - 1].pattern[_r][i] != '.' && players[turn - 1].pattern[_r][i] != _colour) {

											valid = false;
											_cond = false;
										}
										else {

											if (players[turn - 1].pattern[_r][i] == '.')
												possibleTiles++;
										}
									}
								}

								if (valid && possibleTiles == 0) {

									cout << "\033[48;2;0;255;0;0mRequired row is full, can not place more tiles in it.\033[m\n\n";
									valid = false;
									isShow = false;
								}

								//At this moment we know that the location is alright to place the tiles in mosaic
								if (valid) {

									//checking for First turn tile in central factory
									if (!isFirst && _f == 0) {

										bool _cond = true; // Just to break the loop if specific condition meets
										for (size_t i = 0; i < factories[_f].size() && _cond; i++) {


											if (factories[_f][i] == 'F') {

												isFirst = true;
												_cond = false;
											}
										}

										if (isFirst && !firstTileFirstCheck) {

											firstTileFirstCheck = true;
											cout << "\033[48;2;0;255;34;30m" << players[turn - 1].name << " got the first player tile.\033[m\n\n";
										}
									}

									int actual = 0;
									vector<char> temp_central_F;
									vector<char> temp_central_F0;
									ifFirstTileGained = false;
									for (size_t i = 0; i < factories[_f].size(); i++) {
										// if we are in central factory and firstplayer tile is still there
										if (factories[_f][i] == 'F') {

											// then it moves to the broken tiles of respective player
											if (factories[_f][i] == 'F' || factories[_f][i] == 'B' || factories[_f][i] == 'Y' || factories[_f][i] == 'R' || factories[_f][i] == 'U' || factories[_f][i] == 'L' || factories[_f][i] == 'O') {
												players[turn - 1].broken.insert(factories[_f][i]);
												ifFirstTileGained = true;
											}
										}
										//counting the same colur tiles
										else if (factories[_f][i] == _colour) {

											actual++;
										}
										//All other tiles will be moved to the central factory
										else {

											if (factories[_f][i] == 'F' || factories[_f][i] == 'B' || factories[_f][i] == 'Y' || factories[_f][i] == 'R' || factories[_f][i] == 'U' || factories[_f][i] == 'L' || factories[_f][i] == 'O')
												temp_central_F.push_back(factories[_f][i]);
										}
									}
									if (_f != 0) {

										if (!ifFirstTileGained) {

											for (size_t i = 0; i < factories[0].size(); i++) {

												if (factories[0][i] == 'F' || factories[0][i] == 'B' || factories[0][i] == 'Y' || factories[0][i] == 'R' || factories[0][i] == 'U' || factories[0][i] == 'L' || factories[_f][i] == 'O')
													temp_central_F0.push_back(factories[0][i]);
											}
										}
										else {
											// Skipping the first player tile
											for (size_t i = 1; i < factories[0].size(); i++) {

												if (factories[0][i] == 'F' || factories[0][i] == 'B' || factories[0][i] == 'Y' || factories[0][i] == 'R' || factories[0][i] == 'U' || factories[0][i] == 'L' || factories[_f][i] == 'O')
													temp_central_F0.push_back(factories[0][i]);
											}
										}
									}
									
										//This process is to update the central factory
										factories[0].clear();
										for (size_t i = 0; i < temp_central_F0.size(); i++) {

											factories[0].push_back(temp_central_F0[i]);
										}
										for (size_t i = 0; i < temp_central_F.size(); i++) {

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
										for (j = 0; j < actual && i < (_r + 1) && players[turn - 1].pattern[_r][i] == '.'; j++, i++) {

											players[turn - 1].pattern[_r][i] = _colour;
										}

										int x = 0;
										if (actual - possibleTiles >= 0) {

											// Adding the remaining tiles(if any) to the bottom of the mat
											for (x = 0; x < actual - possibleTiles; x++) {

												if (_colour == 'F' || _colour == 'B' || _colour == 'Y' || _colour == 'R' || _colour == 'U' || _colour == 'L' || _colour == 'O')
													players[turn - 1].broken.insert(_colour);
											}
										}
									cout << "\033[48;2;0;255;34;30mTurn Successful.\033[m\n\n";
									if (turn == 1) {

										turn = 2;
									}
									else if (turn == 2) {
										
										turn = 1;
									}
									check = false;
									if (isEmpty(factories)) {

										factories[0].clear();
										round = false;
									}
								}
								else {

									if (isShow)
									cout << "\033[1;37;41m The required row cannot hold " << _colour << " colour.\033[m\n\n";

								}
							}
							else if(justDoIt) {

								cout << "\033[1;37;41mThe Required Factory is Empty Or do not have the required colour. Please enter turn again.\033[m\n\n";
							}
							else {
							
								cout << "\033[1;37;41mInvalid turn, please input again.\033[m\n\n";
							}
						}
					}
					else {

						cout << "\033[1;37;41mInvalid turn, please input again.\033[m\n\n";
					}
				}
				else if (input.substr(0, 5) == "save ") {

					char* name = new char[30];
					size_t i = 0;
					for (size_t j = 5; j < input.size(); i++, j++) {

						name[i] = (char)input[j];
					}
					name[i] = '\0';
					//Now going to remove some unwanted friends from the vector
					int v_size = static_cast<int>(lid.size());
					for (int i = 0; i < v_size; i++) {

						if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L' && lid[i] != 'O') {

							lid.erase(lid.begin() + i);
							i--;
							v_size--;
						}
					}
					//Saving the present state of game
					saveGame(box, lid, players, factories, turn, name, n_player, Bsize);
					delete[] name;
					cout << "Now Enter you turn:\n";
				}
				else if (input == "help") {

					instructions();
				}
				else if (std::cin.eof()) {

					quit = true;
					check = false;
					endGame = false;
					loop = false;
					round = false;
				}
				else {

					cout << "\t\033[1;37;41mInvalid command! please input again.\033[m\n\n";
				}
			}
		}
		//------------------------------------------------------------
		if (!quit) {

			cout << "\t\033[1;37;41m=== END OF ROUND ===\033[m\n\n";
			
			// Refilling the factories
			factories.clear();
			initFactories(factories, box, lid);

			//Setting the turn according to the first tile position
			if (players[0].broken.Head() != nullptr) {

				Node* cur = players[0].broken.Head();
				bool cond = true;
				while (cur != nullptr && cond) {

					if (cur->data == 'F') {

						turn = 1;
						cond = false;
					}
					cur = cur->next;
				}
				//If 'F' tile is not present in floor of player 1
				if (cond) {

					turn = 2;
				}
			}
			//If player 1 does not have the F tile then player 2 must have
			else {

				turn = 2;
			}
			//Now going to remove some unwanted friends from the vector
			int v_size = static_cast<int>(lid.size());
			for (int i = 0; i < v_size; i++) {

				if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L' && lid[i] != 'O') {

					lid.erase(lid.begin() + i);
					i--;
					v_size--;
				}
			}

			/*     Implement score calculations and end of game logic here   */
			//Calculating the scores by shifting the tiles from left side of mosaic to right side (if all conditions meet)
			bool o = true;
			for (int i = 0; i < n_player && o ; i++) {

				if (!calcPoint(players[i].board, Bsize, players[i].pattern, players[i].broken, players[i].score, lid, players[i].name)) {

					quit = true;
					endGame = false;
					round = false;
					o = false;
				}
			}

			//Checking end of the Match condition (a row has completed of any player)
			if (checkForRow(players[0].board) || checkForRow(players[1].board)) {

				endGame = false;
			}
			else {

				round = true;
			}
		}
	}
	/* implementing the logics for final bounus scoring and declare the winner */
	if (!quit) {

		//Now going to remove some unwanted friends from the vector
		int v_size = static_cast<int>(lid.size());
		for (int i = 0; i < v_size; i++) {

			if (lid[i] != 'F' && lid[i] != 'B' && lid[i] != 'Y' && lid[i] != 'R' && lid[i] != 'U' && lid[i] != 'L' && lid[i] != 'O') {

				lid.erase(lid.begin() + i);
				i--;
				v_size--;
			}
		}
		//Calculating the end-of-the-game-final-scoring
		for (int i = 0; i < n_player; i++) {

			finalScoring(players[i].board, players[i].score);
		}

		cout << "\t\033[1;37;41m=== GAME OVER ===\033[m\n\n";

		//Now announcing the winner;
		//Player1 has won
		if (players[0].score > players[1].score) {
			cout << "\nPlayer " << players[0].name << " Wins!\n\n";
			for (int i = 0; i < n_player; i++) {

				cout << "Score of " << players[i].name << " = " << players[i].score << "\n";
			}
		}
		// Player2 has won
		else if (players[0].score < players[1].score) {

			cout << "\nPlayer " << players[1].name << " Wins!\n\n";
			for (int i = 0; i < n_player; i++) {

				cout << "Score of " << players[i].name << " = " << players[i].score << "\n";
			}
		}
		// The match is draw
		else {

			cout << "It's a draw\n\n";
			for (int i = 0; i < n_player; i++) {

				cout << "Score of " << players[i].name << " = " << players[i].score << "\n";
			}
		}

		cout << "\nMosaic for " << players[0].name << "\t\t\tMosaic for " << players[1].name << "\n";
			for (int i = 0; i < Bsize; i++) {

				cout << i + 1 << ": ";
				for (int g = 0; g < n_player; g++) {

					for (int j = 0; j < Bsize - 1 - i; j++) {

						cout << "  ";
					}

					for (int j = 0; j < i + 1; j++) {

						if (players[g].pattern[i][j] == 'B') {

							cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
						}
						else if (players[g].pattern[i][j] == 'L') {

							cout << "\033[48;2;101;136;233m" << "L" << "\033[m "; // Light Blue
						}
						else if (players[g].pattern[i][j] == 'R') {

							cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; // Red
						}
						else if (players[g].pattern[i][j] == 'U') {

							cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; // Black
						}
						else if (players[g].pattern[i][j] == 'O') {
						
							cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
						}
						else if (players[g].pattern[i][j] == 'Y') {

							cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
						}
						else {

							cout << ". ";
						}

					}

					cout << " || ";
					for (int j = 0; j < Bsize; j++) {

						if (players[g].board[i][j] == 'B') {

							cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
						}
						else if (players[g].board[i][j] == 'L') {

							cout << "\033[48;2;101;136;233m" << "L" << "\033[m ";//Light Blue
						}
						else if (players[g].board[i][j] == 'R') {

							cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; //Red
						}
						else if (players[g].board[i][j] == 'U') {

							cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; //Black
						}
						else if (players[g].board[i][j] == 'O') {

							cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
						}
						else if (players[g].board[i][j] == 'Y') {

							cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
						}
						else {
							cout << ". ";
						}
					}
					cout << "\t\t";
				}

				cout << "\n";
			}

		delete[]players;
		players = nullptr;
		cout << "\n ***** Moving towards the main menu *****\n";
		return true;
	}

	else {
		return false;
	}
}