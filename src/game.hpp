// Matan Shtar 324125350
// Niv Shteingart 314830365

#pragma once
#include <string>
#include "dungeon.hpp"

class Game
{
private:
    Dungeon dungeon;
    Command *commands;
    int cmdCount;
    int cmdCapacity;
    std::string *gameMessages;
    int msgCount;
    int msgCapacity;

    std::string executeCreateCharacter(const Command &cmd);
    std::string executeCreateRoom(const Command &cmd);
    std::string executeSetStartRoom(const Command &cmd);
    std::string executeConnectRoom(const Command &cmd);
    std::string executePlaceItem(const Command &cmd);
    std::string executePlaceMonster(const Command &cmd);
    std::string executeEnterDungeon(const Command &cmd);
    std::string executeMove(const Command &cmd);
    std::string executeFight(const Command &cmd);
    std::string executePickUp(const Command &cmd);
    void setMessage(const std::string &message);
public:
    Game();
    ~Game();
    void loadFromFile(const std::string &filename);
    void executeCommands();
    void outputFinalState(const std::string &filename);
};