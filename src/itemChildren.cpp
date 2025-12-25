#include "itemChildren.hpp"

// sword.cpp
Sword::Sword(int hBonus, int sBonus, int dBonus) : Item("Sword", hBonus, sBonus + 5, dBonus + 10) {}

ItemEnum Sword::getItemEnum() const { return ItemEnum::SWORD; }

ItemCategory Sword::getCategory() const { return ItemCategory::EQUIPMENT; }


// dagger.cpp
Dagger::Dagger(int hBonus, int sBonus, int dBonus) : Item("Dagger", hBonus, sBonus + 7, dBonus + 3) {}

ItemEnum Dagger::getItemEnum() const { return ItemEnum::DAGGER; }

ItemCategory Dagger::getCategory() const { return ItemCategory::EQUIPMENT; }


// wand.cpp
Wand::Wand(int hBonus, int sBonus, int dBonus) : Item("Wand", hBonus, sBonus + 10, dBonus) {}

ItemEnum Wand::getItemEnum() const { return ItemEnum::WAND; }

ItemCategory Wand::getCategory() const { return ItemCategory::EQUIPMENT; }


// shield.cpp
Shield::Shield(int hBonus, int sBonus, int dBonus) : Item("Shield", hBonus, sBonus, dBonus + 5) {}

ItemEnum Shield::getItemEnum() const { return ItemEnum::SHIELD; }

ItemCategory Shield::getCategory() const { return ItemCategory::EQUIPMENT; }


// healthPotion.cpp
HealthPotion::HealthPotion(int hBonus, int sBonus, int dBonus) : Item("Health Potion", hBonus + 10, sBonus, dBonus) {}

ItemEnum HealthPotion::getItemEnum() const { return ItemEnum::HEALTH_POTION; }

ItemCategory HealthPotion::getCategory() const { return ItemCategory::POTION; }


// strengthPotion.cpp
StrengthPotion::StrengthPotion(int hBonus, int sBonus, int dBonus) : Item("Strength Potion", hBonus, sBonus + 5, dBonus) {}

ItemEnum StrengthPotion::getItemEnum() const { return ItemEnum::STRENGTH_POTION; }

ItemCategory StrengthPotion::getCategory() const { return ItemCategory::POTION; }


// defensePotion.cpp
DefensePotion::DefensePotion(int hBonus, int sBonus, int dBonus) : Item("Defense Potion", hBonus, sBonus, dBonus + 5) {}

ItemEnum DefensePotion::getItemEnum() const { return ItemEnum::DEFENSE_POTION; }

ItemCategory DefensePotion::getCategory() const { return ItemCategory::POTION; }