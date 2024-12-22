// File: player.cpp

#include "player.hpp"

#include <iostream>
using std::cerr;
using std::endl;

Player::Player(int id, float x, float y) : id(id), x(x), y(y) {}

json Player::to_json() const {
    return json{{"id", id},
                {"x", x},
                {"y", y},
                {"isAlive", is_alive},
                {"score", score}};
}

void Player::from_json(const json& j) {
    try {
        j.at("id").get_to(id);
        j.at("x").get_to(x);
        j.at("y").get_to(y);
        j.at("isAlive").get_to(is_alive);
        j.at("score").get_to(score);
    } catch (json::exception& e) {
        cerr << "Error parsing Player JSON: " << e.what() << endl;
    }
}