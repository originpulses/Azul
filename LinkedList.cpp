#include "LinkedList.h"

// Functional Implementation of LinkedLists
LinkedList::LinkedList() {
    
    head = nullptr;
    size = 0;
}

LinkedList::~LinkedList() {

    this->clear();
}

// Implementing our ADT's (Abstract Data Types)
int LinkedList::getSize() {

    return this->size;
}


Tile* LinkedList::get() {

    if(this->head != nullptr) {
        Node* tmp = this->head;
        this->head = tmp->next;
        this->size--;
        return tmp->tile;
    } 
    else {
        return nullptr;
    }
}

bool LinkedList::remove(Tile *tile) {

    Node* tmp = this->head;
    if(this->head->tile->getColour() == tile->getColour()) {
        this->head = this->head->next;
        delete tmp;
        this->size--;
        return true;
    }
    for(int i=0; i < this->size-1; i++) {
        if(tmp->next->tile->getColour() == tile->getColour()) {
            tmp->next = tmp->next->next;
            this->size--;
            delete tmp;
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void LinkedList::clear() {

    if(head != nullptr) {
        Node* nodeCheck = head;
        while(nodeCheck != nullptr) {
            Node* next = nodeCheck->next;
            nodeCheck = nullptr;
            delete nodeCheck;
            nodeCheck = next;
        }
        delete nodeCheck;
    }

    this->size = 0;
}

void LinkedList::addFront(Tile* tile) {

    Node* tmpHead = new Node(tile, this->head);
    this->head = tmpHead;
    this->size++;
}

void LinkedList::addBack(Tile* tile) {

    if(this->head != nullptr) {
        Node* tmp = this->head;
        while(tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new Node(tile, nullptr);
        this->size++;
    }
}

void LinkedList::shuffle(int seed) {
    std::vector<Tile*> shuffles;
    Node* node = this->head;
    while (node != nullptr) {
        shuffles.push_back(node->tile);
        node = node->next;
    }
    //Give seed to main
    std::default_random_engine e(seed);
    std::shuffle (shuffles.begin(), shuffles.end(), e);

    node = this->head;
    for(int i=0; i < (signed)shuffles.size(); i++) {

        if(shuffles[i] != nullptr) {
            node->tile = shuffles[i];
            node = node->next;
        }
    }
}

void LinkedList::printAll() {
    std::string str = " ";
    Node* node = this->head;
    while(node != nullptr) {
        str.push_back(node->tile->getColour());
        str.push_back(' ');
        node = node->next;
    }
    cout<< str <<endl;
}

