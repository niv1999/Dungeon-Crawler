// Matan Shtar 324125350
// Niv Shteingart 314830365

#include "game.hpp"
#include "utils.hpp"
#include "characterChildren.hpp"
#include "itemChildren.hpp"
#include <string>
using namespace std;

// Execute Command - Create Character
string Game::executeCreateCharacter(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Create <class> <name>\"");

    if (dungeon.getCharacterCount() >= MAX_CHARACTERS)
        return Utils::buildErrMsg(cmd.lineNumber, "Capacity limit reached: Cannot create more than " + to_string(MAX_CHARACTERS) + " characters");

    if (dungeon.findCharacter(cmd.words[2]) != nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character name '" + cmd.words[2] + "' already exists");

    Character *newCharacter = nullptr;
    string characterClass = Utils::toLowerCase(cmd.words[1]);
    if (characterClass == "warrior")
    {
        newCharacter = new Warrior(cmd.words[2]);
    }
    else if (characterClass == "thief")
    {
        newCharacter = new Thief(cmd.words[2]);
    }
    else if (characterClass == "mage")
    {
        newCharacter = new Mage(cmd.words[2]);
    }
    else
    {
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid character class name: " + cmd.words[1]);
    }

    dungeon.addNewCharacter(newCharacter);
    return " ✨ [CREATION] A new " + characterClass + " named '" + cmd.words[2] + "' has entered the world.";
}

// Execute Command - Create Room
string Game::executeCreateRoom(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Create Room <roomName>\"");

    if (dungeon.getRoomCount() >= MAX_ROOMS)
        return Utils::buildErrMsg(cmd.lineNumber, "Capacity limit reached: Cannot create more than " + to_string(MAX_ROOMS) + " rooms");

    if (dungeon.findRoom(cmd.words[2]) != nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room name '" + cmd.words[2] + "' already exists");

    Room *newRoom = new Room(cmd.words[2]);
    dungeon.addNewRoom(newRoom);
    return " 🏗️ [BUILD] Room constructed: '" + cmd.words[2] + "'.";
}

// Execute Command - Place Item in a Room
string Game::executePlaceItem(const Command &cmd)
{
    if (cmd.totalWords != 6)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Place <item> <roomName> <hpBonus> <strBonus> <defBonus>\"");

    Room *room = dungeon.findRoom(cmd.words[2]);
    if (room == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room name '" + cmd.words[2] + "' does not exist");

    if (!Utils::isPositiveNumber(cmd.words[3]) ||
        !Utils::isPositiveNumber(cmd.words[4]) ||
        !Utils::isPositiveNumber(cmd.words[5]))
    {
        return Utils::buildErrMsg(cmd.lineNumber, "Health, Strength, Defense bonuses must be positive numbers or 0");
    }

    if (room->getItem() != nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[2] + "' already contains an item. Can't place more than 1 item in a room");

    ItemEnum itemName = Utils::itemStringToEnum(cmd.words[1]);
    if (itemName == ItemEnum::UNKNOWN)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid item name: " + cmd.words[1]);

    int hpBonus = std::stoi(cmd.words[3]);
    int strBonus = std::stoi(cmd.words[4]);
    int defBonus = std::stoi(cmd.words[5]);

    Item *newItem;
    switch (itemName)
    {
    case ItemEnum::SWORD:
        newItem = new Sword(hpBonus, strBonus, defBonus);
        break;
    case ItemEnum::DAGGER:
        newItem = new Dagger(hpBonus, strBonus, defBonus);
        break;
    case ItemEnum::WAND:
        newItem = new Wand(hpBonus, strBonus, defBonus);
        break;
    case ItemEnum::SHIELD:
        newItem = new Shield(hpBonus, strBonus, defBonus);
        break;
    case ItemEnum::HEALTH_POTION:
        newItem = new HealthPotion(hpBonus, strBonus, defBonus);
        break;
    case ItemEnum::STRENGTH_POTION:
        newItem = new StrengthPotion(hpBonus, strBonus, defBonus);
        break;
    case ItemEnum::DEFENSE_POTION:
        newItem = new DefensePotion(hpBonus, strBonus, defBonus);
        break;
    }

    room->setItem(newItem);
    return " 📦 [ITEM] The '" + newItem->getName() + "' was placed in '" + room->getName() + "'. " + newItem->getPrettyStats();
}

// Execute Command - Place Monster in a Room
string Game::executePlaceMonster(const Command &cmd)
{
    if (cmd.totalWords != 7)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Place Monster <name> <roomName> <health> <strength> <defense>\"");

    if (dungeon.findMonster(cmd.words[2]) != nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Monster name '" + cmd.words[2] + "' already exists");

    Room *room = dungeon.findRoom(cmd.words[3]);
    if (room == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room name '" + cmd.words[3] + "' does not exist");

    if (!Utils::isPositiveNumber(cmd.words[4]) ||
        !Utils::isPositiveNumber(cmd.words[5]) ||
        !Utils::isPositiveNumber(cmd.words[6]))
    {
        return Utils::buildErrMsg(cmd.lineNumber, "Health, Strength, Defense bonuses must be positive numbers");
    }

    if (room->getMonster() != nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[3] + "' Already has a monster in it. Can't place more than 1 monster in a room");

    int health = std::stoi(cmd.words[4]);
    int strength = std::stoi(cmd.words[5]);
    int defense = std::stoi(cmd.words[6]);

    if (health == 0 || strength == 0)
        return Utils::buildErrMsg(cmd.lineNumber, "Can't create a monster with health or strength of 0. Must be a positive integer");

    if (dungeon.getMonsterCount() >= MAX_MONSTERS)
        return Utils::buildErrMsg(cmd.lineNumber, "Capacity limit reached: Cannot create more than " + to_string(MAX_MONSTERS) + " monsters");

    Monster *newMonster = new Monster(cmd.words[2], health, strength, defense);
    dungeon.addNewMonster(newMonster);
    room->setMonster(newMonster);
    return " ⚠️ [SPAWN] A '" + newMonster->getName() + "' now lurks in '" + room->getName() + "'!\n" + newMonster->getPrettyStats();
}

// Execute Command - Set Start Room
string Game::executeSetStartRoom(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Set StartRoom <roomName>\"");

    Room *room = dungeon.findRoom(cmd.words[2]);
    if (room == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room name '" + cmd.words[2] + "' does not exist");

    dungeon.setStartRoom(room);
    return " 📍 [SETUP] The journey is set to begin at '" + room->getName() + "'.";
}

// Execute Command - Connect a Room
string Game::executeConnectRoom(const Command &cmd)
{
    if (cmd.totalWords != 4)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Connect <roomName> <roomName> <direction>\"");

    Room *roomA = dungeon.findRoom(cmd.words[1]);
    if (roomA == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room name '" + cmd.words[1] + "' does not exist");

    Room *roomB = dungeon.findRoom(cmd.words[2]);
    if (roomB == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Room name '" + cmd.words[2] + "' does not exist");

    Direction dir = Utils::dirStringToEnum(cmd.words[3]);
    if (dir == Direction::UNKNOWN)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid direction. Must be one of [North, East, South, West]");

    if (roomA == roomB)
        return Utils::buildErrMsg(cmd.lineNumber, "Can't connect a room to itself");

    if (roomB->isLinked())
        return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[2] + "' is already connected to another room in the dungeon");

    switch (dir)
    {
    case Direction::NORTH:
        if (roomA->north != nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[1] + "' is already connected to the room '" + roomA->north->getName() + "' in that direction");
        roomA->connectNorth(roomB);
        break;
    case Direction::EAST:
        if (roomA->east != nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[1] + "' is already connected to the room '" + roomA->east->getName() + "' in that direction");
        roomA->connectEast(roomB);
        break;
    case Direction::SOUTH:
        if (roomA->south != nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[1] + "' is already connected to the room '" + roomA->south->getName() + "' in that direction");
        roomA->connectSouth(roomB);
        break;
    case Direction::WEST:
        if (roomA->west != nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Room '" + cmd.words[1] + "' is already connected to the room '" + roomA->west->getName() + "' in that direction");
        roomA->connectWest(roomB);
        break;
    }

    return " 🔗 [LINK] Connected '" + cmd.words[1] + "' " + Utils::toLowerCase(cmd.words[3]) + " ↔ " + "'" + cmd.words[2] + "'.";
}

// Execute Command - Enter the Dungeon
string Game::executeEnterDungeon(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Enter Dungeon <characterName>\"");

    Character *character = dungeon.findCharacter(cmd.words[2]);
    if (character == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[2] + "' does not exist");

    if (character->getCurrentRoom() != nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + character->getName() + "' already entered the dungeon");

    Room *startRoom = dungeon.getStartRoom();
    if (startRoom == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Must set a start room before entering the dungeon");

    character->setCurrentRoom(startRoom);
    return " 🚪 [ENTER] " + character->getName() + " steps into the dungeon. The adventure begins!\n" + character->getPrettyStats() + startRoom->getDescription() + "\n   ---------------------------------------\n";
}

// Execute Command - Move Character
string Game::executeMove(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Move <characterName> <direction>\"");

    Character *character = dungeon.findCharacter(cmd.words[1]);
    if (character == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' does not exist");

    Room *currRoom = character->getCurrentRoom();
    if (currRoom == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + character->getName() + "' did not enter the dungeon");

    Direction dir = Utils::dirStringToEnum(cmd.words[2]);
    if (dir == Direction::UNKNOWN)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid direction. Must be one of [North, East, South, West]");

    switch (dir)
    {
    case Direction::NORTH:
        if (currRoom->north == nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' attempted to move north. Cannot move that way; the path is blocked");
        character->setCurrentRoom(currRoom->north);
        break;
    case Direction::EAST:
        if (currRoom->east == nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' attempted to move east. Cannot move that way; the path is blocked");
        character->setCurrentRoom(currRoom->east);
        break;
    case Direction::SOUTH:
        if (currRoom->south == nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' attempted to move south. Cannot move that way; the path is blocked");
        character->setCurrentRoom(currRoom->south);
        break;
    case Direction::WEST:
        if (currRoom->west == nullptr)
            return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' attempted to move west. Cannot move that way; the path is blocked");
        character->setCurrentRoom(currRoom->west);
        break;
    }

    string direction = Utils::toLowerCase(cmd.words[2]);
    return " 👣 [MOVE] " + character->getName() + " marched " + direction + " into '" + character->getCurrentRoom()->getName() + "'.\n" + character->getCurrentRoom()->getDescription();
}

// Execute Command - Fight with a Monster
string Game::executeFight(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"Fight <characterName> <monsterName>\"");

    Character *character = dungeon.findCharacter(cmd.words[1]);
    if (character == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' does not exist");

    Room *currRoom = character->getCurrentRoom();
    if (currRoom == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + character->getName() + "' did not enter the dungeon");

    Monster *monster = dungeon.findMonster(cmd.words[2]);
    if (monster == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Monster '" + cmd.words[2] + "' does not exist");

    if (monster != currRoom->getMonster())
        return Utils::buildErrMsg(cmd.lineNumber, "The monster '" + monster->getName() + "' is not in the same room as the character (" + currRoom->getName() + ")");

    string combatMsg = "\n          ⚔️  [COMBAT STARTED]  ⚔️\n";
    combatMsg += "   ---------------------------------------\n";
    combatMsg += monster->getPrettyStats() + "\n";
    combatMsg += "   ---------------------------------------\n";
    combatMsg += "                     VS.\n";
    combatMsg += character->getPrettyStats();
    setMessage(combatMsg);

    bool playersTurn = true;
    while (character->isAlive() && !monster->isDefeated())
    {
        if (playersTurn)
        {
            character->attack(*monster);
            setMessage(character->getCombatRoundMsg());
            playersTurn = false;
        }
        else
        {
            monster->attack(*character);
            setMessage(monster->getCombatRoundMsg());
            playersTurn = true;
        }
    }

    if (character->isAlive())
    {
        string successMsg = "   🏆  [VICTORY] " + character->getName() + " has slain the " + monster->getName() + "!\n\n   ---------------------------------------\n";
        dungeon.removeMonster(monster);
        currRoom->setMonster(nullptr);
        delete monster;
        return successMsg;
    }

    string msg = "   💀  [DEFEAT] " + character->getName() + " has fallen to the " + monster->getName() + "...\n\n   ---------------------------------------\n";
    dungeon.removeCharacter(character);
    delete character;
    return msg;
}

// Execute Command - Pick Up an Item in the Room
string Game::executePickUp(const Command &cmd)
{
    if (cmd.totalWords != 3)
        return Utils::buildErrMsg(cmd.lineNumber, "Invalid number of arguments in the command. Must follow the pattern of \"PickUp <characterName> <itemName>\"");

    Character *character = dungeon.findCharacter(cmd.words[1]);
    if (character == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + cmd.words[1] + "' does not exist");

    if (character->getCurrentRoom() == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "Character '" + character->getName() + "' did not enter the dungeon");

    ItemEnum itemName = Utils::itemStringToEnum(cmd.words[2]);
    if (itemName == ItemEnum::UNKNOWN)
        return Utils::buildErrMsg(cmd.lineNumber, "Item name '" + cmd.words[2] + "' is invalid");

    Item *itemInRoom = character->getCurrentRoom()->getItem();
    if (itemInRoom == nullptr)
        return Utils::buildErrMsg(cmd.lineNumber, "There is no item in " + character->getCurrentRoom()->getName() + " for " + character->getName() + " to pick up");

    if (itemName != itemInRoom->getItemEnum())
        return Utils::buildErrMsg(cmd.lineNumber, "Item '" + cmd.words[2] + "' is not in the same room as the character");

    if (!character->isItemCompatible(itemInRoom))
        return Utils::buildErrMsg(cmd.lineNumber, "Character of class '" + character->getClass() + "' can't pick up a " + itemInRoom->getName());

    *character += *itemInRoom;
    return character->getItemActionMsg();
}