//-----------------------------------------------------
//                        league class
//-----------------------------------------------------
// This is the main class for the league application
// A main program declares a league object and invokes
// the go() method
//-----------------------------------------------------
#pragma once
#include "teamList.h"
#include "gameList.h"
class league {
public:
    void go();							// main program
private:
    teamList teams;						// a list of teams in the league
    gameList games;						// a list of games in the league
    char getMenuOption();				// main menu: get the user's selection
    void addGame();						// ask user for new game data and add
    void queryTeam();					// look up a team and print its stats
    team * askTeamId(string prompt);	// ask for team ID; validate
};