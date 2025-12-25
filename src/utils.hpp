// Utility functions that are used across multiple classes
#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include "constants.hpp"

namespace Utils
{
    // Create a new array double the size of the previous one (manual implementation of realloc)
    template <typename T>
    void resizeArray(T *&array, int &capacity, int count)
    {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        T *newArray = new T[capacity];
        if (array != nullptr)
        {
            for (int i = 0; i < count; i++)
            {
                newArray[i] = array[i];
            }
            delete[] array;
        }

        array = newArray;
    }

    // Convert entire string to lower-case characters
    inline std::string toLowerCase(std::string str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            str[i] = std::tolower((unsigned char)str[i]);
        }
        return str;
    }

    // Check if a number is 0 or positive
    inline bool isPositiveNumber(const std::string &str)
    {
        return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char c)
                                           { return std::isdigit(c); });
    }

    // Format error messages
    inline std::string buildErrMsg(int lineNumber, const std::string &msg)
    {
        return " 🚫 [ERROR] (Line " + std::to_string(lineNumber) + ") " + msg;
    }

    // Extract command type enum from a string
    inline CommandType extractCommandType(const std::string *words)
    {
        std::string firstWord = Utils::toLowerCase(words[0]);
        std::string secondWord = Utils::toLowerCase(words[1]);

        if (firstWord == "create")
        {
            if (secondWord == "room")
                return CommandType::CREATE_ROOM;
            else
                return CommandType::CREATE_CHARACTER;
        }

        if (firstWord == "place")
        {
            if (secondWord == "monster")
                return CommandType::PLACE_MONSTER;
            else
                return CommandType::PLACE_ITEM;
        }

        if (firstWord == "set" && secondWord == "startroom")
            return CommandType::SET_START_ROOM;

        if (firstWord == "connect")
            return CommandType::CONNECT;

        if (firstWord == "enter" && secondWord == "dungeon")
            return CommandType::ENTER_DUNGEON;

        if (firstWord == "move")
            return CommandType::MOVE;

        if (firstWord == "fight")
            return CommandType::FIGHT;

        if (firstWord == "pickup")
            return CommandType::PICK_UP;

        return CommandType::UNKNOWN;
    }

    // Convert direction from string to enum
    inline Direction dirStringToEnum(const std::string &direction)
    {
        std::string dir = toLowerCase(direction);
        if (dir == "north")
            return Direction::NORTH;
        if (dir == "east")
            return Direction::EAST;
        if (dir == "south")
            return Direction::SOUTH;
        if (dir == "west")
            return Direction::WEST;
        return Direction::UNKNOWN;
    }

    // Convert item from string to enum
    inline ItemEnum itemStringToEnum(const std::string &itemName)
    {
        std::string item = toLowerCase(itemName);
        if (item == "sword")
            return ItemEnum::SWORD;
        if (item == "dagger")
            return ItemEnum::DAGGER;
        if (item == "shield")
            return ItemEnum::SHIELD;
        if (item == "wand")
            return ItemEnum::WAND;
        if (item == "healthpotion")
            return ItemEnum::HEALTH_POTION;
        if (item == "strengthpotion")
            return ItemEnum::STRENGTH_POTION;
        if (item == "defensepotion")
            return ItemEnum::DEFENSE_POTION;
        return ItemEnum::UNKNOWN;
    }
}