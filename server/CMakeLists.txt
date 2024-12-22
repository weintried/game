cmake_minimum_required(VERSION 3.10)
project(GameServer)

# Find the Box2D library
find_package(box2d REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameServer
    src/main.cpp
    src/server.cpp
    src/game_state.cpp
    src/player.cpp
    src/bullet.cpp
)

# include_directories(include)
target_include_directories(GameServer PRIVATE include)

# target_link_libraries(GameServer box2d::box2d)
target_link_libraries(GameServer PRIVATE box2d::box2d)
