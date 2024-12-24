
#ifndef SERVER_HPP
#define SERVER_HPP

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

#include "game_state.hpp"

/**
 * @class Server
 * @brief Represents the game server, handling game state updates and player
 * interactions.
 *
 * The Server class manages the game state, updating it based on player
 * interactions and other game events. It also provides functionality to run the
 * game server and update the game state.
 */
class Server {
   public:
    /**
     * @brief Construct a new Server object
     *
     * @param port Port number to listen on
     */
    Server(int port);

    /**
     * @brief Destroy the Server object
     *
     */
    ~Server();

    /**
     * @brief Start the game server
     *
     */
    int start();

    /**
     * @brief Run the game server
     *
     */
    void run();

    /**
     * @brief Stop the game server
     *
     */
    void stop();

    /**
     * @brief Check if the server is running
     *
     * @return true if the server is running, false otherwise
     */
    bool is_running();

    /**
     * @brief Check if the game is running
     *
     * @return true if the game is running, false otherwise
     */
    bool is_game_running();

   private:
    // general server configuration
    int port;                   ///< port number to listen on
    int server_socket;          ///< server socket file descriptor
    std::atomic<bool> running;  ///< flag indicating if the server is running

    // server client data structures
    std::atomic<int> next_client_id{0};  ///< next client ID
    std::mutex server_state_mutex;    ///< mutex for accessing the server state
    std::mutex game_state_mutex;      ///< mutex for accessing the game state
    std::thread server_thread;        ///< thread for running the server
    std::vector<int> client_sockets;  ///< client socket file descriptors
    std::vector<std::thread> client_threads;  ///< threads for handling clients

    GameState game_state;  ///< current game state

    /**
     * @brief Accept incoming client connections
     *
     */
    void accept_clients();

    /**
     * @brief Set up the server socket
     *
     * @return int 0 on success, -1 on failure
     */
    int set_up_socket();

    /**
     * @brief Handle client connections
     *
     * @param client_socket Client socket file descriptor
     */
    void handle_client(int client_socket);

    int create_client_id();
    int send_initial_data(int client_socket, int client_id);
    void create_player(int client_id);

    /**
     * @brief Update the game state
     *
     * @param deltaTime Time since the last update
     */
    void update_game_state(float deltaTime);

    /**
     * @brief Broadcast the current game state to all clients
     *
     */
    void broadcast_game_state();

    /**
     * @brief Close all client connections
     *
     */
    void close_connections();
};

#endif  // SERVER_HPP