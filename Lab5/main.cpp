//--------------------------------------------------------------------
// CS215-005 LAB 5
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: February 20th 2019
// Description: Shows a menu and performs actions using loops
//--------------------------------------------------------------------
#include <iostream>
using namespace std;

int main() {
    bool exit = false;
    // main program loop
    do {
        // print menu
        char menuOption;
        cout << "S - Sum between" << endl;
        cout << "B - Print Box" << endl;
        cout << "X - Exit" << endl;
        cout << "Enter option: ";
        cin >> menuOption;
        switch (menuOption) {

            // sum some numbers
            case 'S':
            case 's': {
                int beginCount;
                int endCount;
                int total = 0;
                cout << "Enter beginning number: ";
                cin >> beginCount;
                cout << "Enter ending number: ";
                cin >> endCount;

                for (int i = beginCount; i <= endCount; i++) {
                    total = total + i;
                }
                cout << "Sum: " << total << endl;
                break;
            }

            // print box
            case 'B':
            case 'b': {
                cout << "Enter size of box: ";
                int boxSize;
                cin >> boxSize;
                for (int i = 0; i < boxSize; i++) {
                    cout << endl;
                    for (int j = 0; j < boxSize; j++) {
                        cout << "* ";
                    }
                }
                cout << endl;
                break;
            }

            case 'X':
            case 'x': {
                exit = true;
                break;
            }

            default: {
                cout << "Invalid option! Try again!" << endl;
                break;
            }
        }

    } while (!exit);
    system("pause");
}