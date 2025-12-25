#include "character.hpp"
#include "monster.hpp"
#include <string>
using namespace std;

// Ctor
Character::Character(const std::string &name, int health, int strength, int defense) : name(name),
                                                                     health(health),
                                                                     strength(strength),
                                                                     defense(defense),
                                                                     inventory{},
                                                                     inventoryCount(0),
                                                                     currentRoom(nullptr),
                                                                     itemActionMsg(""),
                                                                     combatRoundMsg("")
{
}

// Dtor
Character::~Character()
{
    for(int i = 0; i < inventoryCount; i++)
    {
        delete inventory[i];
    }
}

// Attack a monster
void Character::attack(Monster& target)
{
    int targetInitialHp = target.getHealth();

    int totalDmg = this->strength;
    for(int i = 0; i < inventoryCount; i++) {
        totalDmg += inventory[i]->getStrengthBonus();
    }
    target.defend(totalDmg);

    int dmgDealt = targetInitialHp - target.getHealth();
    string msg = "   🗡️  [PLAYER] " + this->name + " attacks " + target.getName();
    msg += " >> Dealt " + to_string(dmgDealt) + " DMG ";
    msg += "(Enemy HP: " + to_string(target.getHealth()) + ")";

    this->combatRoundMsg = msg;
}

// Defend against an attack from a monster
void Character::defend(int damage)
{
    int totalDefense = this->defense;
    for(int i = 0; i < inventoryCount; i++) {
        totalDefense += inventory[i]->getDefenseBonus();
    }

    int finalDmg = damage - totalDefense > 1 ? damage - totalDefense : 1;
    this->health -= finalDmg;
}

// Check if character is still alive
bool Character::isAlive() const
{
    int totalHp = this->health;
    for(int i = 0; i < inventoryCount; i++) {
        totalHp += inventory[i]->getHealthBonus();
    }
    return totalHp >= 0;
}

// Pick up an item and equip or consume it
Character& Character::operator+=(const Item& item)
{
    // Consume a potion
    if(item.getCategory() == ItemCategory::POTION) 
    {
        this->health += item.getHealthBonus();
        this->strength += item.getStrengthBonus();
        this->defense += item.getDefenseBonus();
        this->currentRoom->setItem(nullptr);
        this->itemActionMsg = " 🧪 [CONSUME] " + this->name + " drank a " + item.getName() + ".\n" + this->getPrettyStats();
    }

    // Equip an item
    else if (item.getCategory() == ItemCategory::EQUIPMENT) 
    {
        bool inInventory = false;
        for(int i = 0; i < inventoryCount; i++) {
            Item* oldItem = inventory[i];
            if(oldItem->getItemEnum() == item.getItemEnum()) {
                inInventory = true;
                int oldItemStats = oldItem->getHealthBonus() + oldItem->getStrengthBonus() + oldItem->getDefenseBonus();
                int newItemStats = item.getHealthBonus() + item.getStrengthBonus() + item.getDefenseBonus();
                // Swap items if the one in the room is better
                if(newItemStats > oldItemStats) {
                    inventory[i] = this->currentRoom->getItem();
                    this->currentRoom->setItem(oldItem);
                    this->itemActionMsg = " ♻️ [SWAP] " + this->name + " discarded " + oldItem->getName() + " for the better " + item.getName() + ".\n" + item.getPrettyStats();
                }
                this->itemActionMsg = " ✋ [KEEP] " + this->name + " decided to keep their " + item.getName() + " (It was stronger).";
                break;
            }
        }

        if(!inInventory)
        {
            if (inventoryCount >= MAX_COMPATIBLE_ITEMS) {
                this->itemActionMsg = this->name + " cannot carry more items\n";
                return *this;
            }
            inventory[inventoryCount] = this->currentRoom->getItem();
            this->currentRoom->setItem(nullptr);
            inventoryCount++;
            this->itemActionMsg = " 🎒 [LOOT] " + this->name + " equipped the " + item.getName() + " - " + item.getPrettyStats();
        }   
    }

    return *this;
}

// Setters -
void Character::setCurrentRoom(Room* room)
{
    this->currentRoom = room;
}

// Getters -
string Character::getPrettyStats() const
{
    string line = "   ---------------------------------------\n";
    string msg = line + "   HERO: " + this->name + "  [" + this->getClass() + "]\n";
    msg += "   ❤️  HP:  " + to_string(this->health) + "\n";
    msg += "   💪  STR: " + to_string(this->strength) + "\n";
    msg += "   🛡️  DEF: " + to_string(this->defense) + "\n";
    
    if (inventoryCount > 0) {
        msg += "   🎒 INVENTORY:\n";
        for (int i = 0; i < inventoryCount; i++) {
            msg += "      • " + inventory[i]->getName() + " (" + inventory[i]->getPrettyStats() + ")\n";
        }
    } else {
        msg += "   🎒 INVENTORY: [Empty]\n";
    }
    msg += line;
    return msg;
}

string Character::getName() const
{
    return this->name;
}

int Character::getHealth() const
{
    return this->health;
}

Room* Character::getCurrentRoom() const
{
    return this->currentRoom;
}

string Character::getItemActionMsg() const
{
    return this->itemActionMsg;
}

string Character::getCombatRoundMsg() const
{
    return this->combatRoundMsg;
}