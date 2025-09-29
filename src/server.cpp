#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>


Server::Server(uint16_t port) : port_(port), fd_(-1), running_(false) {
    std::cout << "Server created for port " << port_ << std::endl;
}

Server::~Server() {
    stop(); 
}

bool Server::start() {
    std::cout << "Starting server on port " << port_ << std::endl;

    if (!setup_socket()) {
        return false;
    }

    running_ = true;
    std::cout << "Server started successfully on port " << port_ << std::endl;
    return true;
}

bool Server::setup_socket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return false;
    }
    std::cout << "Socket created (fd: " << fd_ << ")" << std::endl;

    // Allow socket reuse
    int opt = 1;
    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket reuse: " << strerror(errno) << std::endl;
        cleanup();
        return false;
    }

    // Setup server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_port = htons(port_);      // Convert port to network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept from any IP (0.0.0.0)
    
    // Bind socket to address
    if (bind(fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket: " << strerror(errno) << std::endl;
        cleanup();
        return false;
    }
    std::cout << "Socket bound to port " << port_ << std::endl;
    
    // Start listening for connections
    if (listen(fd_, 10) < 0) {
        std::cerr << "Failed to listen for connections: " << std::endl;
        cleanup();
        return false;
    }
    std::cout << "Server listening for connections on port " << port_ << std::endl;
    
    return true;
}

void Server::cleanup() {
    if (fd_ >= 0) {
        close(fd_);
        fd_ = -1;
        std::cout << "Socket closed" << std::endl;
    }
}

void Server::stop() {
    if (running_) {
        std::cout << "Stopping server..." << std::endl;
        running_ = false;
    } 
    cleanup();
}

void Server::run() {
    if (!running_) {
        std::cerr << "Server is not running" << std::endl;
        return;
    }

    std::cout << "Server running. Listening for connections... (Press Ctrl+C to stop)" << std::endl;

    // Main event loop - accept and handle single client connection
    while (running_) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Accept client connection (blocking)
        int client_fd = accept(fd_, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "Failed to accept client connection: " << strerror(errno) << std::endl;
            continue;
        }

        std::cout << "Accepted client connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
        
        // Handle client connection
        handle_client(client_fd);

        // close client connection
        close(client_fd);
        std::cout << "Client connection closed" << std::endl;
    }
}

void Server::handle_client(int client_fd) {
    // For now, just echo what the client sends back to them
    // This is the basic functionality we'll expand on later
    std::cout << "Handling client connection..." << std::endl;

    char buffer[1024];
    while (true) {
        // Read data from client
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0) {
            // Client disconnected or error
            break;
        } 

        buffer[bytes_read] = '\0';
        std::cout << "Received from client: " << buffer << std::endl;

        // Echo back to client
        if (write(client_fd, buffer, bytes_read) <= 0) {
            std::cerr << "Failed to send data to client" << std::endl;
            break;
        }
    }
}