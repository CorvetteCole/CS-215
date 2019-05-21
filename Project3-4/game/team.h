//
// Created by cole on 5/1/2019.
//
#ifndef PROJECT3_4_TEAM_H
#define PROJECT3_4_TEAM_H

#include <string>

using namespace std;

class team {
public:
    friend class teamList;
    team();

    string getName();

    string getCoach();

    string getTeamId();

    void setTeamID(string newTeamID);

    void setName(string newName);

    void setCoach(string newCoach);

private:
    string teamID;
    string name;
    string coach;
    team * next;
};

#endif