#include <iostream>
#include <string>
#include <vector>
#include "FubctionsHeader.h"
#include <conio.h>
#include "di.hpp"
namespace di = boost::di;
using namespace std;

void show_Menu() {
	cout << "Menu: \n";
	cout << "[1]: Add note" << endl;
	//cout << "[2]: Show all notes" << endl;
	cout << "[2]: Find note" << endl;
	cout << "[3]: Remove one note" << endl;
	cout << "[4]: Remove all notes" << endl;
	cout << "[5]: Add note to complited" << endl;
	//cout << "[7]: Show complited" << endl;
	cout << "[6]: Find note complited" << endl;
	cout << "[7]: Remove note from complited" << endl;
	cout << "[8]: Remove all complited" << endl;
	cout << "[9]: Exit" << endl;
}

int main()
{
	ToDoList lst;
	system("color 71");

	while (true) {
		system("cls");

		cout << "Uncomplited tasks: " << endl;

		lst.Print(10);

		cout << "\n" << "===========================================" << "\n\n";

		cout << "Complited tasks: " << endl;
		lst.Print(11);
		cout << endl;

		show_Menu();

		cout << "Your choise: ";
		int choise = 0;
		cin >> choise;

		if (choise == 9) break;
		else {
			system("cls");
			lst.Print(choise);
			system("pause");
		}
	}

	


	return 0;
    
}

