# Game Server

This project is a basic game server built with C++ and Box2D.

## Features
- Manages game state
- Handles players and bullets
- Uses Box2D for physics

## Building
1. Install [Box2D](https://github.com/erincatto/box2d).
2. Run:

## File Overview
We currently have 9 source/header files and 1 build file:
1. **main.cpp**: Entry point, sets up Box2D and starts the server.
2. **server.cpp/server.hpp**: Manages the server’s lifecycle and main game state.
3. **player.cpp/player.hpp**: Provides functions for player movement and position.
4. **bullet.cpp/bullet.hpp**: Controls bullet updates and speed.
5. **game_state.cpp/game_state.hpp**: Tracks and updates players and bullets.
6. **CMakeLists.txt**: Configures the build, locates Box2D, and produces the GameServer executable.
