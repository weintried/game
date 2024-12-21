
cmake_minimum_required(VERSION 3.10)
project(GameServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(GameServer
    src/main.cpp
    src/server.cpp
    src/game_state.cpp
    src/player.cpp
    src/bullet.cpp
)