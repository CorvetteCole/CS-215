//--------------------------------------------------------------------
// CS215-005 LAB 1 005
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: January 29th 2019
// Description: Project 1
//--------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main() {

    double highOctaneLevels = -1;
    double mediumOctaneLevels;
    double lowOctaneLevels;

    double highOctanePrice;
    double mediumOctanePrice;
    double lowOctanePrice;

    ifstream gasLevelsInput("pumpin.txt");
    if (gasLevelsInput.is_open()) {
        for (string line; getline(gasLevelsInput, line);) {
            istringstream iss(line);
            if (highOctaneLevels == -1) {
                iss >> highOctaneLevels;
                iss >> mediumOctaneLevels;
                iss >> lowOctaneLevels;
            } else {
                iss >> highOctanePrice;
                iss >> mediumOctanePrice;
                iss >> lowOctanePrice;
            }
        }
        gasLevelsInput.close();

        // print tank readings
        cout << setw(15) << left << "Tank Readings:";
        cout << setw(5) << right << "Hi=" << fixed << setprecision(2) << setw(6) << right << highOctaneLevels;
        cout << setw(6) << right << "Med=" << fixed << setprecision(2) << setw(6) << right << mediumOctaneLevels;
        cout << setw(6) << right << "Low=" << fixed << setprecision(2) << setw(6) << right << lowOctaneLevels << endl;

        cout << setw(15) << left << "Today's PPG:";
        cout << setw(6) << right << "Hi=$" << fixed << setprecision(2) << setw(5) << right << highOctanePrice;
        cout << setw(7) << right << "Med=$" << fixed << setprecision(2) << setw(5) << right << mediumOctanePrice;
        cout << setw(7) << right << "Low=$" << fixed << setprecision(2) << setw(5) << right << lowOctanePrice << endl;




    //sleep(5000); // sleep command
    } else {
        cout << "Unable to read input file." << endl;
    }

    // replaces system("pause") since this is Windows specific
    cin.ignore();
    cin.get();

    return 0;
}