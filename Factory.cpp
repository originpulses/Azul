#include "Factory.h"

Factory::Factory(int numOfPlayer, int seed) {

    if(numOfPlayer == NUMBEROFPLAYER) {

        this->numOfFactory = NOFACTORY;
    }
    
    tileBag = new LinkedList();
    boxLid = new LinkedList();
    
    factories = new Tile*[this->numOfFactory];
    
    this->factories[0] = new Tile[this->numOfFactory * MAX_REMAIN];
    
    for(int i = 1; i < this->numOfFactory; i++) {

        this->factories[i] = new Tile[NUMBEROFTILE];
    }
    
       for(int i =0; i != 20; i++)this->boxLid->addBack(new Tile(RED));
       for(int i =0; i != 20; i++)this->boxLid->addBack(new Tile(BLACK));
       for(int i =0; i != 20; i++)this->boxLid->addBack(new Tile(YELLOW));
       for(int i =0; i != 20; i++)this->boxLid->addBack(new Tile(DARK_BLUE));
       for(int i =0; i != 20; i++)this->boxLid->addBack(new Tile(LIGHT_BLUE));

   if(seed > -1) {
    this->setUp(seed);
   }
}

Factory::~Factory() {

    delete tileBag;
    delete boxLid;
    this->numOfFactory = 0;
    
    for(int i= 0; i != this->numOfFactory; i++) {

        delete this->factories[i];
    }

    delete this->factories;
}

int Factory::takeTile(Colour c, int factory) {

    int numOfTile = 0;
    if(factory != 0) {

        if(this->containColour(c, factory) ) {

            for(int i =0; i < 4; i++) {

                if(this->factories[factory][i].getColour() == c) {

                    numOfTile++;
                    this->factories[factory][i] = ' ';
                }
                else {
                    this->factories[0][this->leftover] = this->factories[factory][i].getColour();
                    this->factories[factory][i] = ' ';
                    this->leftover++;
                }
            }
        }
    }

    else {
        
        if(this->containColour(c, factory) ) {

            for(int i =0; i < this->numOfFactory * MAX_REMAIN; i++) {

                if(this->factories[factory][i].getColour() == c) {
                    numOfTile++;
                    this->factories[factory][i] = ' ';
                }
            }
        }
    }

    size -= numOfTile;
    return numOfTile;
}

bool Factory::containColour(Colour c, int factory) {

    if(factory != 0) {

        for(int i =0; i < NUMBEROFTILE; i++) {

            if(this->factories[factory][i].getColour() == c) {
                return true;
            }
        }
    }
    else {
        for(int i =0; i < this->numOfFactory * MAX_REMAIN; i++) {

            if(this->factories[factory][i].getColour() == c) {
                return true;
            }
        }
    }
    return false;
}

void Factory::addRemainder(Tile *tile) {

   if(tile != nullptr && tile->getColour() != FIRST_PLAYER) {
    this->boxLid->addBack(tile);
   }
}

void Factory::printFactory() {

    cout <<"Factories: "<<endl;
    cout << 0 <<": ";
    for(int j =0; j < this->numOfFactory*MAX_REMAIN; j++) {

        if(this->factories[0][j].getColour() != ' ') {
            cout <<this->factories[0][j].getColour()<<" ";
        }
    }
    cout<<endl;
    for(int i =1; i < this->numOfFactory; i++) {

        cout << i <<": ";
        for(int j =0; j < NUMBEROFTILE; j++) {
           cout <<this->factories[i][j].getColour()<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void Factory::setUp(int seed) {
    
    this->leftover = 1;
    
    for(int i = 1; i < this->numOfFactory * MAX_REMAIN; i++) {
        this->factories[0][i] = ' ';
    }
    this->factories[0][0] = FIRST_PLAYER;
   
    if(shuffled == false) {
        this->boxLid->shuffle(seed);
        shuffled =true;
    }
    
    for(int i =0; i < NUMBEROFTILE*(this->numOfFactory -1); i++) {

        Tile* tmp = this->boxLid->get();
        if(tmp != nullptr) {
            this->tileBag->addFront(tmp);
        }
    }
    size = 1;
    
    for(int i = 1; i < this->numOfFactory; i++) {
        for(int j = 0; j<4; j++) {
            size++;
            this->factories[i][j] = tileBag->get()->getColour();
        }
    }
    this->first = true;    
}



bool Factory::isEmpty() {

   if(size > 0) {
       return false;
   }
    return true;
}

void Factory::removeFirst() {

    factories[0][0] = ' ';
    this->first = false;
    this->size -=1;
}

bool Factory::isFirst() {
    return this->first;
}

void Factory::setTileBag(LinkedList* tileBag) {
    this->tileBag = tileBag;
}

void Factory::setBoxLid(LinkedList *boxLid) {
    this->boxLid = boxLid;
}

void Factory::setNumOfFactory(int numOfFactory) {
    this->numOfFactory = numOfFactory;
}

void Factory::setFactories(Tile **factories) {

    this->factories = factories;
    int size = 0;
    int left = 0;
    
    for(int i =1; i < this->numOfFactory; i++) {

        for(int j =0; j < NUMBEROFTILE; j++) {

            if(this->factories[i][j].getColour() != ' ') {
                size++;
            }
        }
    }
   
    for(int i = 0; i < MAX_REMAIN*this->numOfFactory; i++) {

        if(this->factories[0][i].getColour() != ' ') {
            left++;
            if(this->factories[0][i].getColour() == FIRST_PLAYER) {
                this->first = true;
            }
        }
    }

    this->size = size +left;
    this->leftover = left;
}

LinkedList* Factory::getTileBag() {
    return this->tileBag;
}

LinkedList* Factory::getBoxLid() {
    return this->boxLid;
}

int Factory::getNumOfFactory() {
    return this->numOfFactory;
}

Tile** Factory::getFactory() {
    return this->factories;
}