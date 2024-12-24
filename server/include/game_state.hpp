/**
 * @file game_state.hpp
 * @author wein
 * @brief GameState class declaration
 * @version 0.1
 * @date 2024-12-22
 *
 * The GameState class represents the current state of the game, including
 * information such as the current game state, the remaining time, and the
 * reason for the game ending.
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "bullet.hpp"
#include "config.hpp"
#include "enemy.hpp"
#include "player.hpp"

/**
 * @class GameState
 * @brief Represents the current state of the game.
 *
 * The GameState class encapsulates information about the current state of the
 * game, including the game state (e.g., Ready, Game_start, Game_over), the
 * frame count, the remaining time, and the reason for the game ending. It also
 * provides serialization support through the nlohmann::json library.
 */
class GameState {
   public:
    /**
     * @brief Construct a new GameState object
     *
     */
    GameState() = default;

    void update();

    void set_state(const string& state);
    string get_state() const;

    void add_player(int id);

    /**
     * @brief Serialize the GameState object to JSON
     *
     * @return JSON object representing the GameState
     */
    json to_json() const;

    /**
     * @brief Deserialize the GameState object from JSON
     *
     * @param j JSON object to deserialize from
     */
    void from_json(const json& j);

   private:
    std::string state =
        "Ready";  ///< current game state: Ready | Game_start | Game_over
    int frame_count = 0;  ///< current frame count
    // float game_remaining_time = 60.0f;  ///< remaining time in the game
    float game_remaining_time =
        config::game_config::GAME_DURATION;  ///< remaining time in the game

    // additional info
    std::string reason = "";  ///< reason for game ending
    int winner_id = -1;       ///< ID of the winning player

    // game objects
    std::vector<Player> players;  ///< list of players
    std::vector<Bullet> bullets;  ///< list of bullets
    std::vector<Enemy> enemies;   ///< list of enemies
};

#endif  // GAME_STATE_HPP