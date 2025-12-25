// Matan Shtar 324125350
// Niv Shteingart 314830365

#pragma once
#include <string>
#include "constants.hpp"

class Item {
private:
    std::string name;
    int healthBonus;
    int strengthBonus;
    int defenseBonus;
public:
    Item(const std::string& name, int hBonus, int sBonus, int dBonus);
    virtual ~Item();
    std::string getName() const;
    int getHealthBonus() const;
    int getStrengthBonus() const;
    int getDefenseBonus() const;
    std::string getPrettyStats() const;
    virtual ItemEnum getItemEnum() const = 0;
    virtual ItemCategory getCategory() const = 0;
};