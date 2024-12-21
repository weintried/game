
#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
#include "player.hpp"
#include "bullet.hpp"

class GameState {
public:
    // ...existing code...
    void update();
    // ...existing code...
private:
    std::vector<Player> players;
    std::vector<Bullet> bullets;
    // ...existing code...
};

#endif // GAME_STATE_HPP