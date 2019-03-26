#include <iostream>

using namespace std;

const int maxFractions = 10;

struct fraction {
	int numerator;
	int denominator;
	double decimalValue;
};

//--------------------------------------
// askFraction
//--------------------------------------
fraction askFraction() {
	fraction fractionVariable{};
	cout << "Enter numerator: ";
	cin >> fractionVariable.numerator;
	do {
		cout << "Enter denominator: ";
		cin >> fractionVariable.denominator;
		if (fractionVariable.denominator == 0) {
			cout << "Denominator cannot be 0" << endl;
		}
	} while (fractionVariable.denominator == 0);
	return fractionVariable;
}

//--------------------------------------
// calcDecimal
//--------------------------------------
void calcDecimal(fraction &fractionVariable) {
	if (fractionVariable.denominator == 0) {
		fractionVariable.decimalValue = 0.0;
	}
	else {
		fractionVariable.decimalValue = (double)fractionVariable.numerator / fractionVariable.denominator;
	}
}
//--------------------------------------
// printFraction
//--------------------------------------
void printFraction(fraction fractionVariable) {
	cout << fractionVariable.numerator << " / " << fractionVariable.denominator << " (" << fractionVariable.decimalValue << ")";
}
//--------------------------------------
// askFractionList
//--------------------------------------
void askFractionList(fraction(&fractionList)[maxFractions], int &fractionListSize) {
	do {
		cout << "How many fractions in your list? ";
		cin >> fractionListSize;
		if (fractionListSize <= 0 || fractionListSize > 10) {
			cout << "Enter a number between 1 and 10" << endl;
		}
	} while (fractionListSize <= 0 || fractionListSize > 10);
	for (int i = 0; i < fractionListSize; i++) {
		cout << "For fraction " << i + 1 << endl;
		fractionList[i] = askFraction();
		calcDecimal(fractionList[i]);
	}
}

//--------------------------------------
// printFractionList
//--------------------------------------
void printFractionList(fraction fractionList[], int fractionListSize) {
	for (int i = 0; i < fractionListSize; i++) {
		printFraction(fractionList[i]);
		cout << endl;
	}
}

//--------------------------------------
// findMaxFraction
//--------------------------------------
int findMaxFraction(fraction fractionList[], int fractionListSize) {
	if (fractionListSize == 0) {
		return  -1;
	}
	double max = DBL_MIN;
	int maxIndex = 0;
	for (int index = 0; index < fractionListSize; index++) {
		if (fractionList[index].decimalValue > max) {
			maxIndex = index;
			max = fractionList[index].decimalValue;
		}
	}
	return maxIndex;
}

int main() {
	int fractionListSize;
	fraction fractionList[maxFractions] = {};

	askFractionList(fractionList, fractionListSize);
	printFractionList(fractionList, fractionListSize);
	cout << "The highest value fraction is: ";
	printFraction(fractionList[findMaxFraction(fractionList, fractionListSize)]);

	//pause
	cin.get();
	cin.ignore();
	return 0;
}