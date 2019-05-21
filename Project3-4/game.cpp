//
// Created by cole on 5/1/2019.
//

#include "game.h"

void game::setData(string newDate, team *newTeam1, team *newTeam2, int newTeam1Points, int newTeam2Points) {
    date = newDate;
    team1 = newTeam1;
    team2 = newTeam2;
    team1Points = newTeam1Points;
    team2Points = newTeam2Points;
}

int game::getTeam1Points() {
    return team1Points;
}

int game::getTeam2Points() {
    return team2Points;
}

team *game::getTeam1() {
    return team1;
}

team *game::getTeam2() {
    return team2;
}

string game::getDate() {
    return date;
}

game::game() {
    date = "";
    team1Points = 0;
    team2Points = 0;
    team1 = nullptr;
    team2 = nullptr;
    next = nullptr;
}
