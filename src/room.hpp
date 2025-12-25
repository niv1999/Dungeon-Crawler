// Matan Shtar 324125350
// Niv Shteingart 314830365

#pragma once
#include <string>
#include "item.hpp"
#include "constants.hpp"
class Monster;


class Room {
private:
    std::string name;
    Item* item;
    Monster* monster;
public:
    Room* north;
    Room* south;
    Room* east;
    Room* west;
    Room(const std::string& name);
    ~Room();
    void connectNorth(Room* room);
    void connectSouth(Room* room);
    void connectEast(Room* room);       
    void connectWest(Room* room);
    bool isLinked() const;
    void setItem(Item* item);
    void setMonster(Monster* monster);
    Item* getItem() const;
    Monster* getMonster() const;
    std::string getName() const;
    std::string getDescription() const;
};