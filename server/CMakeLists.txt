cmake_minimum_required(VERSION 3.10)
project(GameServer)

# Find the dependencies
find_package(box2d REQUIRED)
find_package(nlohmann_json 3.10.5 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
# target_compile_features(GameServer PRIVATE cxx_std_17)

add_executable(GameServer
    src/main.cpp
    src/server.cpp
    src/game_state.cpp
    src/player.cpp
    src/bullet.cpp
    src/enemy.cpp
)

# include_directories(include)
# target_include_directories(GameServer PRIVATE include)
target_include_directories(GameServer PRIVATE
    include
    /usr/include/c++/11
    /usr/include/x86_64-linux-gnu/c++/11
    /usr/include/c++/11/backward
    /usr/lib/gcc/x86_64-linux-gnu/11/include
    /usr/local/include
    /usr/include/x86_64-linux-gnu
    /usr/include
)

target_link_libraries(GameServer PRIVATE box2d::box2d nlohmann_json::nlohmann_json)
