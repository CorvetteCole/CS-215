//
// Created by cole on 5/1/2019.
//

#include "team.h"

using namespace std;


class teamList {
public:
    teamList();

    team * getTeamRef(string teamID);

    void printTeams();

    void readData();

    void addTeam(team newTeam);

    int getNumTeams();

private:
    team * head;
};



