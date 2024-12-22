#include <iostream>
using std::cout;
using std::endl;

#include <box2d/box2d.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "bullet.hpp"
#include "enemy.hpp"
#include "game_state.hpp"
#include "player.hpp"
#include "server.hpp"

int main() {
    cout << "Starting server..." << std::endl;

    Player player = Player(1, 50.0f, 10.0f);
    Enemy enemy = Enemy(10, 10, 1);
    Bullet bullet;
    GameState game_state = GameState();

    Server server;

    json some_json;

    cout << "Player:" << endl;
    cout << player.to_json().dump(2) << endl;
    cout << "\n";

    cout << "Enemy:" << endl;
    cout << enemy.to_json().dump(2) << endl;
    cout << "\n";

    cout << "Bullet:" << endl;
    cout << bullet.to_json().dump(2) << endl;
    cout << "\n";

    cout << "GameState:" << endl;
    cout << game_state.to_json().dump(2) << endl;
    cout << "\n";

    return 0;
}