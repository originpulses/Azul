#ifndef AZUL_LINKEDLIST_H
#define AZUL_LINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>

#include "Node.h"

using std::vector;
using std::cout;
using std::endl;

class LinkedList {
private:
	Node* head;
	int size = 0;

public:
	LinkedList(); //Constructor
	~LinkedList();

	void insert(char data); //Inserts the char data at the end of the list
	void removeAll(vector<char>& lid, bool check);// Removes all nodes from list, This function will also move all the broken tiles to the back of the lid
	void print();	// Print data of all nodes in linear form
	int getSize();
	Node *Head();	// Returns the head pointer of list
};

#endif // AZUL_LINKEDLIST_H