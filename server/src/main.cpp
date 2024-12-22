#include <iostream>
using std::cout;

#include <box2d/box2d.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "server.hpp"

int main() {
    cout << "Starting server..." << std::endl;

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    cout << gravity.x << " " << gravity.y << std::endl;

    json j;
    j["pi"] = 3.141;
    cout << j << std::endl;
    cout << j["pi"] << std::endl;
    j["new"]["key"] = {"value", "another value"};
    cout << j.dump(4) << std::endl;

    Server server;
    server.start();
    // ...existing code...
    server.stop();
    return 0;
}