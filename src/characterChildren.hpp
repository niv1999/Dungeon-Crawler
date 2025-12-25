// Matan Shtar 324125350
// Niv Shteingart 314830365

#pragma once
#include "character.hpp"

class Warrior : public Character {
public:
    Warrior(const std::string &name);
    std::string getClass() const;
    bool isItemCompatible(Item* item) const;
};

class Thief : public Character {
public:
    Thief(const std::string &name);
    std::string getClass() const;
    bool isItemCompatible(Item* item) const;
};

class Mage : public Character {
public:
    Mage(const std::string &name);
    std::string getClass() const;
    bool isItemCompatible(Item* item) const;
};