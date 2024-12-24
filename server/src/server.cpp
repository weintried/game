// File: server.cpp
#include <iostream>

#include "game_state.hpp"
using std::cerr;
using std::cout;
using std::endl;

#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include <chrono>
#include <nlohmann/json.hpp>
#include <thread>
using json = nlohmann::json;

#include "config.hpp"
#include "server.hpp"

Server::Server(int port) : port(port), server_socket(-1), running(false) {
    // Initialize the game state
    // game_state = GameState();
    GameState game_state;

    // cout << "Server created with port " << port << endl;
    cout << "\n(main thread " << std::this_thread::get_id()
         << ", Server::Server) Server created with port " << port << endl;
}

Server::~Server() {
    // Stop the server
    this->stop();
    // cout << "Server stopped and resources cleaned up." << endl;
    cout << "\n(main thread " << std::this_thread::get_id()
         << ", Server::~Server) Server stopped and resources cleaned up."
         << endl;
}

int Server::start() {
    // Set the running flag to true
    this->running = true;
    // cout << "Starting server on port " << port << "..." << endl;
    cout << "\n(main thread " << std::this_thread::get_id()
         << ", Server::start) Starting server on port " << port << "..."
         << endl;

    // Create the server socket
    if (this->set_up_socket() < 0) {
        // cerr << "Error setting up server socket" << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::start) Error setting up server socket" << endl;
        this->stop();
        return -1;
    }
    // cout << "Server successfully started on socket " << server_socket <<
    // endl;
    cout << "(main thread " << std::this_thread::get_id()
         << ", Server::start) Server successfully started on socket "
         << server_socket << endl;

    // sleep for a bit
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Start the server thread
    // cout << "Starting server thread..." << endl;
    cout << "(main thread " << std::this_thread::get_id()
         << ", Server::start) Starting server thread..." << endl;
    try {
        this->server_thread = std::thread(&Server::accept_clients, this);
    } catch (std::exception &e) {
        // cerr << "Error starting server thread:\n\n" << e.what() << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::start) Error starting server thread:\n\n"
             << e.what() << endl;
        this->stop();
        return -1;
    } catch (...) {
        // cerr << "Unknown exception in server thread creation." << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::start) Unknown exception in server thread creation."
             << endl;
        this->stop();
        return -1;
    }

    return 0;
}

void Server::run() {
    // cout << "Running the game server..." << endl;
    cout << "\n(main thread " << std::this_thread::get_id()
         << ", Server::run) Running the game server..." << endl;

    while (this->running)
        ;  // FIXME: this is a temporary block to keep the server running

    // // Set the game state to "Game_start"
    // game_state.set_state("Game_start");

    // // cout << "Game started!" << endl;
    // cout << "(main thread " << std::this_thread::get_id()
    //      << ", Server::run) Game started!" << endl;

    // // Main game loop
    // while (this->running) {
    //     // cout << "Game running..." << endl;
    //     cout << "(main thread " << std::this_thread::get_id()
    //          << ", Server::run) Game running..." << endl;

    //     // Sleep for a bit
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // }
}

int Server::set_up_socket() {
    // Create the server socket
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_socket < 0) {
        // cerr << "Error creating server socket" << endl;
        cerr << "\n(main thread " << std::this_thread::get_id()
             << ", Server::set_up_socket) Error creating server socket" << endl;
        return -1;
    }

    // Bind the server socket to the port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    if (bind(this->server_socket, (struct sockaddr *)&server_address,
             sizeof(server_address)) < 0) {
        // cerr << "Error binding server socket" << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::set_up_socket) Error binding server socket" << endl;
        close(this->server_socket);
        return -1;
    }

    // configure the server socket to allow reuse of the address
    int opt = 1;
    // setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
    // sizeof(opt));
    if (setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
                   sizeof(opt)) < 0) {
        // cerr << "Error setting socket options" << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::set_up_socket) Error setting socket options" << endl;
        close(this->server_socket);
        return -1;
    }

    // configure the server socket to timeout after a certain period, so that it
    // won't block forever, especially when waiting for clients but sigint is
    // received
    struct timeval timeout;
    timeout.tv_sec = config::server_config::CLIENT_SOCKET_TIMEOUT_SEC;
    timeout.tv_usec = config::server_config::CLIENT_SOCKET_TIMEOUT_USEC;
    if (setsockopt(this->server_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                   sizeof(timeout)) < 0) {
        // cerr << "Error setting socket options" << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::set_up_socket) Error setting socket options" << endl;
        close(this->server_socket);
        return -1;
    }

    // Listen for incoming connections,
    // this is a 1v2 game, so we only need to listen for 2 clients
    if (listen(this->server_socket, config::server_config::SOCKET_BACKLOG) <
        0) {
        // cerr << "Error listening on server socket" << endl;
        cerr << "(main thread " << std::this_thread::get_id()
             << ", Server::set_up_socket) Error listening on server socket"
             << endl;
        close(this->server_socket);
        return -1;
    }

    return 0;
}

void Server::accept_clients() {
    std::thread::id this_id = std::this_thread::get_id();
    // cout << "\n\nWaiting for clients to connect..." << endl;
    cout << "\n(server thread " << this_id
         << ", Server::accept_clients) Waiting for clients to connect..."
         << endl;

    // Accept incoming client connections
    while (this->running) {
        if (game_state.get_state() == "Game_start") {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);

        int clientSocket =
            accept(this->server_socket, (sockaddr *)&clientAddr, &clientSize);

        if (clientSocket == -1) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                // just timeout, no big deal
                // cout << "boo" << endl;
            } else {
                cerr << "(server thread " << this_id
                     << ", Server::accept_clients) Error accepting client "
                        "connection"
                     << endl;
            }
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(server_state_mutex);
            client_sockets.push_back(clientSocket);
        }

        // cout << "Client connected on socket " << clientSocket << endl;
        // cout << "Current number of clients: " << client_sockets.size() <<
        // endl;
        // cout << "(server thread " << this_id << ") "
        //      << "Client connected on socket " << clientSocket << endl;
        // cout << "(server thread " << this_id << ") "
        //      << "Current number of clients: " << client_sockets.size() <<
        //      endl;
        cout << "(server thread " << this_id << ", Server::accept_clients) "
             << "Client connected on socket " << clientSocket << endl;
        cout << "(server thread " << this_id << ", Server::accept_clients) "
             << "Current number of clients: " << client_sockets.size() << endl;

        this->client_threads.emplace_back(&Server::handle_client, this,
                                          clientSocket);

        if (client_sockets.size() >= config::game_config::MAX_PLAYERS) {
            // cout << "All players connected. Game ready to start!" << endl;
            cout << "(server thread " << this_id
                 << ", Server::accept_clients) All players connected. Game "
                    "ready to start!"
                 << endl;

            // TODO: should I start the game here?
            // game_state.set_state("Game_start");

            this->run();
        }
    }
}

void Server::handle_client(int client_socket) {
    // FIXME: quick and dirty way to manage client connections
    // I should probably split read/write into separate threads...

    std::thread::id this_id = std::this_thread::get_id();
    cout << "\n(client thread " << this_id
         << ", Server::handle_client) Handling client connection on socket "
         << client_socket << endl;

    // set up the client socket
    struct timeval timeout;
    timeout.tv_sec = config::server_config::CLIENT_SOCKET_TIMEOUT_SEC;
    timeout.tv_usec = config::server_config::CLIENT_SOCKET_TIMEOUT_USEC;
    if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                   sizeof(timeout)) < 0) {
        // cerr << "Error setting client socket options" << endl;
        cerr << "(client thread " << this_id
             << ", Server::handle_client) Error setting client socket options"
             << endl;
        return;
    }

    // Send the client its ID
    int client_id = this->create_client_id();
    // cout << "(Client on socket " << client_socket
    //      << ") Assigned ID: " << client_id << endl;
    cout << "(client thread " << this_id
         << ", Server::handle_client) Assigned ID: " << client_id << endl;

    // Send the client its initial data
    if (this->send_initial_data(client_socket, client_id) < 0) {
        // cerr << "Error sending initial data to client" << endl;
        cerr << "(client thread " << this_id
             << ", Server::handle_client) Error sending initial data to client"
             << endl;
        return;
    }

    // Create the player
    this->create_player(client_id);

    // Main client loop
    // cout << "(Client on socket " << client_socket << " , ID " << client_id
    //      << ") waiting for game to start..." << endl;
    cout << "(client thread " << this_id << ", Server::handle_client) "
         << "(client ID " << client_id << ") "
         << "waiting for game to start..." << endl;
    // while (this->game_state.get_state() != "Game_start") {
    while (this->running && this->game_state.get_state() != "Game_start") {
        // Sleep for a bit
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // cout << "(Client on socket " << client_socket << " , ID " << client_id
    //      << ") game started!" << endl;
    cout << "(client thread " << this_id << ", Server::handle_client) "
         << "(client ID " << client_id << ") "
         << "game started!" << endl;
    // while (this->game_state.get_state() == "Game_start") {
    while (this->running && this->game_state.get_state() == "Game_start") {
        // Receive data from the client
        char buffer[1024] = {0};
        int valread = recv(client_socket, buffer, 1024, 0);
        if (valread < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                // basically no input from client, which is fine
            } else {
                // cerr << "Error receiving data from client" << endl;
                cerr << "(client thread " << this_id
                     << ", Server::handle_client) Error receiving data from "
                        "client"
                     << endl;
                break;
            }
        } else {
            // Parse the received data
            json data;
            try {
                data = json::parse(buffer);
            } catch (json::exception &e) {
                // cerr << "Error parsing JSON data: " << e.what() << endl;
                cerr << "(client thread " << this_id
                     << ", Server::handle_client) Error parsing JSON data: "
                     << e.what() << endl;
                break;
            }

            // Process the received data
            // TODO: somehow update the player's position, maybe write
            // another member function in GameState to do this?
        }

        // Send the updated game state to the client
        std::string game_state_str = game_state.to_json().dump();
        if (send(client_socket, game_state_str.c_str(), game_state_str.length(),
                 0) < 0) {
            // cerr << "Error sending game state to client" << endl;
            cerr
                << "(client thread " << this_id
                << ", Server::handle_client) Error sending game state to client"
                << endl;
            break;
        }

        // // Sleep for a bit
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // nope, just keep looping
    }
}

int Server::create_client_id() {
    // return this->next_client_id++;
    return this->next_client_id++ % config::game_config::MAX_PLAYERS + 1;
}

int Server::send_initial_data(int client_socket, int client_id) {
    // FIXME: this is ugly as fuuuuuuuuuuck
    json initial_data = {{"game_state", "Ready"},
                         {"players",
                          {
                              {"id", 0},
                              {"x", 0.0f},
                              {"y", 0.0f},
                              {"isAlive", true},
                              {"score", 0},
                          }}};

    switch (client_id) {
        case 1:
            initial_data["players"]["id"] = 1;
            initial_data["players"]["x"] =
                config::game_config::PLAYER_1_START_X;
            initial_data["players"]["y"] =
                config::game_config::PLAYER_1_START_Y;
            break;
        case 2:
            initial_data["players"]["id"] = 2;
            initial_data["players"]["x"] =
                config::game_config::PLAYER_2_START_X;
            initial_data["players"]["y"] =
                config::game_config::PLAYER_2_START_Y;
            break;
        default:
            cerr << "Invalid client ID: " << client_id << endl;
            return -1;
    }

    // Send the initial data to the client
    std::string initial_data_str = initial_data.dump();
    if (send(client_socket, initial_data_str.c_str(), initial_data_str.length(),
             0) < 0) {
        cerr << "Error sending initial data to client" << endl;
        return -1;
    }

    return 0;
}

void Server::create_player(int client_id) {
    this->game_state.add_player(client_id);
}

void Server::stop() {
    cout << "\n(??? thread " << std::this_thread::get_id()
         << ", Server::stop) Stopping server..." << endl;

    this->running = false;  // Ensure the server loop exits

    if (server_thread.joinable()) {
        // cout << "Joining server thread..." << endl;
        cout << "\n(??? thread " << std::this_thread::get_id()
             << ", Server::stop) Joining server thread..." << endl;
        server_thread.join();  // Wait for the thread to finish
    }

    for (auto &thread : this->client_threads) {
        if (thread.joinable()) {
            // cout << "Joining client thread..." << endl;
            cout << "\n(??? thread " << std::this_thread::get_id()
                 << ", Server::stop) Joining client thread " << thread.get_id()
                 << "..." << endl;
            thread.join();  // Wait for the thread to finish
        }
    }

    if (server_socket != -1) {
        // cout << "Cleaning up server resources..." << endl;
        cout << "\n(??? thread " << std::this_thread::get_id()
             << ", Server::stop) Cleaning up server resources..." << endl;
        close(server_socket);  // Close the server socket
    }
}

bool Server::is_running() { return this->running; }
