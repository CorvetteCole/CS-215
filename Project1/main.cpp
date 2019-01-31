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
#include <zconf.h> //import this for device agnostic sleep
//#include <windows.h> //import this if using Windows only

using namespace std;

void pumpGas(double totalGallons){
    cout << endl << "Pumping gas..." << endl;
    //use int and multiply total by two instead of double because floating points in for loops is bad practice
    for (int x = 1; x < totalGallons * 2; x += 1 ){
        if (x % 2 == 0) {
            cout << x / 2.00 << " gallons pumped..." << endl;
        } else {
            cout << x - (x / 2.00) << " gallons pumped..." << endl;
        }
        sleep(2); //use this on any device
        //sleep(2000); //use this on Windows only
    }
    cout << totalGallons << " gallons pumped..." << endl;
}

void printReceipt(char octane, double price, double gallons){
    string octaneFull;
    switch (octane){
        case 'l': {
            octaneFull = "Low";
            break;
        }
        case 'm': {
            octaneFull = "Medium";
            break;
        }
        case 'h': {
            octaneFull = "High";
            break;
        }
        default: {
            octaneFull = octane;
            break;
        }
    }
    cout << endl << "---------- Your Receipt ----------" << endl;
    cout << setw(24) << left << "Octane:" << octaneFull << endl;
    cout << setw(24) << left << "Price per gallon: " << '$' << price << endl;
    cout << setw(24) << left << "Total:" << '$' << price * gallons << endl;
    cout << "Thank you for your patronage" << endl;
    cout << "----------------------------------" << endl;
}

double getGallonsToPump(double selectedOctaneLevels){
    double gallonsToPump;
    cout << endl << "Enter number of gallons (-1 to fill it up): ";
    cin >> gallonsToPump;
    cin.clear();
    if (gallonsToPump == -1) {
        srand(time(nullptr));  //set seed for rand() to the time, otherwise it will always default to 1
        gallonsToPump = (rand() % 7) + 1;
        cout << "Sensor reports " << gallonsToPump << " gallons needed to fill up.";
    }
    if (gallonsToPump > selectedOctaneLevels) {
        cout << "Sorry, our tank is nearly empty. We only have " << selectedOctaneLevels << " gallons available."
             << endl;
        gallonsToPump = selectedOctaneLevels;
    }
    return gallonsToPump;
}

char getOctane(){
    cout << endl;
    do {
        string input;
        cout << "Select octane (H/M/L): ";
        cin >> input;
        cin.clear();
        if (input.length() == 1 &&
            (tolower(input[0]) == 'h' || tolower(input[0]) == 'm' || tolower(input[0]) == 'l')) {
            return (char)(tolower(input[0]));
        } else {
            cout << "Error. Please enter H, M, or L." << endl;
        }
    } while (true);
}

void printPumpLevels(double highOctaneLevels, double mediumOctaneLevels, double lowOctaneLevels){
    cout << setw(15) << left << "Tank Readings:";
    cout << setw(5) << right << "Hi=" << fixed << setprecision(2) << setw(6) << right << highOctaneLevels;
    cout << setw(6) << right << "Med=" << fixed << setprecision(2) << setw(6) << right << mediumOctaneLevels;
    cout << setw(6) << right << "Low=" << fixed << setprecision(2) << setw(6) << right << lowOctaneLevels << endl;
}

void printPumpPrices(double highOctanePrice, double mediumOctanePrice, double lowOctanePrice, bool startup){
    // print gas prices
    if (startup){
        cout << setw(15) << left << "Today's PPG:";
        cout << setw(6) << right << "Hi=$" << fixed << setprecision(2) << setw(5) << right << highOctanePrice;
        cout << setw(7) << right << "Med=$" << fixed << setprecision(2) << setw(5) << right << mediumOctanePrice;
        cout << setw(7) << right << "Low=$" << fixed << setprecision(2) << setw(5) << right << lowOctanePrice << endl;
    } else {
        cout << "Prices per Gallon:" << endl;
        cout << setw(20) << left << "High Octane: " << "$" << highOctanePrice << endl;
        cout << setw(20) << left << "Medium Octane: " << "$" << mediumOctanePrice << endl;
        cout << setw(20) << left << "Low Octane: " << "$" << lowOctanePrice << endl;
    }
}

char getRewardsStatus(){
    do {
        cout << setw(35) << left << "Are you a rewards customer? (Y/N): ";
        string input;
        cin >> input;
        cin.clear();
        if (input == "shutdown"){
            return 's';
        } else if (input.length() == 1 && tolower(input[0]) == 'y') {
            return 'y';
        } else if (input.length() == 1 && tolower(input[0]) == 'n') {
            return 'n';
        } else {
            cout << "Please enter Y or N" << endl;
        }
    } while (true);
}

int main() {

    double highOctaneLevels = -1;
    double mediumOctaneLevels = -1;
    double lowOctaneLevels = -1;

    double highOctanePrice = -1;
    double mediumOctanePrice = -1;
    double lowOctanePrice = -1;

    ifstream gasLevelsInput("pumpin.txt");
    if (gasLevelsInput.is_open()) {
        for (string line; getline(gasLevelsInput, line);) {
            istringstream iss(line);
            // check if code has read the first line yet or should read the second
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
    } else {
        cout << "Unable to read input file." << endl;
        // replaces system("pause") since this is Windows specific
        cin.ignore();
        cin.get();
        return 0;
    }

    // print gas levels and price
    printPumpLevels(highOctaneLevels, mediumOctaneLevels, lowOctaneLevels);
    printPumpPrices(highOctanePrice, mediumOctanePrice, lowOctanePrice, true);

    // loop runs all the time, return 0 is called to shut down program
    while (true) {
        double highOctanePriceRetail;
        double mediumOctanePriceRetail;
        double lowOctanePriceRetail;

        bool rewardsMember;
        double rewardsDiscount = 0;

        char selectedOctane;

        // print logo
        cout << endl << " ------ Cole Gerdemann's Gas -----" << endl;

        // find out if customer is a rewards member
        switch (getRewardsStatus()){
            case 'y': {
                rewardsMember = true;
                break;
            }
            case 'n': {
                rewardsMember = false;
                break;
            }
            case 's': {
                ofstream output;
                output.open("pumpout.txt");
                output << highOctaneLevels << " " << mediumOctaneLevels << " " << lowOctaneLevels << endl;
                output << highOctanePrice << " " << mediumOctanePrice << " " << lowOctanePrice;
                output.close();
                // print gas levels
                printPumpLevels(highOctaneLevels, mediumOctaneLevels, lowOctaneLevels);
                cout << "Pump shut down.";
                // replaces system("pause") since this is Windows specific
                cin.ignore();
                cin.get();
                return 0;
            }
            default: {
                return 0;
            }
        }

        // get rewards number and calculate discount
        if (rewardsMember) {
            cout << setw(35) << left << "Enter customer rewards number: ";
            int input;
            cin >> input;
            cin.clear();
            rewardsDiscount = ((input % 10) + 1) / 100.0;
            cout << setw(35) << left << "Price Per Gallon Discount: " << "$" << rewardsDiscount << endl << endl;
        }

        // calculate final retail prices
        highOctanePriceRetail = highOctanePrice - rewardsDiscount;
        mediumOctanePriceRetail = mediumOctanePrice - rewardsDiscount;
        lowOctanePriceRetail = lowOctanePrice - rewardsDiscount;

        printPumpPrices(highOctanePriceRetail, mediumOctanePriceRetail, lowOctanePriceRetail, false);

        // get desired octane choice
        selectedOctane = getOctane();

        // get number of gallons to pump and pump it
        switch (selectedOctane) {
            case 'l': {
                double gallonsToPump = getGallonsToPump(lowOctaneLevels);
                lowOctaneLevels -= gallonsToPump;
                pumpGas(gallonsToPump);
                printReceipt(selectedOctane, lowOctanePriceRetail, gallonsToPump);
                break;
            }
            case 'm': {
                double gallonsToPump = getGallonsToPump(mediumOctaneLevels);
                mediumOctaneLevels -= gallonsToPump;
                pumpGas(gallonsToPump);
                printReceipt(selectedOctane, mediumOctanePriceRetail, gallonsToPump);
                break;
            }
            case 'h': {
                double gallonsToPump = getGallonsToPump(highOctaneLevels);
                highOctaneLevels -= gallonsToPump;
                pumpGas(gallonsToPump);
                printReceipt(selectedOctane, highOctanePriceRetail, gallonsToPump);
                break;
            }
            default: {
                return 0;
            }
        }

        // replaces system("pause") since this is Windows specific
        cin.ignore();
        cin.get();
    }
}

