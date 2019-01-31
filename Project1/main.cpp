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
#include <zconf.h> //import this if using Linux
//#include <windows.h> //import this if using Windows

using namespace std;

void pumpGas(double totalGallons){
    cout << endl << "Pumping gas..." << endl;
    for (double x = .5; x < totalGallons; x += .5 ){
        cout << x << " gallons pumped..." << endl;
        sleep(2); //use this on linux
        //sleep(2000); //use this on Windows
    }
    cout << totalGallons << " gallons pumped..." << endl;
}

void printReceipt(char octane, double price, double gallons){
    //#TODO finish this method
}

int main() {

    double highOctaneLevels = -1;
    double mediumOctaneLevels;
    double lowOctaneLevels;

    double highOctanePrice;
    double mediumOctanePrice;
    double lowOctanePrice;

    double highOctanePriceRetail;
    double mediumOctanePriceRetail;
    double lowOctanePriceRetail;

    bool rewardsMember = false;
    double rewardsDiscount = 0;

    char octaneToPump;
    double selectedOctaneLevels;
    double gallonsToPump;

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
    } else {
        cout << "Unable to read input file." << endl;
        // replaces system("pause") since this is Windows specific
        cin.ignore();
        cin.get();
        return 0;
    }
    // print gas levels and price
    cout << setw(15) << left << "Tank Readings:";
    cout << setw(5) << right << "Hi=" << fixed << setprecision(2) << setw(6) << right << highOctaneLevels;
    cout << setw(6) << right << "Med=" << fixed << setprecision(2) << setw(6) << right << mediumOctaneLevels;
    cout << setw(6) << right << "Low=" << fixed << setprecision(2) << setw(6) << right << lowOctaneLevels << endl;

    cout << setw(15) << left << "Today's PPG:";
    cout << setw(6) << right << "Hi=$" << fixed << setprecision(2) << setw(5) << right << highOctanePrice;
    cout << setw(7) << right << "Med=$" << fixed << setprecision(2) << setw(5) << right << mediumOctanePrice;
    cout << setw(7) << right << "Low=$" << fixed << setprecision(2) << setw(5) << right << lowOctanePrice << endl;

    // print logo
    cout << endl << " ------ Cole Gerdemann's Gas -----" << endl;

    // find out if customer is a rewards member
    bool inputValid = false;
    do {
        cout << setw(35) << left << "Are you a rewards customer? (Y/N): ";
        string input;
        cin >> input;

        if (input.length() == 1 && tolower(input[0]) == 'y'){
            rewardsMember = true;            cout << setw(20) << left << "High Octance: " << "$" << highOctanePrice - rewardsDiscount << endl;
            cout << setw(20) << left << "Medium Octane: " << "$" << mediumOctanePrice - rewardsDiscount << endl;
            cout << setw(20) << left << "Low Octance: " << "$" << lowOctanePrice - rewardsDiscount << endl;
            inputValid = true;
        } else if (input.length() == 1 && tolower(input[0]) == 'n'){
            inputValid = true;
        } else {
            cout << "Please enter Y or N" << endl;
        }
    } while (!inputValid);

    // get rewards number and calculate discount
    if (rewardsMember){
        cout << setw(35) << left << "Enter customer rewards number: ";
        int input;
        cin >> input;
        rewardsDiscount = ((input % 10) + 1) / 100.0;
        cout << setw(35) << left << "Price Per Gallon Discount: " << "$" << rewardsDiscount << endl;

        highOctanePriceRetail = highOctanePrice - rewardsDiscount;
        mediumOctanePriceRetail = mediumOctanePrice - rewardsDiscount;
        lowOctanePriceRetail = lowOctanePrice - rewardsDiscount;
    } else {
        highOctanePriceRetail = highOctanePrice;
        mediumOctanePriceRetail = mediumOctanePrice;
        lowOctanePriceRetail = lowOctanePrice;
    }

    // print gas prices
    cout << endl << "Prices per Gallon:" << endl;
    cout << setw(20) << left << "High Octance: " << "$" << highOctanePriceRetail << endl;
    cout << setw(20) << left << "Medium Octane: " << "$" << mediumOctanePriceRetail << endl;
    cout << setw(20) << left << "Low Octance: " << "$" << lowOctanePriceRetail<< endl;

    // select an octane level
    inputValid = false;
    do {
        string input;
        cout << "Select octane (H/M/L): ";
        cin >> input;
        if (input.length() == 1 && (tolower(input[0]) == 'h' || tolower(input[0]) == 'm' || tolower(input[0]) == 'l')){
            octaneToPump = tolower(input[0]);
            inputValid = true;
        }
    } while (!inputValid);

    // get number of gallons to pump
    switch (octaneToPump){
        case 'l':
            selectedOctaneLevels = lowOctaneLevels;
            break;
        case 'm':
            selectedOctaneLevels = mediumOctaneLevels;
            break;
        case 'h':
            selectedOctaneLevels = highOctaneLevels;
    }
    cout << endl << "Enter number of gallons (-1 to fill it up): ";
    cin >> gallonsToPump;
    if (gallonsToPump == -1){
        gallonsToPump = (rand() % 7) + 1; //#TODO figure out why this always gives 2 gallons
        cout << "Sensor reports " << gallonsToPump << " gallons needed to fill up.";
    }
    if (gallonsToPump > selectedOctaneLevels){
        cout << "Sorry, our tank is nearly empty. We only have " << selectedOctaneLevels << " gallons available." << endl;
        gallonsToPump = selectedOctaneLevels;
    }
    pumpGas(gallonsToPump);


    

    // replaces system("pause") since this is Windows specific
    cin.ignore();
    cin.get();

    return 0;
}

