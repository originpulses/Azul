#include "LinkedList.h"

LinkedList::LinkedList()
{
	this->head = nullptr;
	this->size = 0;
}

void LinkedList::insert(char data)
{
	if (this->head == nullptr)
	{
		this->head = new Node();
		head->data = data;
	}
	else
	{
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

void LinkedList::removeAll(vector<char>& lid, bool check)	//This function will also move all the broken tiles to the back of the lid
{
	Node* cur = this->head;
	while (cur != nullptr)
	{
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

void LinkedList::print()
{
	Node* temp = this->head;
	//printf("Broken: ");
	cout << "Broken: ";
	while (temp != nullptr)
	{
		if (temp->data == 'F' || temp->data == 'B' || temp->data == 'Y' || temp->data == 'R' || temp->data == 'U' || temp->data == 'L')
			//printf("%c ", temp->data);
			cout << temp->data << " ";
		temp = temp->next;
	}
	//printf("\n");
	cout << "\n";
}

int LinkedList::getSize()
{
	return this->size;
}

Node* LinkedList::Head()
{
	return this->head;
}
