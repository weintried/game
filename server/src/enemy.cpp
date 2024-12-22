// File: enemy.cpp

#include "enemy.hpp"

#include <iostream>
using std::cerr;
using std::endl;

Enemy::Enemy(int x, int y, int speed) : x(x), y(y), speed(speed) {}

json Enemy::to_json() const { return json{{"x", x}, {"y", y}}; }

void Enemy::from_json(const json& j) {
    try {
        j.at("x").get_to(x);
        j.at("y").get_to(y);
    } catch (json::exception& e) {
        cerr << "Error parsing Enemy JSON: " << e.what() << endl;
    }
}
