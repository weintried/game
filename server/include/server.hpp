
#ifndef SERVER_HPP
#define SERVER_HPP

#include "game_state.hpp"

/**
 * @class Server
 * @brief Represents the game server, handling game state updates and player
 * interactions.
 *
 * The Server class manages the game state, updating it based on player
 * interactions and other game events. It also provides functionality to run the
 * game server and update the game state.
 */
class Server {
   public:
    Server();
    void run();
    void update_game_state(float deltaTime);

   private:
    GameState game_state;
};

#endif  // SERVER_HPP