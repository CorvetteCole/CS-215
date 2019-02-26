#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>


using namespace std;

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

void incrementTime(int &time){
    time += timeIncrement;
    int hour = time / 100;
    int minute = (int)(round(((time / 100.0) - hour) * 100));
    if (minute >= 60){
        time -= 60;  // subtract the 60 minutes
        time += 100; // add one hour
    }
}

// #TODO see if I can combine the incrementTime and get12HourTime functions in a readable way
void printStockInfo(const string &ticker, const string &date, array<double, numDataPoints> price){
    int time = timeStart;
    cout << "STOCK: " << setw(6) << left << ticker;
    cout << "DATE: " << setw(10) << left << date << endl;
    cout << setw(12) << left << "TIME";
    cout << setw(15) << left << "PRICE" << endl;

    for (double i : price){
        //cout << time << endl;
        cout << setw(5) << right << get12HourTime(time);
        cout << "       $" << setw(6) << right << fixed << setprecision(2) << i << endl;
        incrementTime(time);
    }




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
