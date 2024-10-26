# SFML Dinosaur Game

A simple endless runner game inspired by Chrome's dinosaur game, built with C++ and SFML. The player controls a dinosaur that must jump over incoming cacti to survive and achieve a high score.

## Features

- Simple one-button gameplay
- Progressive difficulty (cacti spawn more frequently as score increases)
- Score tracking
- Game over screen with restart capability
- Smooth jumping physics
- Random obstacle generation

## Prerequisites

Before you can build and run the game, you need to have the following installed:
- C++ compiler (g++ recommended)
- SFML library (2.5 or newer)
- Make build system

### Installing SFML

#### Ubuntu/Debian
```bash
sudo apt-get install libsfml-dev
```

#### macOS (using Homebrew)
```bash
brew install sfml
```

#### Windows (using MSYS2)
```bash
pacman -S mingw-w64-x86_64-sfml
```

## Build System

The project uses a Makefile build system with the following structure:

### Directory Structure
```
.
├── main.cpp          # Main game source code
├── Makefile         # Build configuration
├── README.md        # This file
├── arial.ttf        # Font file (required)
├── build/          # Compiled object files (created during build)
└── bin/            # Executable output directory (created during build)
```

### Makefile Configuration

Before building, you need to configure the SFML paths in the Makefile:

1. Open the Makefile in a text editor
2. Locate these lines at the top:
```makefile
SFML_INCLUDE = -I/path/to/sfml/include
SFML_LIB_PATH = -L/path/to/sfml/lib
```
3. Replace them with your actual SFML paths:
   - On Linux (if installed via package manager): Usually no change needed
   - On macOS (Homebrew): Usually `/usr/local/include` and `/usr/local/lib`
   - On Windows: Depends on your MSYS2 installation

### Build Commands

The Makefile provides several useful commands:

```bash
# Build the game
make

# Build and run the game
make run

# Clean build files
make clean

# Install the game system-wide
make install

# Uninstall the game
make uninstall
```

### Compiler Flags

The build system uses the following compiler flags:
- `-Wall -Wextra`: Enable comprehensive warnings
- `-std=c++11`: Use C++11 standard
- `-O2`: Enable optimization
- `-MMD -MP`: Generate dependency files

## How to Play

- Press SPACE to make the dinosaur jump
- Avoid the incoming red cacti
- Your score increases the longer you survive
- When you hit a cactus, the game ends
- Press R to restart after game over

## Controls

- SPACE: Jump
- R: Restart (after game over)
- Close window to exit game

## Game Classes

### GameObject
Base class for game entities with common functionality:
- Position and collision detection
- Virtual update method
- Drawing capabilities

### Dinosaur
Player character class featuring:
- Jump mechanics with gravity
- Ground collision detection
- State management (jumping/grounded)

### Cactus
Obstacle class implementing:
- Automatic movement
- Screen boundary checking
- Collision detection with player

### Game
Main game class managing:
- Game loop and state
- Object creation and cleanup
- Score tracking
- User input
- Rendering

## Customization

You can modify various game parameters by changing the constants in the source code:
- Dinosaur jump force and gravity
- Cactus movement speed
- Spawn timing
- Window dimensions
- Colors and sizes of objects


