#include <utility>

//----------------------------------------------------------------------------
//                  CS 215 - Project 2 - MiniMud
//----------------------------------------------------------------------------
// Author:
// Date:
// Description:
// Assistance: I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.
// OR
// Assistance: I received help from the following:
//-----------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "gameutils.h"

using namespace std;


void printLogo(){
    cout << "-------------------------" << endl;
    cout << "    Project 2 Game       " << endl;
    cout << "    Cole Gerdemann       " << endl;
    cout << "-------------------------" << endl;
}

string getInputFileName(){
    string input;
    cout << "Enter name of game to play: ";
    cin >> input;
    return input + ".txt";
}

void initItems(item items[], int &numItems){
    for (int i = 0; i < MAX_ITEMS; i ++){
        items[i].shortDesc = "";
        items[i].longDesc = "";
        numItems = 0;
    }
}

void initRooms(room rooms[]){
    for (int i = 0; i < MAX_ROOMS; i ++) {
        rooms[i].shortDesc = "";
        rooms[i].longDesc = "";
        rooms[i].north = NO_EXIT;
        rooms[i].east = NO_EXIT;
        rooms[i].south = NO_EXIT;
        rooms[i].west = NO_EXIT;
        initItems(rooms[i].items, rooms[i].numItems);
    }
}

void initWinData(winDataStruct &winDataStructInit){
    winDataStructInit.winMessage = "";
    winDataStructInit.winRoom = NO_EXIT;
    initItems(winDataStructInit.winItem, winDataStructInit.numWinItems);
}

item removeItem(int removeIndex, item itemList[], int &numItems){
    if (removeIndex + 1 > numItems || removeIndex < 0){
        gameAbort("removeItem: invalid index = " + to_string(removeIndex));
    }
    item removedItem = itemList[removeIndex];
    for (int i = removeIndex; i + 1 < MAX_ITEMS; i++){
        itemList[i] = itemList[i + 1];
    }
    numItems -= 1;
    return removedItem;
}

void addItem(item newItem, item items[], int &numItems){
    if (numItems + 1 <= MAX_ITEMS){
        items[numItems] = newItem;
        numItems++;
    } else {
        gameAbort("addItem: maximum number of items exceeded!");
    }
}

void addItem(string shortDesc, string longDesc, item items[], int &numItems){
    item newItem = item{};
    newItem.shortDesc = shortDesc;
    newItem.longDesc = longDesc;
    addItem(newItem, items, numItems);
}


//----------------------------------------------------------------------------
//							loadData
//----------------------------------------------------------------------------
void loadData(room rooms[], int & numRooms, winDataStruct & winData) {
    // variable declarations
    ifstream f;				// input file handle
    string tag;				// first word extracted from each line
    string filename;		// name of input file
    string data;			// data read from file using cleanGetline()
    int roomNdx = -1;		// index of the "current room" being read/populated
    // this should always be rumRooms-1

    // initialize the rooms and winData
    initRooms(rooms);
    initWinData(winData);

    // get input file name and open the input file; abort on failure
    filename = getInputFileName();
    f.open(filename);
    if (!f.is_open()){
        gameAbort("Unable to open " + filename);
    }

    // read line-by-line and store data in the game data structures
    f >> tag;

    while (tag != "END:") {
        if (tag == "ROOM:") {
            numRooms++;		// starting a new room
            roomNdx++;		// increment every time numRooms is incremented
            cleanGetline(f, rooms[roomNdx].shortDesc); // short desc on remainder of ROOM: line
            cleanGetline(f, rooms[roomNdx].longDesc);  // long desc on next line by itself (no tag)
        } else if (tag == "ITEM:") {
            string shortDesc, longDesc;
            cleanGetline(f, shortDesc);
            cleanGetline(f, longDesc);
            addItem(shortDesc, longDesc, rooms[roomNdx].items, rooms[roomNdx].numItems);
        } else if (tag == "WIN_ITEM:") {
            cleanGetline(f, data);
            addItem(data, "", winData.winItem, winData.numWinItems);
        } else if (tag == "NORTH:") {
            f >> rooms[roomNdx].north;
        } else if (tag == "SOUTH:") {
            f >> rooms[roomNdx].south;
        } else if (tag == "EAST:") {
            f >> rooms[roomNdx].east;
        } else if (tag == "WEST:") {
            f >> rooms[roomNdx].west;
        } else if (tag == "WIN_ROOM:") {
            f >> winData.winRoom;
        } else if (tag == "REMARK:") {
            cleanGetline(f, data);        // data is junk, throw it away
        } else if (tag == "WIN_TEXT:") {
            cleanGetline(f, winData.winMessage);
        } else if (tag == "END:"){
        } else {
            gameAbort("Unknown tag in " + filename + ": " + tag);
        }
        // check for read failure and read the next tag
        if (f.fail())
            gameAbort("Failure while reading input file " + filename);
        f >> tag;
    }
} // loadData()

string getCmd(string &remainder){
    string input;
    cout << "===> ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, input);
    return split(input, remainder);
}

//----------------------------------------------------------------------------
//							makeExitList
//----------------------------------------------------------------------------
string makeExitList(room thisRoom) {
    string exitList = "You can go:";
    if (thisRoom.north != NO_EXIT) exitList += " north,";
    if (thisRoom.south != NO_EXIT) exitList += " south,";
    if (thisRoom.east != NO_EXIT) exitList += " east,";
    if (thisRoom.west != NO_EXIT) exitList += " west.";
    exitList[exitList.length() - 1] = '.'; // change last comma to a period
    return exitList;
} // makeExitList()

void doLook(room currentRoom, bool showShortDesc) {
    if (showShortDesc) {
        cout << currentRoom.shortDesc << endl;
    } else {
        cout << currentRoom.longDesc << endl;
    }

    if (currentRoom.numItems > 0) {
        cout << "You notice the following: ";
        for (int i = 0; i < currentRoom.numItems - 1; i++) {
            cout << currentRoom.items[i].shortDesc << ", ";
        }
        cout << currentRoom.items[currentRoom.numItems - 1].shortDesc << ".";
        cout << endl << makeExitList(currentRoom) << endl;
    }
}

void doLook(room currentRoom){
    doLook(currentRoom, false);
}

//----------------------------------------------------------------------------
//							doInventory
//----------------------------------------------------------------------------
// Given: the player's inventory (partial array of items)
// This is the game's response to the "inv"/"i" (inventory) command.
// Prints a message telling the player what he/she is holding.
//----------------------------------------------------------------------------
void doInventory(item item[], int numItems) {
    if (numItems == 0)
        cout << "You don't have anything.\n";
    else {
        cout << "You are holding: ";
        for (int i = 0; i < (numItems - 1); i++)		// for all but last item
            cout << item[i].shortDesc << ", ";			// print short desc with comma
        cout << item[numItems - 1].shortDesc << ".\n";  // for last item, use period and newline
    }
} // doInventory()

int findItem(string itemName, item items[], int numItems){
    for (int i = 0; i < numItems; i++){
        if (items[i].shortDesc == itemName){
            return i;
        }
    }
    return NOT_FOUND;
}

void doExamine(string itemName, item roomInventory[], int numRoomItems, item playerInventory[], int numPlayerItems){
    int foundIndex = findItem(itemName, roomInventory, numRoomItems);
    if (foundIndex == NOT_FOUND){
        foundIndex = findItem(itemName, playerInventory, numPlayerItems);
        if (foundIndex == NOT_FOUND){
            cout << "You see no " + itemName << endl;
        } else {
            cout << playerInventory[foundIndex].longDesc << endl;
        }
    } else {
        cout << roomInventory[foundIndex].longDesc << endl;
    }
}

void doTake(string itemName, item roomInventory[], int & numRoomItems, item playerInventory[], int & numPlayerItems){
    int itemIndex = findItem(itemName, roomInventory, numRoomItems);
    if (itemIndex == NOT_FOUND){
        itemIndex = findItem(itemName, playerInventory, numPlayerItems);
        if (itemIndex == NOT_FOUND){
            cout << "You see no " + itemName << endl;
        } else {
            cout << "You already have the " + itemName << endl;
        }
    } else {
        if (numPlayerItems < MAX_ITEMS){
            addItem(removeItem(itemIndex, roomInventory, numRoomItems), playerInventory, numPlayerItems);
        }
    }
}

void doDrop(string itemName, item roomInventory[], int & numRoomItems, item playerInventory[], int & numPlayerItems){
    int itemIndex = findItem(itemName, playerInventory, numPlayerItems);
    if (itemIndex == NOT_FOUND){
        itemIndex = findItem(itemName, roomInventory, numRoomItems);
        if (itemIndex == NOT_FOUND){
            cout << "You have no " + itemName << endl;
        } else {
            cout << "You don’t have the " + itemName << endl;
        }
    } else {
        if (numRoomItems < MAX_ITEMS){
            addItem(removeItem(itemIndex, playerInventory, numPlayerItems), roomInventory, numRoomItems);
        }
    }
}

bool gameWon(winDataStruct winData, room rooms[]){
    for (int j = 0; j < winData.numWinItems; j++){
        if (findItem(winData.winItem[j].shortDesc, rooms[winData.winRoom].items, rooms[winData.winRoom].numItems) == -1){
            return false;
        }
    }
    return true;
}



void startUp(room rooms[], int & numRooms, item inventory[], int & numInventoryItems, winDataStruct &winDataStructure){
    printLogo();
    loadData(rooms, numRooms, winDataStructure);
    initItems(inventory, numInventoryItems);
    cout << "You fall asleep and dream of a place far away..." << endl;
    doLook(rooms[START_ROOM]);
}

//----------------------------------------------------------------------------
//							goNorth
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "north"/"n" command.
// When the north exit exists, changes the current room index and performs
// a "look" command with a short room description
void goNorth(int & currentRoom, room rooms[]) {
    if (rooms[currentRoom].north == NO_EXIT)
        cout << "You can't go north.\n";
    else {
        currentRoom = rooms[currentRoom].north;
        doLook(rooms[currentRoom], true); // true = show short room desc.
    }
} // goNorth()

//----------------------------------------------------------------------------
//							goEast
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "east"/"n" command.
// When the east exit exists, changes the current room index and performs
// a "look" command with a short room description
void goEast(int & currentRoom, room rooms[]) {
    if (rooms[currentRoom].east == NO_EXIT)
        cout << "You can't go east.\n";
    else {
        currentRoom = rooms[currentRoom].east;
        doLook(rooms[currentRoom], true); // true = show short room desc.
    }
} // goEast()

//----------------------------------------------------------------------------
//							goSouth
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "south"/"n" command.
// When the south exit exists, changes the current room index and performs
// a "look" command with a short room description
void goSouth(int & currentRoom, room rooms[]) {
    if (rooms[currentRoom].south == NO_EXIT)
        cout << "You can't go south.\n";
    else {
        currentRoom = rooms[currentRoom].south;
        doLook(rooms[currentRoom], true); // true = show short room desc.
    }
} // goSouth()

//----------------------------------------------------------------------------
//							goWest
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the west"/"n" command.
// When the west exit exists, changes the current room index and performs
// a "look" command with a short room description
void goWest(int & currentRoom, room rooms[]) {
    if (rooms[currentRoom].west == NO_EXIT)
        cout << "You can't go west.\n";
    else {
        currentRoom = rooms[currentRoom].west;
        doLook(rooms[currentRoom], true); // true = show short room desc.
    }
} // goWest()

//----------------------------------------------------------------------------
//							main
//----------------------------------------------------------------------------
int main() {
    // declare data structures
    room rooms[MAX_ROOMS] = {};
    int numRooms = 0;
    item inventory[MAX_ITEMS] = {};
    int numInventoryItems = 0;
    int currentRoom = START_ROOM;
    winDataStruct winData = {};


    // declare other variables
    string cmd;					// command entered by user (first word of input)
    string remainder;			// remainder of command entered by user
    bool   gameWasWon = false;	// check with gameWon() as needed

    // start up: load game data from file and initialize player inventory
    startUp(rooms, numRooms, inventory, numInventoryItems, winData);

    // get first command input
    cmd = getCmd(remainder);


    // repeat until "exit" entered or the game is won
    while (cmd != "exit" && !gameWasWon) {
        if (cmd == "help") {
            printHelp();
        } else if (cmd == "look" || cmd == "l"){
            doLook(rooms[currentRoom]);
        } else if (cmd == "inv" || cmd == "i"){
            doInventory(inventory, numInventoryItems);
        } else if (cmd =="exa" || cmd == "x"){
            doExamine(remainder, rooms[currentRoom].items, rooms[currentRoom].numItems, inventory, numInventoryItems);
        } else if (cmd == "take" || cmd == "t"){
            doTake(remainder, rooms[currentRoom].items, rooms[currentRoom].numItems, inventory, numInventoryItems);
        } else if (cmd == "drop" || cmd == "d"){
            doDrop(remainder, rooms[currentRoom].items, rooms[currentRoom].numItems, inventory, numInventoryItems);
        } else if (cmd == "north" || cmd == "n"){
            goNorth(currentRoom, rooms);
        } else if (cmd == "east" || cmd == "e"){
            goEast(currentRoom, rooms);
        } else if (cmd == "south" || cmd == "s"){
            goSouth(currentRoom, rooms);
        } else if (cmd == "west" || cmd == "w"){
            goWest(currentRoom, rooms);
        } else { // the user entered an unrecognized command
            cout << "What??\n";
        }
        gameWasWon = gameWon(winData, rooms);
        // check if game was won and print win message or get next user input
        if (gameWasWon) {
            cout << winData.winMessage << endl;
        } else {
            cmd = getCmd(remainder);
        }
    }

    system("pause");
    return 0;
}