/**
 * @file player.hpp
 * @author wein
 * @brief Player class declaration
 *
 * The Player class represents an in-game player, handling movement,
 * shooting, and other player-related functionalities.
 *
 * @version 0.1
 * @date 2024-12-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "nlohmann/json.hpp"
using json = nlohmann::json;

/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * The Player class encapsulates player data, including position, score, and
 * movement/shooting mechanics. It also provides serialization support through
 * the nlohmann::json library.
 */
class Player {
   public:
    /**
     * @brief Construct a new Player object
     *
     * @param id unique player ID
     * @param x player position on the screen
     * @param y player position on the screen
     */
    Player(int id = 0, float x = 0.0f, float y = 0.0f);

    void moveLeft();
    void moveRight();

    /**
     * @brief Serialize the Player object to JSON
     *
     * @return JSON object representing the Player
     */
    json to_json() const;

    /**
     * @brief Deserialize the Player object from JSON
     *
     * @param j JSON object to deserialize from
     */
    void from_json(const json& j);

   private:
    int id;                ///< unique player ID
    float x, y;            ///< player position on the screen
    bool is_alive = true;  ///< player's life status
    int score = 0;         ///< player's current score

    float speed = 5.0f;  ///< player movement speed

    float bullet_cooldown_time = 0.0f;  ///< time since last bullet shot
    float bullet_cooldown = 0.5f;       ///< time between bullets
    bool can_shoot = true;              ///< player can shoot
};

#endif  // PLAYER_HPP