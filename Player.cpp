#include "Player.h"

Player::Player(std::string name) {

    this->name = name;
    this->pt = 0;
}

Player::~Player() {

    this->name = "";
    this->pt = 0;
}

void Player::setPoints(int points) {

   if(points >= 0)this->pt = points; 
   else this->pt = 0;
}

int Player::getPoints() {

    return this->pt;
}

std::string Player::getName() {

    return this->name;
}

void Player::print() {
    
    cout <<"Name: "<< this->name <<endl;
    cout <<"Points: "<< this->pt <<endl;
    cout<<endl;
}