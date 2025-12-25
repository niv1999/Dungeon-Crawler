#include "item.hpp"
#include <string>
using namespace std;

// Ctor
Item::Item(const string &name, int hBonus, int sBonus, int dBonus) : name(name),
                                                                     healthBonus(hBonus),
                                                                     strengthBonus(sBonus),
                                                                     defenseBonus(dBonus)
{}

// Dtor
Item::~Item() {}

// Getters-
string Item::getName() const
{
    return this->name;
}

int Item::getHealthBonus() const
{
    return this->healthBonus;
}

int Item::getStrengthBonus() const
{
    return this->strengthBonus;
}

int Item::getDefenseBonus() const
{
    return this->defenseBonus;
}

string Item::getPrettyStats() const
{
    string msg = "[";
    bool first = true;

    if (this->healthBonus > 0) {
        msg += " +" + to_string(this->healthBonus) + " HP";
        first = false;
    }
    if (this->strengthBonus > 0) {
        if (!first) msg += " |";
        msg += " +" + to_string(this->strengthBonus) + " STR";
        first = false;
    }
    if (this->defenseBonus > 0) {
        if (!first) msg += " |";
        msg += " +" + to_string(this->defenseBonus) + " DEF";
    }

    if (msg == "[") msg += " No Stats ";
    msg += " ]";
    
    return msg;
}