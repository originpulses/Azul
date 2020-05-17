#include "Mosaic.h"

Mosaic::Mosaic(Player* player) {

    this->player = player;
    this->pointBoard = new Tile*[BOARD_SIZE];
    this->turnBoard = new Tile*[BOARD_SIZE];
    this->pointCalculator = new char*[BOARD_SIZE];
    this->colourCounting = new bool[NUMBEROFCOLOUR];
    for(int i =0; i < 5; i++) {
        this->turnBoard[i] = new Tile[i+1];
        this->pointBoard[i] = new Tile[BOARD_SIZE];
        this->pointCalculator[i] = new char[BOARD_SIZE];
    }
    
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j = 0; j <BOARD_SIZE; j++) {
            this->pointCalculator[i][j] = EMPTY;
        }
    }
    
    for(int i = 0; i <= BOARD_SIZE-1; i++) {
        for(int j = BOARD_SIZE-1; j >= 0; j--) {
            if(i+j < BOARD_SIZE-1) {
                this->turnBoard[i][j].setColour(' ');
            }

            else {
                this->turnBoard[i][j].setColour(EMPTY);
            }
            
        }
    }
    
    for(int i = 0; i <= BOARD_SIZE-1; i++) {
       
        this->pointBoard[i][i] =    EMPTY_DARK_BLUE;
        this->pointBoard[i][i+1] =  EMPTY_YELLOW;
        this->pointBoard[i][i+2] =  EMPTY_RED;
        this->pointBoard[i][i+3] =  EMPTY_BLACK;
        this->pointBoard[i][i+4] =  EMPTY_LIGHT_BLUE;
        
        this->pointBoard[i][i-1] =  EMPTY_LIGHT_BLUE;
        this->pointBoard[i][i-2] =  EMPTY_BLACK;
        this->pointBoard[i][i-3] =  EMPTY_RED;
        this->pointBoard[i][i-4] =  EMPTY_YELLOW;
    }
    
    remaining = new LinkedList();
    for(int i =0; i < BROKEN_LEN; i++) {

        this->broken[i] = nullptr;
    }
}

Mosaic::~Mosaic() {

    player->~Player();
    for(int i =0; i < BOARD_SIZE; i++) {
        delete this->pointBoard[i];
        delete this->turnBoard[i];
        delete this->pointCalculator[i];
    }

    for(int i =0; i < BROKEN_LEN; i++) {
        delete broken[i];
    }
    delete this->remaining;
}

bool Mosaic::isFirstPlayer() {

    return this->containFirst;
}

bool Mosaic::tilePlacing(int row, Colour c, int number) {

    row -= 1;
    if(c == FIRST_PLAYER) {
        this->containFirst = true;
        this->broken[this->brokenPts] = new Tile(c);
        this->brokenPts++;
        return true;
    }
    
    bool valid = false;
    for(int i = 0; i <BOARD_SIZE; i++) {
       if(this->pointBoard[row][i].getColour() == tolower(c)) {
           valid = true;
       }    
    }

    for(int i = 0; i <BOARD_SIZE; i++) {
        if(this->turnBoard[row][i].getColour() != EMPTY && this->turnBoard[row][i].getColour() != c && this->turnBoard[row][i].getColour() != ' ') {
            valid = false;
        }
    }
    
    if(valid == true) {
        for (int i =0; i <= BOARD_SIZE; i++) {
           
            if(this->turnBoard[row][5-i].getColour() == EMPTY && number != 0) {

                this->turnBoard[row][5-i] = c;
                number--;
            }
        }

        if(number != 0) {
            for(int i =0; i < number; i++) {
                if(brokenPts < BROKEN_LEN) {
                    
                    this->broken[this->brokenPts] = new Tile(c);
                    this->brokenPts++;

                }
            }
        }
        return valid;
    }
    else { 
            if(number != 0) { 
                for(int i =0; i < number; i++)
                {
                    if(brokenPts < BROKEN_LEN)
                    {
                        this->broken[this->brokenPts] = new Tile(c);
                        this->brokenPts++;
                        
                    }
                }
            }
        return valid;
    }  
}

void Mosaic::checkTurn() {
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        bool rowisfull = true;
        Colour c = EMPTY;
        for (int j = BOARD_SIZE-1; j >= 0; j--) {
            if(this->turnBoard[i][j].getColour() == EMPTY) {
                rowisfull = false;
            }
            else if(this->turnBoard[i][j].getColour() != ' ') {

                c = this->turnBoard[i][j].getColour();
            }
        }
        
        if(rowisfull == true) {
            for (int j = BOARD_SIZE-1; j >= 0; j--) {

                if(this->turnBoard[i][j].getColour() != ' ' && j < NUMBEROFTILE) {
                    this->turnBoard[i][j].setColour(EMPTY);
                    remaining->addBack(new Tile(c));
                }
                
                if(this->pointBoard[i][j].getColour() == tolower(c)) {
                    this->pointBoard[i][j].setColour(c);
                    this->pointCalculator[i][j] = OCCUPIED;
                }
            }
            this->turnBoard[i][NUMBEROFTILE].setColour(EMPTY);
        }
    }
    this->pointCalculation();  
}


bool Mosaic::checkWin() {
    for(int i =0; i < BOARD_SIZE; i++) {

        bool rowisfull = true;
        
        for(int j =0; j < BOARD_SIZE; j++) {

            if(this->pointBoard[i][j].getColour() == tolower(this->pointBoard[i][j].getColour())) {

                rowisfull = false;
            }  
        }
        
        if(rowisfull) {

            return true;
        }
    }  
    return false;
}

LinkedList* Mosaic::returnTile() {
    for(int i = 0; i < brokenPts; i++) {

            this->remaining->addBack(broken[i]);
            this->broken[i] = new Tile(' ');
    }

    this->brokenPts = 0;
    return this->remaining;
}

Player* Mosaic::getPlayer() {

    return this->player;
}

bool Mosaic::isPlayerTurn() {

    return this->currentTurn;
}

void Mosaic::setTurn(bool turn) {

    this->currentTurn = turn;
}

void Mosaic::setFirst(bool first) {

    this->containFirst = first;
}

void Mosaic::printMosaic() {

    cout<<"Mosaic for "<< this->player->getName() <<endl;
    
    for(int i =0; i < BOARD_SIZE; i++) {

        cout<<i+1<<": ";
        
        for (int j =0; j < BOARD_SIZE ;j++ ) {

            cout<<this->turnBoard[i][j].getColour();
            cout<<"  ";
        }

        cout<<"||";

        for (int j =0; j < BOARD_SIZE ;j++ ) {

            cout<<"  ";
            cout<<this->pointBoard[i][j].getColour();
        }
        cout<<endl;
    }
    
    cout <<"broken: ";

    for(int i = 0; i < BROKEN_LEN; i++) {

        if(broken[i] != nullptr) {

            cout<<broken[i]->getColour()<<" ";
            cout <<" ";
        }
    }
    cout<<endl;
}

void Mosaic::pointCalculation() {

    int point = this->player->getPoints();
    std::vector<int> checkI;
    std::vector<int> checkJ;
    bool horizontal = true;
    bool vertical = true;
    
    for(int i = 0; i < BOARD_SIZE; i++) {

        for(int j = 0; j < BOARD_SIZE; j++) {

            if(pointCalculator[i][j] == OCCUPIED) {

                checkI.push_back(i);
                checkJ.push_back(j);
            }
        }
    }
    
    for(int x = 0; x < (signed)checkI.size(); x++) {

        pointCalculator[checkI[x]][checkJ[x]] = COUNTED;
        bool addhorizontal = false;
        bool addvertical = false;
        
        for(int y = checkJ[x]+1; y < BOARD_SIZE; y++) {

            if(pointCalculator[checkI[x]][y] == COUNTED) {

                point++;
                if(y == checkJ[x]+1) {

                    addhorizontal = true;
                    point++;
                }
            }
            else {
                y = 5;
                horizontal = false;
            }
        }
        
        for(int y = checkJ[x]-1; y >= 0; y--) {

            if(pointCalculator[checkI[x]][y] == COUNTED) {
              
               point++;
               
               if(addhorizontal == false) {

                   addhorizontal = true;
                   point++;
               }
           }

           else {
               y = 0;
               horizontal = false;
           }
           
        }
        
        for(int y = checkI[x]+1; y <  BOARD_SIZE; y++) {

           if(pointCalculator[y][checkJ[x]] == COUNTED) {

               point++;
               if(y == checkI[x]+1) {

                   addvertical = true;
                   point++;
               }
           }
           else {
               y = 5;
               vertical = false;
           }
        }

        for(int y = checkI[x]-1; y >= 0; y--) {

           if(pointCalculator[y][checkJ[x]] == COUNTED) {
               
               point++;

               if(addvertical == false) {
                   addvertical = true;
                   point++;
               }
           }
           else {
               y = 0;
               vertical = false;
           }
        }
        
        if(addvertical == false && addhorizontal == false) {

            addvertical = true;
            point++;
        }
        
        
        if(vertical == true) {

            point += 7;
        }

        if(horizontal == true) {

            point +=2;
        }
       
    }
    
    
    for (int i = 0; i <= brokenPts; i++) {

       if(broken[i] != nullptr) {
         if(i < 2) point--;
         else if(i < 5) point-=2;
         else point -=3;
       }
       else {
           i = brokenPts+1;
       }
        
    }
    
    int RCount = 0;
    int UCount = 0;
    int YCount = 0;
    int BCount = 0;
    int LCount = 0;
    
    for(int i = 0; i <  BOARD_SIZE; i++) {

        for(int j = 0; j <  BOARD_SIZE; j++) {

            if(this->pointBoard[i][j].getColour() == RED) RCount++;
            else if(this->pointBoard[i][j].getColour() == LIGHT_BLUE) LCount++;
            else if(this->pointBoard[i][j].getColour() == DARK_BLUE) BCount++;
            else if(this->pointBoard[i][j].getColour() == YELLOW) YCount++;
            else if(this->pointBoard[i][j].getColour() == BLACK) UCount++;
        }
    }

    if(UCount == 5 && this->colourCounting[0] == false) {point+=10; this->colourCounting[0] = true;}
    if(LCount == 5 && this->colourCounting[1] == false) {point+=10; this->colourCounting[1] = true;}
    if(BCount == 5 && this->colourCounting[2] == false) {point+=10; this->colourCounting[2] = true;}
    if(YCount == 5 && this->colourCounting[3] == false) {point+=10; this->colourCounting[3] = true;}
    if(RCount == 5 && this->colourCounting[4] == false) {point+=10; this->colourCounting[4] = true;}
    
    this->player->setPoints(point);
}

void Mosaic::setPlayer(Player *player) {

    this->player = player;
}

void Mosaic::setPointsBoard(Tile **pointBoard) {

    this->pointBoard = pointBoard;
    int RCount = 0;
    int UCount = 0;
    int YCount = 0;
    int BCount = 0;
    int LCount = 0;
    
    for(int i = 0; i <  BOARD_SIZE; i++) {
        for(int j = 0; j <  BOARD_SIZE; j++) {
            switch (pointBoard[i][j].getColour()) {
                case RED: RCount++;
                case BLACK: UCount++;
                case LIGHT_BLUE: LCount++;
                case DARK_BLUE: BCount++;
                case YELLOW: YCount++;
            }
        }
    }

    if(UCount == 5 && this->colourCounting[0] == false) this->colourCounting[0] = true;
    if(LCount == 5 && this->colourCounting[1] == false) this->colourCounting[1] = true;
    if(BCount == 5 && this->colourCounting[2] == false) this->colourCounting[2] = true;
    if(YCount == 5 && this->colourCounting[3] == false) this->colourCounting[3] = true;
    if(RCount == 5 && this->colourCounting[4] == false) this->colourCounting[4] = true;
    
}

void Mosaic::setTurnsBoard(Tile **turnBoard) {
    this->turnBoard = turnBoard;
}

void Mosaic::setRemaining(LinkedList *remaining) {
    this->remaining = remaining;
}

void Mosaic::setBroken(Tile* tile,int location) {
    this->broken[location] = tile;
}

void Mosaic::setPointCalculator(char **pointCalculator) {
    this->pointCalculator = pointCalculator;
}

Tile** Mosaic::getPointsBoard() {
    return this->pointBoard;
}

Tile** Mosaic::getTurnsBoard() {
   return this->turnBoard;
}

LinkedList* Mosaic::getRemaining() {
    return this->remaining;
}

Tile* Mosaic::getBroken(int index) {
    return this->broken[index];
}

char** Mosaic::getPointCalculator() {
    return this->pointCalculator;
}