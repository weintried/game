
#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config {

// server config
namespace server_config {

constexpr int SERVER_PORT = 12345;
constexpr int SOCKET_BACKLOG = 2;
constexpr float TICK_RATE = 32.0f;

constexpr int CLIENT_SOCKET_TIMEOUT_SEC = 0;
constexpr int CLIENT_SOCKET_TIMEOUT_USEC = (int)(1000000.0f / TICK_RATE);

}  // namespace server_config

// game config
namespace game_config {

constexpr int MAX_PLAYERS = 2;
constexpr float GAME_DURATION = 20.0f;

constexpr float PLAYER_SPEED = 5.0f;
constexpr float PLAYER_SIZE = 1.0f;

constexpr float BULLET_SPEED = 10.0f;
constexpr float BULLET_SIZE = 0.5f;

constexpr float ENEMY_SPEED = 2.0f;
constexpr float ENEMY_SIZE = 1.0f;

constexpr float WORLD_SIZE = 100.0f;

constexpr float PLAYER_1_START_X = 10.0f;
constexpr float PLAYER_1_START_Y = 10.0f;
constexpr float PLAYER_2_START_X = 90.0f;
constexpr float PLAYER_2_START_Y = 10.0f;

}  // namespace game_config

}  // namespace config

#endif  // CONFIG_HPP