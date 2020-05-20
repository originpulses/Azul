#ifndef AZUL_DATABASE_H
#define AZUL_DATABASE_H
#include <iostream>
#include "Factory.cpp"

class Database {
    
public:
    Database(std::istream inputstream);
    Factory* getFactory();
};

#endif // AZUL_DATABASE_H