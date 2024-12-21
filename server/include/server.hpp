
#ifndef SERVER_HPP
#define SERVER_HPP

#include "game_state.hpp"

class Server {
public:
    // ...existing code...
    void start();
    void stop();
    // ...existing code...
private:
    GameState gameState;
    // ...existing code...
};

#endif // SERVER_HPP