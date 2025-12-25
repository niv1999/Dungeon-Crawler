#pragma once
#include <string>
#include "character.hpp"
#include "monster.hpp"
#include "room.hpp"
#include "constants.hpp"

class Dungeon {
private:
    Character* characters[MAX_CHARACTERS];
    int characterCount;
    Monster* monsters[MAX_MONSTERS];
    int monsterCount;
    Room* rooms[MAX_ROOMS];
    int roomsCount;
    Room* startRoom;
public:
    Dungeon();
    ~Dungeon();
    void addNewCharacter(Character* newCharacter);
    void addNewRoom(Room* newRoom);
    void addNewMonster(Monster* newMonster);
    Character* findCharacter(const std::string& name);
    Room* findRoom(const std::string& name);
    Monster* findMonster(const std::string& name);
    void removeCharacter(Character* character);
    void removeMonster(Monster* monster);
    std::string gameState() const;
    void setStartRoom(Room* room);
    Room* getStartRoom() const;
    int getCharacterCount() const;
    int getMonsterCount() const;
    int getRoomCount() const;
};