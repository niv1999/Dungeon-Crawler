#include "characterChildren.hpp"
#include <string>
using namespace std;

// Warrior.cpp
Warrior::Warrior(const string &name) : Character(name, 100, 15, 10) {}

bool Warrior::isItemCompatible(Item *item) const
{
    if (item->getCategory() == ItemCategory::POTION || item->getItemEnum() == ItemEnum::SWORD || item->getItemEnum() == ItemEnum::SHIELD)
        return true;
    return false;
}

string Warrior::getClass() const
{
    return "Warrior";
}

// Thief.cpp
Thief::Thief(const string &name) : Character(name, 60, 20, 7) {}

bool Thief::isItemCompatible(Item *item) const
{
    if (item->getCategory() == ItemCategory::POTION || item->getItemEnum() == ItemEnum::DAGGER)
        return true;
    return false;
}

string Thief::getClass() const
{
    return "Thief";
}

// Mage.cpp
Mage::Mage(const string &name) : Character(name, 40, 25, 5) {}

bool Mage::isItemCompatible(Item *item) const
{
    if (item->getCategory() == ItemCategory::POTION || item->getItemEnum() == ItemEnum::WAND)
        return true;
    return false;
}

string Mage::getClass() const
{
    return "Mage";
}