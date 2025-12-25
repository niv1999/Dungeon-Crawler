#include "game.hpp"
#include <iostream>
using namespace std;

// In main.cpp
int main() {
    cerr << "DEBUG: Starting Program..." << endl; // Use cerr, not cout
    
    Game game;
    cerr << "DEBUG: Game Object Created." << endl;

    game.loadFromFile("input.txt");
    cerr << "DEBUG: Finished Loading." << endl; // If you don't see this, the crash is in loadFromFile

    game.executeCommands();
    cerr << "DEBUG: Finished Execution." << endl;

    game.outputFinalState("output.txt");
    cerr << "DEBUG: Saved File." << endl;

    return 0;
}