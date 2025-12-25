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

## ⚙️ How to Build and Run

### Prerequisites
* A C++ Compiler (`g++` or `clang++`)
* Standard C++11 or higher

### Compilation
Since all files are in the same directory, compilation is straightforward. Open your terminal in the project folder and run:

```bash
# Compile all C++ source files
g++ -std=c++11 *.cpp -o dungeon_game
