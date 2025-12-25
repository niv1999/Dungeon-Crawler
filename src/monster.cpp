#include "monster.hpp"
#include "character.hpp"
#include <string>
using namespace std;

// Ctor
Monster::Monster(const string &name, int health, int strength, int defense) : name(name),
                                                                              health(health),
                                                                              strength(strength),
                                                                              defense(defense),
                                                                              combatRoundMsg("")
{
}

// Perform an attack on a character
void Monster::attack(Character& target)
{
    int targetInitialHp = target.getHealth();
    target.defend(this->strength);
    int dmgDealt = targetInitialHp - target.getHealth();
    
    // New Format: [ATTACK] Goblin hits Thorin for 5 damage! (Thorin HP: 95)
    string msg = "   ⚔️  [ATTACK] " + this->name + " strikes " + target.getName();
    msg += " for " + to_string(dmgDealt) + " damage! ";
    msg += "(" + target.getName() + " HP: " + to_string(target.getHealth()) + ")";
    
    this->combatRoundMsg = msg;
}

// Defend against an attack from a character
void Monster::defend(int damage)
{
    int totalDmg = damage - this->defense;
    int finalDmg = totalDmg > 1 ? totalDmg : 1;
    this->health -= finalDmg;
}

// Check if the monster is dead
bool Monster::isDefeated() const
{
    return (this->health <= 0);
}

// Getters-
string Monster::getPrettyStats() const
{
    string msg = "   👹 [ENEMY] " + this->name + "\n";
    msg += "   ❤️  HP: " + to_string(this->health);
    msg += "  |  💪 STR: " + to_string(this->strength);
    msg += "  |  🛡️  DEF: " + to_string(this->defense);
    
    return msg;
}

string Monster::getCombatRoundMsg() const
{
    return this->combatRoundMsg;
}

string Monster::getName() const
{
    return this->name;
}

int Monster::getHealth() const
{
    return this->health >= 0 ? this->health : 0;
}