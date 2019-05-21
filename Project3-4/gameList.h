//
// Created by cole on 5/1/2019.
//

#include "game.h"

using namespace std;

class gameList {
public:
    gameList();

    int getNumWins(team * teamWins);

    int getNumLosses(team * teamLosses);

    void printGames(team * teamPrint);

    void writeGames();

    void readGames(teamList newTeamList);

    void addGame(game newGame);

    int getNumGames();


private:
    game * head;
    game * tail;

};


