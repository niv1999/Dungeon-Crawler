// Matan Shtar 324125350
// Niv Shteingart 314830365

#include "room.hpp"
#include "monster.hpp"
#include <string>
using namespace std;

// Ctor
Room::Room(const string& name) : name(name),
                                 item(nullptr),
                                 monster(nullptr),
                                 north(nullptr),
                                 south(nullptr),
                                 east(nullptr),
                                 west(nullptr)
{
}

// Dtor
Room::~Room()
{
    if(this->item != nullptr) {
        delete this->item;
        this->item = nullptr;
    }
}

// Connect this room northern path
void Room::connectNorth(Room* room)
{
    this->north = room;
    room->south = this;
}

// Connect this room southern path
void Room::connectSouth(Room* room)
{
    this->south = room;
    room->north = this;
}

// Connect this room eastern path
void Room::connectEast(Room* room)
{
    this->east = room;
    room->west = this;
}

// Connect this room western path
void Room::connectWest(Room* room)
{
    this->west = room;
    room->east = this;
}

// Check if another room is already linked to this room
bool Room::isLinked() const
{
    return this->north != nullptr || 
           this->south != nullptr || 
           this->east != nullptr || 
           this->west != nullptr;
}

// Setters -
void Room::setItem(Item* item)
{
    this->item = item;
}

void Room::setMonster(Monster* monster)
{
    this->monster = monster;
}

// Getters -
Item* Room::getItem() const
{
    return this->item;
}

Monster* Room::getMonster() const
{
    return this->monster;
}

string Room::getName() const
{
    return this->name;
}

string Room::getDescription() const
{
    string desc = "\n   📍 [LOCATION] You are currently in '" + this->name + "'.\n";

    // 1. Check for Monsters
    if (this->monster != nullptr) {
        desc += "      👹 [DANGER] A " + this->monster->getName() +" is guarding this room!\n";
    }

    // 2. Check for Items
    if (this->item != nullptr) {
        desc += "      ✨ [ITEM] You spot a " + this->item->getName() + " lying on the ground - " + this->item->getPrettyStats() + "\n";
    }

    // 3. List Connections (Exits)
    desc += "      🧭 [EXITS]:\n";
    bool hasExit = false;

    if (this->north != nullptr) {
        desc += "         ⬆️  North -> " + this->north->getName() + "\n";
        hasExit = true;
    }
    if (this->east != nullptr) {
        desc += "         ➡️  East  -> " + this->east->getName() + "\n";
        hasExit = true;
    }
    if (this->south != nullptr) {
        desc += "         ⬇️  South -> " + this->south->getName() + "\n";
        hasExit = true;
    }
    if (this->west != nullptr) {
        desc += "         ⬅️  West  -> " + this->west->getName() + "\n";
        hasExit = true;
    }

    if (!hasExit) {
        desc += "         🚫 None (Dead End)\n";
    }

    return desc;
}