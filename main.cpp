#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::cin;
using std::string;

void mainMenu(void);
void Credits(void);

int main(void) {
   mainMenu();
}

void mainMenu(void) {
	cout<<"=================="<<endl;
	cout<< " Welcome to Azul!" <<endl;
	cout<<"=================="<<endl;
	bool exit = false;
	while(exit != true) {
		cout<<endl;
		cout<< "Menu" <<endl;
		cout<< "----" <<endl;
		cout<< "1. New Game" <<endl;
		cout<< "2. Load Game" <<endl;
		cout<< "3. Credits (Students Info)" <<endl;
		cout<< "4. Quit\n\n> ";
		string choice;
		cin>>choice;
			
	if(choice == "1") {
		//TODO
	}

	else if(choice == "2") {
		//TODO
	}

	else if(choice == "3") {
		Credits();
	}

	else if(choice == "4") {
		cout << "Goodbye" <<endl;;
		std::exit(EXIT_SUCCESS);
	}
			
	else if (std::cin.eof()) {
		cout << "Goodbye." <<endl;
		std::exit(EXIT_SUCCESS);
	}

	else {
		cout << "Invalid input";
	}
		
	 cout<<endl;
	}
}

void Credits(void) {
	cout<<"=========================="<<endl;
	cout<< " Team Name: AZUL UNITED" <<endl;
	cout<<"==========================\n\n";
	cout<< "----------------------------------" <<endl;
	cout<< "Student 1:\n\n";
	cout<< "Name: Syed Sabih Ali" <<endl;
	cout<< "Student ID: s3528350" <<endl;
	cout<< "Email: s3528350@student.rmit.edu.au" <<endl;
	cout<< "----------------------------------\n\n";
	cout<< "----------------------------------" <<endl;
	cout<< "Student 2:\n\n";
	cout<< "Name: Carlo Manfredi" <<endl;
	cout<< "Student ID: s3545832" <<endl;
	cout<< "Email: s3545832@student.rmit.edu.au" <<endl;
	cout<< "----------------------------------\n\n";
	cout<< "----------------------------------" <<endl;
	cout<< "Student 3:\n\n";
	cout<< "Name: Stephen Finlay" <<endl;
	cout<< "Student ID: S3786139" <<endl;
	cout<< "Email: S3786139@student.rmit.edu.au" <<endl;
	cout<< "----------------------------------\n\n";
}