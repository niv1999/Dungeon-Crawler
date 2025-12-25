// Matan Shtar 324125350
// Niv Shteingart 314830365

#include "dungeon.hpp"
#include "utils.hpp"
#include <string>
using namespace std;

// Ctor
Dungeon::Dungeon() : characters{},
                     characterCount(0),
                     monsters{},
                     monsterCount(0),
                     rooms{},
                     roomsCount(0),
                     startRoom(nullptr)
{
}

// Dtor
Dungeon::~Dungeon()
{
    for (int i = 0; i < characterCount; i++)
        delete characters[i];
    for (int i = 0; i < monsterCount; i++)
        delete monsters[i];
    for (int i = 0; i < roomsCount; i++)
        delete rooms[i];
}

// Add a character to the characters database
void Dungeon::addNewCharacter(Character* newCharacter) 
{
    if(newCharacter != nullptr)
    {
        characters[characterCount] = newCharacter;
        characterCount++;
    }
}

// Add a room to the rooms database
void Dungeon::addNewRoom(Room* newRoom) 
{
    if(newRoom != nullptr)
    {
        rooms[roomsCount] = newRoom;
        roomsCount++;
    }
}

// Add a monster to the monsters database
void Dungeon::addNewMonster(Monster* newMonster) 
{
    if(newMonster != nullptr)
    {
        monsters[monsterCount] = newMonster;
        monsterCount++;
    }
}

// Find a character in the characters database
Character* Dungeon::findCharacter(const string &name)
{
    for (int i = 0; i < characterCount; i++)
    {
        if (Utils::toLowerCase(name) == Utils::toLowerCase(characters[i]->getName()))
            return characters[i];
    }
    return nullptr;
}

// Find a room in the rooms database
Room* Dungeon::findRoom(const string &name)
{
    for (int i = 0; i < roomsCount; i++)
    {
        if (Utils::toLowerCase(name) == Utils::toLowerCase(rooms[i]->getName()))
            return rooms[i];
    }
    return nullptr;
}

// Find a monster in the monsters database
Monster* Dungeon::findMonster(const string &name)
{
    for (int i = 0; i < monsterCount; i++)
    {
        if (Utils::toLowerCase(name) == Utils::toLowerCase(monsters[i]->getName()))
            return monsters[i];
    }
    return nullptr;
}

// Remove a character from the characters database
void Dungeon::removeCharacter(Character* character)
{
    for(int i = 0; i < characterCount; i++)
    {
        if(characters[i] == character) {
            characters[i] = characters[characterCount-1];
            characters[characterCount-1] = nullptr;
            characterCount--;
            return;
        }
    }
}

// Remove a monster from the monsters database
void Dungeon::removeMonster(Monster* monster)
{
    for(int i = 0; i < monsterCount; i++)
    {
        if(monsters[i] == monster) {
            monsters[i] = monsters[monsterCount-1];
            monsters[monsterCount-1] = nullptr;
            monsterCount--;
            return;
        }
    }
}

// Create a "game state" message with all the players alive and their stats
string Dungeon::gameState() const
{
    string msg = "\n==========================================\n";
    msg +=       "         📜  DUNGEON CHRONICLE  📜        \n";
    msg +=       "==========================================\n";

    if(characterCount == 0)
        return msg + "   ☠️  All heroes have fallen.\n";

    for(int i = 0; i < characterCount; i++)
    {
        Character* c = characters[i];
        // Matches your character sheet style
        msg += "\n   HERO: " + c->getName() + "  [" + c->getClass() + "]\n";
        msg += "   ❤️  HP:  " + std::to_string(c->getHealth()) + "\n";
        // Only show inventory count here to keep it brief, or full stats if you prefer
    }
    msg += "==========================================\n";
    return msg;
}

// Set a start room
void Dungeon::setStartRoom(Room* room)
{
    if(room != nullptr)
        this->startRoom = room;
}

// Getters -
Room* Dungeon::getStartRoom() const
{
    return this->startRoom;
}

int Dungeon::getCharacterCount() const
{
    return this->characterCount;
}

int Dungeon::getMonsterCount() const
{
    return this->monsterCount;
}

int Dungeon::getRoomCount() const
{
    return this->roomsCount;
}