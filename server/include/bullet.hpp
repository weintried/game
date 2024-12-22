/**
 * @file bullet.hpp
 * @author wein
 * @brief Bullet class declaration
 * @version 0.1
 * @date 2024-12-22
 *
 * The Bullet class represents a bullet in the game, handling movement and other
 * bullet-related functionalities.
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef BULLET_HPP
#define BULLET_HPP

#include "nlohmann/json.hpp"
using json = nlohmann::json;

/**
 * @class Bullet
 * @brief Represents a bullet in the game.
 *
 * The Bullet class encapsulates bullet data, including position and movement
 * mechanics. It also provides serialization support through the nlohmann::json
 * library.
 */
class Bullet {
   public:
    /**
     * @brief Construct a new Bullet object
     *
     */
    Bullet() = default;

    void update();

    /**
     * @brief Serialize the Bullet object to JSON
     *
     * @return JSON object representing the Bullet
     */
    json to_json() const;

    /**
     * @brief Deserialize the Bullet object from JSON
     *
     * @param j JSON object to deserialize from
     */
    void from_json(const json& j);

   private:
    int x, y;
    int speed;
};

#endif  // BULLET_HPP