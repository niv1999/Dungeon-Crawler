// Matan Shtar 324125350
// Niv Shteingart 314830365

#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Ctor
Game::Game() : 
dungeon(),              
commands(nullptr),              
cmdCount(0),             
cmdCapacity(0),             
gameMessages(nullptr),              
msgCount(0),              
msgCapacity(0)
{
}

// Dtor
Game::~Game()
{
    delete[] commands;
    delete[] gameMessages;
}

// Load commands from file - skip empty lines, comment lines, and unknown commands
void Game::loadFromFile(const string &filename)
{
    // Open the file
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "CRITICAL ERROR opening file: " << filename << ". Exiting" << endl;
        return;
    }

    string line;
    int lineCounter = 1;
    while (getline(file, line))
    {
        // Skip empty and comment lines
        if (line.length() < 2 || line.substr(0, 2) == "//")
        {
            lineCounter++;
            continue;
        }

        // Parsing each word in line to an array
        Command cmd;
        stringstream ss(line);
        string tempWord;
        int wordCount = 0;
        while(wordCount < MAX_WORDS_PER_LINE && ss >> tempWord)
        {
            if(tempWord == "//")
                break;
            
            cmd.words[wordCount] = tempWord;
            wordCount++;
        }

        // Validate minimal word count
        if(wordCount < 3)
        {
            setMessage("Commands must have at least 3 words - SKIPPING line " + to_string(lineCounter));
            lineCounter++;
            continue;
        }
    
        // Validate command type
        cmd.type = Utils::extractCommandType(cmd.words);
        if (cmd.type == CommandType::UNKNOWN)
        {
            setMessage("Unknown command in line " + to_string(lineCounter) + " - SKIPPING");
            lineCounter++;
            continue;
        }

        // Check we have enough capacity for the new command
        if (cmdCount >= cmdCapacity)
        {
            Utils::resizeArray(commands, cmdCapacity, cmdCount);
        }

        // Append command to the commands array
        cmd.totalWords = wordCount;
        cmd.lineNumber = lineCounter;
        commands[cmdCount++] = cmd;
        lineCounter++;
    }

    setMessage(to_string(cmdCount) + " commands were loaded successfully");
    file.close();
}

// Execute all game commands
void Game::executeCommands()
{
    for (int i = 0; i < cmdCount; i++)
    {
        Command currCmd = commands[i];
        switch (currCmd.type)
        {
        case CommandType::CREATE_CHARACTER:
            setMessage(executeCreateCharacter(currCmd));
            break;
        case CommandType::CREATE_ROOM:
            setMessage(executeCreateRoom(currCmd));
            break;
        case CommandType::SET_START_ROOM:
            setMessage(executeSetStartRoom(currCmd));
            break;
        case CommandType::CONNECT:
            setMessage(executeConnectRoom(currCmd));
            break;
        case CommandType::PLACE_ITEM:
            setMessage(executePlaceItem(currCmd));
            break;
        case CommandType::PLACE_MONSTER:
            setMessage(executePlaceMonster(currCmd));
            break;
        case CommandType::ENTER_DUNGEON:
            setMessage(executeEnterDungeon(currCmd));
            break;
        case CommandType::MOVE:
            setMessage(executeMove(currCmd));
            break;
        case CommandType::FIGHT:
            setMessage(executeFight(currCmd));
            break;
        case CommandType::PICK_UP:
            setMessage(executePickUp(currCmd));
            break;
        }
    }
    setMessage(dungeon.gameState());
}

// Sets a message to the messages array, later to be outputted in the output file
void Game::setMessage(const string &message)
{
    // Check we have enough capacity for the new message
    if (msgCount >= msgCapacity)
    {
        Utils::resizeArray(gameMessages, msgCapacity, msgCount);
    }
    gameMessages[msgCount++] = message;
}

// Output all the game messages into an output file
void Game::outputFinalState(const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (int i = 0; i < msgCount; i++)
    {
        file << gameMessages[i] << endl;
    }

    file.close();
}