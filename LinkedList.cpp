#include "LinkedList.h"

LinkedList::LinkedList() {

	this->head = nullptr;
	this->size = 0;
}

 LinkedList::~LinkedList(){}

void LinkedList::insert(char data) {

	if (this->head == nullptr) {

		this->head = new Node();
		head->data = data;
	}

	else {
		Node* temp = this->head;
		while (temp->next != nullptr)
			temp = temp->next;

		Node* T = new Node();
		T->data = data;
		temp->next = T;
		//delete temp;
	}
	this->size++;
}

//This function will also move all the broken tiles to the back of the lid
void LinkedList::removeAll(vector<char>& lid, bool check) {
	Node* cur = this->head;
	while (cur != nullptr) {
		Node* next = cur->next;
		if (check && cur->data != 'F')	//First player tiles should not be added into lid or box
		{
			lid.push_back(cur->data);
		}
		delete cur;
		cur = next;
	}
	this->head = nullptr;
	this->size = 0;
}

void LinkedList::print() {

	Node* temp = this->head;
	cout << "Broken: ";
	while (temp != nullptr) {

		if (temp->data == 'B') {

			cout << "\033[48;2;0;9;255m" << "B" << "\033[m "; // Dark Blue
		}
		else if (temp->data == 'L') {

			cout << "\033[48;2;101;136;233m" << "L" << "\033[m ";//Light Blue
		}
		else if (temp->data == 'R') {

			cout << "\033[48;2;255;0;0m" << "R" << "\033[m "; //Red
		}
		else if (temp->data == 'U') {

			cout << "\033[48;2;0;0;0m" << "U" << "\033[m "; //Black
		}
		else if (temp->data == 'O') {

			cout << "\033[48;2;255;165;0;30m" << "O" << "\033[m ";  // Orange
		}
		else if (temp->data == 'Y') {

			cout << "\033[48;2;255;255;0;30m" << "Y" << "\033[m "; // Yellow
		}
		else if (temp->data == 'F') {

			cout << "\033[48;2;255;255;255;30m" << "F" << "\033[m "; // First player tile
		}
		temp = temp->next;
	}
}

int LinkedList::getSize() {

	return this->size;
}

Node* LinkedList::Head() {
	
	return this->head;
}
