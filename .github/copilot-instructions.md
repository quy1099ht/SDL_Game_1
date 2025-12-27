# Copilot Instructions for SDL_Game_1

Welcome to the SDL_Game_1 codebase! This document provides essential guidelines for AI coding agents to be productive in this project. Please follow these instructions to maintain consistency and quality.

## Project Overview

SDL_Game_1 is a simple 2D platformer game built using C++ and SDL2. The game involves basic mechanics like block jumping. The project structure is designed to separate concerns between rendering, entity management, and utility functions.

### Key Components

- **Rendering**: Handled by `RenderWindow` class in `src/renderwindow.cpp` and `include/RenderWindow.hpp`.
- **Entities**: Managed through the `Entity` class in `src/entity.cpp` and `include/Entity.hpp`.
- **Utilities**: Common helper functions are located in `include/Utils.hpp`.
- **Math**: Mathematical operations are abstracted in `include/Math.hpp`.

## Build and Run Instructions

### Prerequisites

Ensure the following dependencies are installed:
- SDL2
- SDL2_image
- g++

### Building the Project

1. Open the project in Sublime Text or your preferred editor.
2. Press `F7` to build the project.

Alternatively, use the provided script:
```bash
./build_and_run.sh
```

### Running the Game

- Navigate to `bin/debug/`.
- Run the generated `.exe` file.

## Project-Specific Conventions

- **File Organization**: Source files are in `src/`, headers in `include/`, and resources (e.g., graphics) in `res/`.
- **Naming**: Classes use PascalCase (e.g., `Entity`, `RenderWindow`), and functions use camelCase.
- **Error Handling**: Minimal error handling is implemented; ensure SDL functions return valid pointers before use.

## External Resources

- SDL2 setup guide: [codergopher YouTube Channel](https://www.youtube.com/channel/UCfiC4q3AahU4Io-s83-CIbQ)
- SDL2 library: [Download Link](https://drive.google.com/drive/folders/1Y6eDY8mkzXZMScY476sLLFnKBFUZQ7-8?usp=drive_link)

## Examples of Common Patterns

### Rendering a Texture
```cpp
RenderWindow window("Game", 800, 600);
SDL_Texture* texture = window.loadTexture("res/gfx/block.png");
window.clear();
window.render(texture, x, y);
window.display();
```

### Managing Entities
```cpp
Entity player(x, y, width, height);
player.update();
player.render(window);
```

## Debugging Tips

- Use `SDL_Log` for debugging messages.
- Check the `bin/debug/` folder for build outputs.
- Use `utils::logTexts` and `utils::logTime` for logging.

## Contribution Guidelines

- Follow the existing code style.
- Document new functions and classes.
- Test changes thoroughly before committing.

---

Feel free to update this document as the project evolves.