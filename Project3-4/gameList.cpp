//
// Created by cole on 5/1/2019.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include "gameList.h"
#include "teamList.h"

extern void doAbort(string error);

gameList::gameList() {
    head = nullptr;
    tail = nullptr;
}

//    string date;
//    int team1Points;
//    int team2Points;
//    team * team1;
//    team * team2;
void gameList::addGame(game newGame) {
    game * x = new game;
    x -> date = newGame.date;
    x -> team1Points = newGame.team1Points;
    x -> team2Points = newGame.team2Points;
    x -> team1 = newGame.team1;
    x -> team2 = newGame.team2;
    x -> next = head;
    head = x;
}

void gameList::readGames(teamList newTeamList) {
    ifstream file;
    file.open("games.txt");
    if (!file.is_open()){
        doAbort("gameList::readGames: unable to open games.txt");
    }
    while (!file.eof()){
        string date;
        string team1ID;
        string team2ID;
        int team1Points = 0;
        int team2Points = 0;
        file >> date;
        file >> team1ID;
        file >> team1Points;
        file >> team2ID;
        file >> team2Points;

        game tmp = {};
        tmp.date = date;
        tmp.team1 = newTeamList.getTeamRef(team1ID);
        tmp.team2 = newTeamList.getTeamRef(team2ID);
        if (tmp.team1 == nullptr){
           doAbort("gameList::read: invalid team id 1/2 = " + team1ID);
        } else if (tmp.team2 == nullptr){
            doAbort("gameList::read: invalid team id 1/2 = " + team2ID);
        }
        tmp.team1Points = team1Points;
        tmp.team2Points = team2Points;
        addGame(tmp);
    }
}

int gameList::getNumGames() {
    int numGames = 0;
    game * tmp = head;
    for (;tmp; tmp = tmp -> next) {
        numGames++;
    }
    return numGames;
}

int gameList::getNumWins(team *teamWins) {
    int numWins = 0;
    game * tmp = head;
    for (; tmp; tmp = tmp->next) {
        if ((tmp->team1Points > tmp->team2Points && tmp->team1 == teamWins) ||
            (tmp->team2Points > tmp->team1Points && tmp->team2 == teamWins)) {
            numWins++;
        }
    }
    return numWins;
}

int gameList::getNumLosses(team *teamLosses) {
    int numLosses = 0;
    game * tmp = head;
    for (; tmp; tmp = tmp->next) {
        if ((tmp->team1Points > tmp->team2Points && tmp->team2 == teamLosses) ||
            (tmp->team2Points > tmp->team1Points && tmp->team1 == teamLosses)) {
            numLosses++;
        }
    }
    return numLosses;
}

void gameList::printGames(team *teamPrint) {
    game * tmp = head;
    cout << endl;
    cout << "---------GAMES (" << getNumGames() << ")------------" << endl;
    cout << setw(10) << left << "DATE" << "  " << setw(4) << left <<  "TEAM" << "  " << setw(3) << left << "SC" << "  " << setw(4) << left <<  "TEAM" << "  " << setw(3) << left << "SC" << endl;
    cout << setw(10) << left << "----------" << "  " << setw(4) << left <<  "----" << "  " << setw(3) << left << "---" << "  " << setw(4) << left <<  "----" << "  " << setw(3) << left << "---" << endl;
    for (;tmp; tmp = tmp -> next) {
        if (teamPrint == tmp->team1 || teamPrint == tmp->team2) {
            cout << setw(10) << left << tmp->date << "  " << setw(4) << left <<  tmp->team1->getTeamId() << "  " << setw(3) << left << tmp->team1Points << "  " << setw(4) << left <<  tmp->team2->getTeamId() << "  " << setw(3) << left << tmp->team2Points << endl;

        } else if (teamPrint == nullptr) {
            cout << setw(10) << left << tmp->date << "  " << setw(4) << left <<  tmp->team1->getTeamId() << "  " << setw(3) << left << tmp->team1Points << "  " << setw(4) << left <<  tmp->team2->getTeamId() << "  " << setw(3) << left << tmp->team2Points << endl;
        }
    }
}

void gameList::writeGames() {
    ofstream file;
    file.open("games2.txt");
    game * tmp = head;
    for (;tmp; tmp = tmp -> next) {
        file << setw(10) << left << tmp->date << " " << setw(4) << left <<  tmp->team1->getTeamId() << " " << setw(3) << left << tmp->team1Points << " " << setw(4) << left <<  tmp->team2->getTeamId() << " " << setw(3) << left << tmp->team2Points << endl;
    }
}
