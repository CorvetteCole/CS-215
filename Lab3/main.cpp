//--------------------------------------------------------------------
// CS215-005 LAB 3 005
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: January 29th 2019
// Description:   a program to be used as a “cash register” at a small
// hot dog stand.
//--------------------------------------------------------------------
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	cout << "---- Cole Gerdemann's Hot Dogs & Drinks ----" << endl;
	cout << endl;

	const double hotDogPrice = 2.50;
	const double deluxeHotDogPrice = 3.50;
	const double smallDrinkPrice = 1.50;
	const double largeDrinkPrice = 2.25;
	const double taxRate = .06;

	double subTotal = 0;
	double tax;
	double total;
	double cash;

	char menuInput;

	do {
		// print menu
		cout << endl;

		cout << setw(25) << left << "H - Hot Dog" << "$" << setw(6) << hotDogPrice;
		cout << setw(25) << left << "D - Deluxe Hot Dog" << "$" << deluxeHotDogPrice << endl;

		cout << setw(25) << left << "S - Small Drink" << "$" << setw(6) << smallDrinkPrice;
		cout << setw(25) << left << "L - Large Drink" << "$" << largeDrinkPrice << endl;

		cout << setw(25) << left << "F - Finish Order";
		cout << setw(22) << right << "X - Exit system" << endl;

		cout << "Enter option ====> ";

		// get user input
		char input;
		input = cin.peek();
		cin.clear();
		cin.ignore(10000, '\n');
		menuInput = tolower(input);

		switch (menuInput) {
		case 'h':
			subTotal += hotDogPrice;
			break;
		case 'd':
			subTotal += deluxeHotDogPrice;
			break;
		case 's':
			subTotal += smallDrinkPrice;
			break;
		case 'l':
			subTotal += largeDrinkPrice;
			break;
		default:
			break;
		}

		if (menuInput != 'x' && menuInput != 'f') {
			cout << setw(20) << left << "Current Sub Total: " << "$" << subTotal << endl;
		}
		else if (menuInput == 'f') {
			tax = subTotal * taxRate;
			total = subTotal + tax;
			cout << setw(15) << left << "Sub Total: " << "$" << subTotal << endl;
			cout << setw(15) << left << "Tax: " << "$" << tax << endl;
			cout << setw(15) << left << "Total: " << "$" << total << endl;
			cout << setw(15) << left << "Enter cash: " << "$";
			cin >> cash;
			cout << setw(15) << left << "Change: " << "$" << cash - total << endl;


			subTotal = 0;
			cout << "Press any key to continue..." << endl;
			// replaces system("pause") since this is Windows specific
			cin.ignore();
			cin.get();

		}

	} while (menuInput != 'x');


	cout << "Press any key to continue..." << endl;
	// replaces system("pause") since this is Windows specific
	cin.ignore();
	cin.get();

	return 0;
}