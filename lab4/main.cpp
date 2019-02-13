//--------------------------------------------------------------------
// CS215-005 Lab 4
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: February 13th 2019
// Description: a program that reads data from the input file and writes
// a report to a file called “tempsout.txt”
// --------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {

    ifstream dataInput("tempsin.txt");

    if (dataInput.is_open()) {

        // creates tempsout file and prints header
        ofstream dataOutput("tempsout.txt");
        dataOutput << setw(15) << left << "DATE";
        dataOutput << setw(6) << left << "HIGH";
        dataOutput << setw(6) << left << "LOW" << endl;
        dataOutput << "------------------------" << endl;

        string input;
        dataInput >> input;

        int minTemp;
        int maxTemp;

        // reads input while the endofdata hasn't been reached
        while (input != "ENDOFDATA"){
            int numDays;
            dataInput >> numDays;

            minTemp = 2147483647;
            maxTemp = -2147483647;

            // find min and max temps
            for (int i = 0; i < numDays; i++){
                int temp;
                dataInput >> temp;
                if (temp > maxTemp){
                    maxTemp = temp;
                } else if (temp < minTemp){
                    minTemp = temp;
                }
            }

            // output temps and date
            dataOutput << setw(15) << left << input;
            dataOutput << setw(6) << left << maxTemp;
            dataOutput << setw(6) << left << minTemp << endl;

            // get next input for loop
            dataInput >> input;
        }

        // close files
        dataOutput.close();
        dataInput.close();
    } else {
        cout << "Error: file not opened" << endl;

        // universal pause
        cin.get();
        cin.ignore();

    }



    return 0;
}