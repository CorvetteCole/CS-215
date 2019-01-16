//--------------------------------------------------------------------
// CS215-005 LAB 1 005 should be your section
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: January 16th 2019
// Description: My first C++ program. It does arithmetic on two numbers.
//--------------------------------------------------------------------
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	cout << "      Number Fun          \n";
	cout << "   By Cole Gerdemann      \n";
	cout << "\n";

	//obtain two numbers from the user
	int numberOne;
	int numberTwo;
	cout << "Enter a number: ";
	cin >> numberOne;
	cout << "Enter another: ";
	cin >> numberTwo;

	cout << "\n";

	//math block using the two numbers obtained from the user
	int sum = numberOne + numberTwo;
	int difference = numberOne - numberTwo;
	int product = numberOne * numberTwo;
	int lossyQuotient = numberOne / numberTwo;
	float quotient = (float)numberOne / numberTwo;

	//display math results using the two numbers
	cout << setw(21) << left << "Sum: " << sum << "\n";
	cout << setw(21) << left << "Difference: " << difference << "\n";
	cout << setw(21) << left << "Product: " << product << "\n";
	cout << setw(21) << left << "Int Quotient: " << lossyQuotient << "\n";
	cout << setw(21) << left << "Quotient: " << quotient << "\n";
	
	system("pause");
	return 0;




}
