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
| **Create Room** | `Create Room <RoomName>` | Constructs a new room in the dungeon. |
| **Connect** | `Connect <Room1> <Room2> <Direction>` | Links two rooms together in a specific direction. |
| **Set Start** | `Set StartRoom <RoomName>` | Designates the entry point for the dungeon. |

### 👤 Entity Placement
| Command | Schema | Description |
| :--- | :--- | :--- |
| **Create Character** | `Create <Class> <Name>` | Initializes a new hero (`Warrior`, `Mage`, or `Thief`). |
| **Place Item** | `Place <ItemName> <RoomName> <HP> <STR> <DEF>` | Spawns an item with bonus stats in a room. |
| **Place Monster** | `Place Monster <Name> <RoomName> <HP> <STR> <DEF>` | Spawns an enemy with specific stats in a room. |

### ⚔️ Gameplay Actions
| Command | Schema | Description |
| :--- | :--- | :--- |
| **Enter** | `Enter Dungeon <CharacterName>` | Spawns a character into the designated Start Room. |
| **Move** | `Move <CharacterName> <Direction>` | Moves a character to a connected adjacent room. |
| **PickUp** | `PickUp <CharacterName> <ItemName>` | Character attempts to take an item from the room they're in. |
| **Fight** | `Fight <CharacterName> <MonsterName>` | Engages the character in combat with a monster. |


### 💡 Schema Notes & System Limitations

The engine enforces strict validation logic to ensure stability. Below is a complete list of checks performed for each command type.

#### 1. Global Validation Rules
* **Argument Count:** Every command must have the exact number of words specified in the schema. Extra words or missing arguments will trigger an `Invalid number of arguments` error.
* **Numeric Validation:**
    * **Items:** HP, STR, and DEF bonuses must be **positive integers or 0**.
    * **Monsters:** Health and Strength must be **strictly positive integers (>0)**. Defense can be 0.
* **Entity Existence:** Commands referencing specific Rooms, Characters, or Monsters will fail if those entities have not been created yet.

#### 2. Capacity Limits
* **Characters:** Maximum of **5** active characters.
* **Rooms:** Maximum of **25** rooms.
* **Monsters:** Maximum of **10** active monsters.
    * *Note:* Attempting to create more than these limits triggers a "Capacity limit reached" error.

#### 3. Creation & Placement Constraints
* **Unique Names:** Names for Rooms, Characters, and Monsters must be unique across their respective lists. Duplicates are rejected.
* **Valid Classes:** Characters must be created with the class `Warrior`, `Mage`, or `Thief` (case-insensitive).
* **Valid Item Names:** Item names must match the internal Enum list (e.g., `Sword`, `Shield`, `HealthPotion`, etc.). Unknown item names are rejected.
* **Room Occupancy (The "One-Entity" Rule):**
    * **Items:** A room can hold **max 1 Item**. You cannot place an item in a room that already has one.
    * **Monsters:** A room can hold **max 1 Monster**. You cannot place a monster in a room that already has one.

#### 4. Topology & Connections
* **Self-Connection:** You cannot connect a room to itself.
* **Existing Connection (Source):** You cannot overwrite an exit. (e.g., If `RoomA` already has a North neighbor, you cannot connect it North to another room).
* **Existing Connection (Target):** The target room (`Room2`) **must not be linked** to any other room yet.
    * *Constraint:* This effectively enforces a specific graph structure where you attach new, isolated rooms to the existing dungeon, rather than linking existing rooms together in loops.

#### 5. Gameplay Logic
* **Dungeon Entry:**
    * **Start Room:** A `StartRoom` must be set via command before anyone can enter.
    * **One-Time Entry:** A character cannot enter the dungeon if they are already inside (i.e., if they already have a `CurrentRoom`).
* **Movement:**
    * **Walls:** Characters cannot move in a direction that has no connection (`nullptr`).
    * **Active State:** Characters cannot move if they haven't entered the dungeon yet.
* **Combat:**
    * **Proximity:** The specific Monster must be in the **same room** as the Character.
    * **Target Validity:** You cannot fight a monster that doesn't exist in the global registry.
    * **Permadeath:** If the player loses, the `Character` object is deleted from memory.
    * **Victory:** If the player wins, the `Monster` object is deleted and removed from the room.
* **Item Pickup:**
    * **Room Contents:** The room must actually contain an item (cannot pick up from an empty floor).
    * **Specific Target:** The item name provided in the command must match the item actually in the room.
    * **Class Compatibility:**
        * **Warrior:** Cannot pick up `Wand`, `Dagger`.
        * **Mage:** Cannot pick up `Sword`, `Shield`, `Dagger`.
        * **Thief:** Cannot pick up `Sword`, `Shield`, `Wand`.

---

## ⚙️ How to Build and Run

### Prerequisites
* A C++ Compiler (`g++` or `clang++`)
* Standard C++11 or higher

### Compilation
Since all files are in the same directory, compilation is straightforward. 
First upload an `input.txt` file with all the commands.
Open your terminal in the project folder (src) and run:

```bash
# Compile all C++ source files
g++ -std=c++11 *.cpp -o dungeon_game
