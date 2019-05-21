//
// Created by cole on 5/1/2019.
//

#include "team.h"


void team::setTeamID(string newTeamID) {
    teamID = newTeamID;
}

string team::getTeamId() {
    return teamID;
}

void team::setName(string newName) {
    name = newName;
}

string team::getName() {
    return name;
}

void team::setCoach(string newCoach) {
    coach = newCoach;
}

string team::getCoach() {
    return coach;
}

team::team() {
    teamID = "";
    name  = "";
    coach = "";
    next = nullptr;
}
