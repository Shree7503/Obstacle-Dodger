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

## Building the Game

1. Clone the repository:
```bash
git clone [your-repository-url]
cd [repository-name]
```

2. Build the game using make:
```bash
make
```

3. Run the game:
```bash
make run
```

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

## Project Structure

```
.
├── main.cpp          # Main game source code
├── Makefile         # Build configuration
├── README.md        # This file
└── arial.ttf        # Font file (required)
```

## Game Classes

- `GameObject`: Base class for game entities
- `Dinosaur`: Player character with jumping mechanics
- `Cactus`: Obstacle class with movement logic
- `Game`: Main game loop and state management

## Technical Details

- Written in C++11
- Uses SFML for graphics and window management
- Implements basic collision detection
- Features dynamic difficulty scaling
- Uses smart pointers for memory management
- Includes error handling for resource loading

## Customization

You can modify various game parameters by changing the constants in the source code:
- Dinosaur jump force and gravity
- Cactus movement speed
- Spawn timing
- Window dimensions
- Colors and sizes of objects

## Troubleshooting

### Common Issues

1. **SFML library not found**
   - Make sure SFML is properly installed
   - Check if library paths are correct in Makefile

2. **Font loading error**
   - Ensure 'arial.ttf' is in the same directory as the executable
   - Try using a different font and update the font path in the code

3. **Compilation errors**
   - Verify your C++ compiler supports C++11
   - Check if all required SFML components are installed

## Contributing

Feel free to fork the project and submit pull requests with improvements such as:
- New features
- Bug fixes
- Performance optimizations
- Better graphics
- Sound effects
- Additional game mechanics

## License

[Add your chosen license here]

## Credits

Built using:
- SFML (Simple and Fast Multimedia Library)
- Inspired by Chrome's dinosaur game