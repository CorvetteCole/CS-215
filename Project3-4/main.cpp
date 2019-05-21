#include <iostream>
#include <string>
#include <Windows.h>
#include "league.h"

using namespace std;

void doAbort(string error){
    cout << error << endl;
    system("pause");
    exit(1);
}

int main() {
    league newLeague{};
    newLeague.go();
    return 0;
}