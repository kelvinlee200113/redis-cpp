#pragma once

#include <cstdint>

/**
 * Basic TCP Server for Redis-CPP
 * Following the "Build Your Own Redis" tutorial approach
 */
class Server {
public:
    explicit Server(uint16_t port = 6379);
    ~Server();

    // Core server operations
    bool start();        // Create socket, bind, listen
    void run();          // Main server loop - accept and handle connections
    void stop();         // Clean shutdown

private:
    uint16_t port_;
    int fd_;      // Server socket file descriptor
    bool running_;

    // Socket setup and client handling
    bool setup_socket();               // socket() + bind() + listen()
    void handle_client(int client_fd); // Process one client connection
    void cleanup();                    // Clean up resources
};