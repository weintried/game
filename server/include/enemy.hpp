/**
 * @file enemy.hpp
 * @author wein
 * @brief Enemy class declaration
 *
 * The Enemy class represents an in-game enemy, handling movement and other
 * enemy-related functionalities.
 *
 * @version 0.1
 * @date 2024-12-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "nlohmann/json.hpp"
using json = nlohmann::json;

/**
 * @class Enemy
 * @brief Represents an enemy in the game.
 *
 * The Enemy class encapsulates enemy data, including position and movement
 * mechanics. It also provides serialization support through the nlohmann::json
 * library.
 */
class Enemy {
   public:
    /**
     * @brief Construct a new Enemy object
     *
     * @param x enemy position on the screen
     * @param y enemy position on the screen
     * @param speed enemy movement speed
     */
    Enemy(int x = 0, int y = 0, int speed = 1);

    void update();

    /**
     * @brief Serialize the Enemy object to JSON
     *
     * @return JSON object representing the Enemy
     */
    json to_json() const;

    /**
     * @brief Deserialize the Enemy object from JSON
     *
     * @param j JSON object to deserialize from
     */
    void from_json(const json& j);

   private:
    int x, y;   ///< enemy position on the screen
    int speed;  ///< enemy movement speed
};

#endif  // ENEMY_HPP