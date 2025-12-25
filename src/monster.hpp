#pragma once
#include <string>
#include "constants.hpp"
class Character;

class Monster {
private:
    std::string name;
    int health;
    int strength;
    int defense;
    std::string combatRoundMsg;
public:
    Monster(const std::string& name, int health, int strength, int defense);
    void attack(Character& target);
    void defend(int damage);
    bool isDefeated() const;
    std::string getPrettyStats() const;
    std::string getCombatRoundMsg() const;
    std::string getName() const;
    int getHealth() const;
};