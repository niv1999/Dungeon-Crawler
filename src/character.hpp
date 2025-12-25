// Matan Shtar 324125350
// Niv Shteingart 314830365

#pragma once
#include <string>
#include "item.hpp"
#include "room.hpp"
#include "constants.hpp"
class Monster;

class Character {
private:
    std::string name;
    int health;
    int strength;
    int defense;
    Item* inventory[MAX_COMPATIBLE_ITEMS];
    int inventoryCount;
    Room* currentRoom;
    std::string itemActionMsg;
    std::string combatRoundMsg;
public:
    Character(const std::string& name, int health, int strength, int defense);
    virtual ~Character();
    void attack(Monster& target);
    void defend(int damage);
    bool isAlive() const;
    Character& operator+=(const Item& item);
    void setCurrentRoom(Room* room);
    std::string getPrettyStats() const;
    std::string getName() const;
    int getHealth() const;
    Room* getCurrentRoom() const;
    std::string getItemActionMsg() const;
    std::string getCombatRoundMsg() const;
    virtual std::string getClass() const = 0;
    virtual bool isItemCompatible(Item* item) const = 0;
};