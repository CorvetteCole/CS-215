//
// Created by cole on 5/1/2019.
//

#include "teamList.h"
#include <fstream>
#include <iostream>
#include <iomanip>

teamList::teamList() {
    head = nullptr;
}

void teamList::addTeam(team newTeam) {
    team * x = new team;
    x -> teamID = newTeam.teamID;
    x -> name = newTeam.name;
    x -> coach = newTeam.coach;
    x -> next = head;
    head = x;
}

void teamList::readData() {
    ifstream file;
    file.open("teams.txt");
    while (!file.eof()){
        string tempID;
        string tempName;
        string tempCoach;
        getline(file, tempID);
        getline(file, tempName);
        getline(file, tempCoach);
        team tmp = {};
        tmp.teamID = tempID;
        tmp.name = tempName;
        tmp.coach = tempCoach;
        addTeam(tmp);
    }
}

void teamList::printTeams() {
    team * tmp = head;
    cout << endl;
    cout << "-------------------TEAMS (" << getNumTeams() << ")-------------------------" << endl;
    cout << setw(4) << left << "TID" << "  " << setw(25) << left <<  "TEAM" << "  " << setw(20) << left << "COACH" << endl;
    cout << setw(4) << left << "----" << "  " << setw(25) << left <<  "-------------------------" << "  " << setw(20) << left << "--------------------" << endl;
    for (;tmp; tmp = tmp -> next){
        cout << setw(4) << left << tmp->getTeamId() << "  " << setw(25) << left <<  tmp->getName() << "  " << setw(20) << left << tmp->getCoach() << endl;
    }
}

team *teamList::getTeamRef(string teamID) {
    team * desiredTeam = nullptr;
    team * tmp = head;
    for (;tmp; tmp = tmp -> next) {
        if (tmp ->teamID == teamID){
            desiredTeam = tmp;
        }
    }
    return desiredTeam;
}

int teamList::getNumTeams() {
    int numTeams = 0;
    team * tmp = head;
    for (;tmp; tmp = tmp -> next) {
        numTeams++;
    }
    return numTeams;
}
