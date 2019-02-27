//--------------------------------------------------------------------
// CS215-005 LAB 6
//--------------------------------------------------------------------
// Author: Cole Gerdemann
// Date: February 27th 2019
// Description: Program that analyzes the daily prices of a corporate
// stock.
//--------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>

using namespace std;

// there are no limitations on these settings, program can handle almost anything
const int timeStart = 800;      // 24 hour time of 8am
const int timeIncrement = 60;  // default 1 hour between prices recorded
const int numDataPoints = 10;   // number of stock price data points

string get12HourTime(int time){
    string formattedTime;
    int hour;
    int minute;
    while (time >= 1300){
        time -= 1200;
    }
    hour = time / 100;
    minute = (int)(round(((time / 100.0) - hour) * 100));
    string minuteString = to_string(minute);
    if (minuteString.size() == 1){
        minuteString += "0";
    }
    return to_string(hour) + ":" + minuteString;
}
// robust time incrementing solution allowing for any timeIncrement value
void incrementTime(int &time){
    if (timeIncrement >= 60){
        time += (timeIncrement / 60) * 100;
        time += timeIncrement - (timeIncrement / 60) * 60;
    } else {
        time += timeIncrement;
    }

    int hour = time / 100;
    int minute = (int)(round(((time / 100.0) - hour) * 100));
    if (minute >= 60){
        time -= 60;  // subtract the 60 minutes
        time += 100; // add one hour
    }

    if (time >= 2500){
        time -= 2400;
    }
}

void printStockInfo(const string &ticker, const string &date, array<double, numDataPoints> price){
    int time = timeStart;
    double change;
    double high = DBL_MIN;
    double low = DBL_MAX;
    double average;
    double total = 0;
    double median;

    cout << "STOCK: " << setw(6) << left << ticker;
    cout << "DATE: " << setw(10) << left << date << endl;
    cout << setw(12) << left << "TIME";
    cout << setw(15) << left << "PRICE" << endl;

    // print prices with time and also do stuff needed for future calculations
    for (double i : price){
        cout << setw(5) << right << get12HourTime(time);
        cout << "       $" << setw(6) << right << fixed << setprecision(2) << i << endl;
        incrementTime(time);
        if (i > high){
            high = i;
        } else if (i < low){
            low = i;
        }
        total += i;
    }

    // calculate statistics of stock
    change = price[numDataPoints -1] - price[0];
    average = total / numDataPoints;
    sort(price.begin(), price.end()); // why reinvent the wheel?
    median = numDataPoints % 2 == 0 ? (price[(numDataPoints / 2) - 1] + price[(numDataPoints / 2)]) / 2.0
                                    : price[round(numDataPoints / 2)];

    // display stock statistics
    cout << endl << setw(12) << left << "CHANGE:" << "$" << fixed << setprecision(2) << setw(6) << right << change << endl;
    cout << setw(12) << left << "HIGH:" << "$" << fixed << setprecision(2) << setw(6) << right << high << endl;
    cout << setw(12) << left << "LOW:" << "$" << fixed << setprecision(2) << setw(6) << right << low << endl;
    cout << setw(12) << left << "AVERAGE:" << "$" << fixed << setprecision(2) << setw(6) << right << average << endl;
    cout << setw(12) << left << "MEDIAN:" << "$" << fixed << setprecision(2) << setw(6) << right << median << endl;


}

int main() {
    string inputFileName;
    cout << "Enter stock data file name: ";
    cin >> inputFileName;

    ifstream stockDataFile(inputFileName);

    if (stockDataFile.is_open()){
        string stockTicker;
        string stockDate;
        array<double, numDataPoints> stockPrice{};

        stockDataFile >> stockTicker;
        stockDataFile >> stockDate;

        for (double &i : stockPrice) {
            stockDataFile >> i;
        }

        printStockInfo(stockTicker, stockDate, stockPrice);
    } else {
        cout << "Failed to open file " << inputFileName << endl;
    }

    cin.get();
    cin.ignore();
    return 0;
}
