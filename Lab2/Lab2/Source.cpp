//--------------------------------------------------------------------
// CS215-005 LAB 1 005 
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: January 23rd 2019
// Description:  a program that asks the user to enter 3 numbers, one at a time. Prints the three numbers
// in sorted order then shows a menu of peppers. 
//--------------------------------------------------------------------
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	int num1;
	int num2;
	int num3;

	cout << "Enter number 1: ";
	cin >> num1;
	cout << endl << "Enter number 2: ";
	cin >> num2;
	cout << endl << "Enter number 3: ";
	cin >> num3;

	int largest;
	int middle;
	int smallest;

	// sort numbers
	if (num1 > num2 && num1 > num3) {
		largest = num1;
		if (num3 < num2) {
			smallest = num3;
			middle = num2;
		} else {
			smallest = num2;
			middle = num3;
		}
	} else if (num3 > num1 && num3 > num2) {
		largest = num3;
		if (num2 < num1) {
			smallest = num2;
			middle = num1;
		} else {
			smallest = num1;
			middle = num2;
		}
	} else {
		largest = num2;
		if (num3 < num1) {
			smallest = num3;
			middle = num1;
		} else {
			smallest = num1;
			middle = num3;
		}
	}

	cout << endl << smallest << " " << middle << " " << largest << endl;

	cout << "A. Aleppo Pepper " << endl;
	cout << "B. Banana Pepper " << endl;
	cout << "C. Cayenne Pepper " << endl;
	cout << "D. Dragons Breath " << endl;
	cout << "Enter a letter to choose a pepper:  ";

	char menuInput;
	cin >> menuInput;
	menuInput = tolower(menuInput);

	int heat;
	switch (menuInput) {
		case 'a':
			heat = 30000;
			break;
		case 'b':
			heat = 1000;
			break;
		case 'c':
			heat = 40000;
			break;
		case 'd':
			heat = 2480000;
			break;
		default: 
			heat = 0;
	}

	// check if pepper was on the list
	if (heat == 0) {
		cout << endl << "That pepper is not on the list";
	} else {
		cout << endl << "That's " << heat << " Scovilles of heat!";
	}

	// replaces system("pause") since this is Windows specific
	cin.ignore();
	cin.get();

	return 0;
}