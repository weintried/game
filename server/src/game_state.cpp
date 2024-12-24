// File: game_state.cpp

#include <iostream>
using std::cerr;
using std::endl;

#include "game_state.hpp"

void GameState::update() {
    // Update game state logic
}

void GameState::set_state(const string& state) { this->state = state; }
string GameState::get_state() const { return this->state; }

void GameState::add_player(int id) {
    // Add a player to the game
    switch (id) {
        case 1:
            this->players.emplace_back(
                Player(1, config::game_config::PLAYER_1_START_X,
                       config::game_config::PLAYER_1_START_Y));
            break;
        case 2:
            this->players.emplace_back(
                Player(2, config::game_config::PLAYER_2_START_X,
                       config::game_config::PLAYER_2_START_Y));
            break;
        default:
            cerr << "Invalid player ID: " << id << endl;
            break;
    }
}

json GameState::to_json() const {
    if (this->state == "Ready") {
        return json{{"game_state", "Ready"},
                    {"frameCount", frame_count},
                    {"gameRemainingTime", game_remaining_time}};
    } else if (this->state == "Game_start") {
        return json{{"game_state", "Game_start"},
                    {"frameCount", frame_count},
                    {"gameRemainingTime", game_remaining_time}};
    } else if (this->state == "Game_over") {
        return json{{"game_state", "Game_over"},
                    {"frameCount", frame_count},
                    {"gameRemainingTime", game_remaining_time},
                    {"reason", reason}};
    } else {
        return json{{"game_state", "Unknown"}};
    }
}

void GameState::from_json(const json& j) {
    try {
        j.at("state").get_to(state);
        j.at("frameCount").get_to(frame_count);
        j.at("gameRemainingTime").get_to(game_remaining_time);
        j.at("reason").get_to(reason);
    } catch (json::exception& e) {
        cerr << "Error parsing GameState JSON: " << e.what() << endl;
    }
}