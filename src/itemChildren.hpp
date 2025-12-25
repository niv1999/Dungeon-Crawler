#pragma once
#include "item.hpp"

// sword.hpp
class Sword : public Item {
    public:
    Sword(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};


// dagger.hpp
class Dagger : public Item {
    public:
    Dagger(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};


// wand.hpp
class Wand : public Item {
    public:
    Wand(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};


// shield.hpp
class Shield : public Item {
    public:
    Shield(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};


// healthPotion.hpp
class HealthPotion : public Item {
    public:
    HealthPotion(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};


// strengthPotion.hpp
class StrengthPotion : public Item {
    public:
    StrengthPotion(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};


// defensePotion.hpp
class DefensePotion : public Item {
    public:
    DefensePotion(int hBonus, int sBonus, int dBonus);
    ItemEnum getItemEnum() const;
    ItemCategory getCategory() const;
};