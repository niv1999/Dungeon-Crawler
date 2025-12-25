// Matan Shtar 324125350
// Niv Shteingart 314830365

#pragma once
#include <string>

// Constants
const int MAX_WORDS_PER_LINE = 8;
const int MAX_CHARACTERS = 5;
const int MAX_MONSTERS = 10;
const int MAX_ROOMS = 25;
const int MAX_COMPATIBLE_ITEMS = 2;

// Enums
enum class Direction {
    NORTH, 
    EAST, 
    SOUTH, 
    WEST, 
    UNKNOWN
};

enum class CommandType
{
    CREATE_CHARACTER,
    CREATE_ROOM,
    SET_START_ROOM,
    CONNECT,
    PLACE_ITEM,
    PLACE_MONSTER,
    ENTER_DUNGEON,
    MOVE,
    FIGHT,
    PICK_UP,
    UNKNOWN
};

enum class ItemCategory {
    EQUIPMENT, 
    POTION,
    UNKNOWN
};

enum class ItemEnum {
    SWORD, 
    DAGGER, 
    WAND, 
    SHIELD, 
    HEALTH_POTION, 
    STRENGTH_POTION, 
    DEFENSE_POTION, 
    UNKNOWN
};

// Structs
struct Command
{
    CommandType type;
    std::string words[MAX_WORDS_PER_LINE];
    int totalWords;
    int lineNumber;
};