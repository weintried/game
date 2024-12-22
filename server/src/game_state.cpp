// File: game_state.cpp

#include <iostream>
using std::cerr;
using std::endl;

#include "game_state.hpp"

void GameState::update() {
    // Update game state logic
    // ...existing code...
}

json GameState::to_json() const {
    if (this->state == "Ready") {
        return json{{"state", "Ready"},
                    {"frameCount", frame_count},
                    {"gameRemainingTime", game_remaining_time}};
    } else if (this->state == "Game_start") {
        return json{{"state", "Game_start"},
                    {"frameCount", frame_count},
                    {"gameRemainingTime", game_remaining_time}};
    } else if (this->state == "Game_over") {
        return json{{"state", "Game_over"},
                    {"frameCount", frame_count},
                    {"gameRemainingTime", game_remaining_time},
                    {"reason", reason}};
    } else {
        return json{{"state", "Unknown"}};
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