// File: bullet.cpp

#include <iostream>
using std::cerr;
using std::endl;

#include "bullet.hpp"

void Bullet::update() {
    // Update bullet position
    // ...existing code...
}

json Bullet::to_json() const { return json{{"x", x}, {"y", y}}; }

void Bullet::from_json(const json& j) {
    try {
        j.at("x").get_to(x);
        j.at("y").get_to(y);
    } catch (json::exception& e) {
        cerr << "Error parsing Bullet JSON: " << e.what() << endl;
    }
}
