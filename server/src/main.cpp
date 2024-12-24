#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
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

Server* server_ptr = nullptr;

void sigint_handler(int signal) {
    cout << "\n(main thread " << std::this_thread::get_id()
         << ", sigint_handler) Stopping server..." << endl;
    if (server_ptr != nullptr) {
        if (server_ptr->is_running()) {
            server_ptr->stop();
        }
    }
    cout << "\n(main thread " << std::this_thread::get_id()
         << ", sigint_handler) Server stopped." << endl;

    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);

    std::thread::id main_thread_id = std::this_thread::get_id();
    cout << "(main thread " << main_thread_id << ", main) Starting server..."
         << endl;

    Player player = Player(1, 50.0f, 10.0f);
    Enemy enemy = Enemy(10, 10, 1);
    Bullet bullet;
    GameState game_state = GameState();

    Server server(12345);
    server_ptr = &server;
    int ret = server.start();

    if (ret < 0) {
        // cout << "(main thread) Error starting server" << endl;
        cout << "\n(main thread " << main_thread_id << ", main) "
             << "Error starting server" << endl;
        return -1;
    } else {
        // cout << "(main thread) Server started successfully. Press Ctrl+C to "
        //         "stop."
        //      << endl;
        cout << "\n(main thread " << main_thread_id << ", main) "
             << "Server started successfully. Press Ctrl+C to stop." << endl;
        while (server.is_running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    // cout << "Player:" << endl;
    // cout << player.to_json().dump(2) << endl;
    // cout << "\n";

    // cout << "Enemy:" << endl;
    // cout << enemy.to_json().dump(2) << endl;
    // cout << "\n";

    // cout << "Bullet:" << endl;
    // cout << bullet.to_json().dump(2) << endl;
    // cout << "\n";

    // cout << "GameState:" << endl;
    // cout << game_state.to_json().dump(2) << endl;
    // cout << "\n";

    return 0;
}