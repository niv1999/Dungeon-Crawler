# 🏰 Dungeon Crawler (C++)

A robust, text-based Dungeon Crawler engine built in C++. This project demonstrates advanced Object-Oriented Programming principles, custom dynamic memory management, and file I/O processing to simulate a dynamic Dungeons & Dragons style adventure.

---

## 🚀 Features

### 🛠 Technical Highlights
* **Polymorphism & Inheritance:** Distinct `Character` classes (Warrior, Mage, Thief) and `Item` types (Sword, Potion, etc.) with unique behaviors and compatibility logic.
* **Dynamic Memory Management:** Custom array resizing and strictly managed object lifecycles to prevent memory leaks.
* **File-Based Input System:** Parses multiple commands from a text file to build the world, populate it, and execute game logic.
* **Rich Logging:** Generates a detailed, formatted Text log of the entire game session, featuring combat logs, inventory updates, and error reporting.

### 🎮 Gameplay Features
* **World Building:** Create rooms, connect them in any direction (North, East, South, West), and populate them with monsters and loot.
* **Combat System:** Turn-based combat engine where stats (Strength, Defense) and equipment determine the victor.
* **Inventory System:** Characters can equip items, but only if they are compatible with their class (e.g., Thieves can't wield heavy Swords).
* **Smart Validation:** The engine prevents illegal moves, such as walking into walls, picking up items that don't exist, or interacting with dead entities.

---

## 📂 File Organization

Although all files reside in the root directory, they are logically categorized by their responsibility:

### ⚡ Core Engine
* `main.cpp`: The entry point of the application.
* `game.hpp/cpp`: The game controller; handles file loading, command parsing (`loadFromFile`), and execution (`executeCommands`).
* `utils.hpp`: Static helper functions for string manipulation and custom array resizing.
* `constants.hpp`: Global game rules, enums (Commands, Directions), and limits.

### 🏰 World & Environment
* `dungeon.hpp/cpp`: The central database holding all active objects (Rooms, Monsters, Characters).
* `room.hpp/cpp`: Represents map locations and manages pointers to neighboring rooms, items, and monsters.

### 👤 Characters & Entities
* `character.hpp/cpp`: The abstract base class for players.
* `characterChildren.hpp/cpp`: Derived classes (`Warrior`, `Mage`, `Thief`) implementing specific class logic.
* `monster.hpp/cpp`: Enemy logic & stats.

### ⚔️ Items & Loot
* `item.hpp/cpp`: The abstract base class for game objects.
* `itemChildren.hpp/cpp`: Specific item implementations (`Sword`, `HealthPotion`, etc.).

---

## 📜 Command Reference

The engine processes commands line-by-line from the input file. Below is the required schema for every supported action.

### 🏗 World Construction
| Command | Schema | Description |
| :--- | :--- | :--- |
| **Create Room** | `Create Room <RoomName>` | Defines a new location (Max 25 rooms). |
| **Connect** | `Connect <Room1> <Room2> <Direction>` | Links two rooms via `North`, `South`, `East`, or `West`. |
| **Set Start** | `Set StartRoom <RoomName>` | Defines where all characters begin the game. |

### 👤 Entity Placement
| Command | Schema | Description |
| :--- | :--- | :--- |
| **Create Character** | `Create <Class> <Name>` | Creates a `Warrior`, `Mage`, or `Thief` (Max 5 characters). |
| **Place Item** | `Place <ItemName> <RoomName> <HP> <STR> <DEF>` | Spawns a `Sword`, `Wand`, `Dagger`, `Shield`, or `HealthPotion`. |
| **Place Monster** | `Place Monster <Name> <RoomName> <HP> <STR> <DEF>` | Spawns an enemy in a specific room (Max 10 monsters). |

### ⚔️ Gameplay Actions
| Command | Schema | Description |
| :--- | :--- | :--- |
| **Enter** | `Enter Dungeon <CharacterName>` | Places a created character into the Start Room. |
| **Move** | `Move <CharacterName> <Direction>` | Moves the character to an adjacent room. |
| **PickUp** | `PickUp <CharacterName> <ItemName>` | Attempts to take an item (Checks class compatibility and stats). |
| **Fight** | `Fight <CharacterName> <MonsterName>` | Initiates turn-based combat in the current room. |


### 💡 Schema Notes
* **Case Sensitivity:** Commands like `Create Room` are case-insensitive (e.g., `cReAtE rOoM` works), but **Entity Names** (e.g., `Thorin`, `Room01`) are case-sensitive.
* **Item Compatibility:** * **Warriors:** Can equip Swords and Shields.
    * **Mages:** Can equip Wands.
    * **Thieves:** Can equip Daggers.
* **Inventory Logic:**
    * **Consumables:** Potions are used instantly upon pickup and do not occupy a slot.
    * **Automatic Swapping:** If a character picks up a superior item of the same type, they automatically swap; if the new item is weaker, they keep their current gear.
    * **Room Limits:** Each room can hold only **one** item at a time. Picking up an item clears the room slot.

---

## ⚙️ How to Build and Run

### Prerequisites
* A C++ Compiler (`g++` or `clang++`)
* Standard C++11 or higher

### Compilation
Since all files are in the same directory, compilation is straightforward. 
First upload or modify the existing input.txt file to determine all the commands.
Open your terminal in the project folder and run:

```bash
# Compile all C++ source files
g++ -std=c++11 *.cpp -o dungeon_game
