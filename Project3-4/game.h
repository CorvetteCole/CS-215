//
// Created by cole on 5/1/2019.
//
#include <string>
#include "team.h"

using namespace std;

class game {
public:
    friend class gameList;
    game();
    void setData(string newDate, team * newTeam1, team * newTeam2, int newTeam1Points, int newTeam2Points);
    int getTeam1Points();
    int getTeam2Points();
    team * getTeam1();
    team * getTeam2();
    string getDate();


private:
    game * next;
    string date;
    team * team1;
    team * team2;
    int team2Points;
    int team1Points;

};
