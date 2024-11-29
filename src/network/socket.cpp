#include "socket.hpp"
#include <netinet/in.h>  // For sockaddr_in
#include <sys/socket.h>  // For socket functions
#include <unistd.h> // For close

namespace network {
    Socket::Socket(int port) : _port(std::move(port)) {
    }

    Socket::~Socket() {
        if (_sockfd >= 0) {
            close(_sockfd);
        } 
    }
    
    void Socket::create() {
        if ((_sockfd = socket(
            AF_INET, // IPv4
            SOCK_STREAM, // TCP socket type
            0 // Default protocol (TCP for SOCK_STREAM)
        )) < 0) {
            throw std::runtime_error("Could not create socket");
        }

        // Setting SO_REUSEADDR to reuse a local address in case it's in a TIME_WAIT state
        int opt = 1;
        if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            throw std::runtime_error("Could not add SO_REUSEADDR option");
        }
    }

    void Socket::bind() {
        struct sockaddr_in address{
            .sin_family = AF_INET, // IPv4
            .sin_addr.s_addr = INADDR_ANY, // Accept connections from any network interface
            .sin_port = htons(_port) // Port number (htons converts port number from host to network byte order)
        };

        if (::bind(_sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            throw std::runtime_error("Error on binding");
        }
    }

    void Socket::listen() {
        if (::listen(
            _sockfd,
            SOMAXCONN // Backlog size (maximum length of the pending connections queue)
        ) < 0) {
            throw std::runtime_error("Error on listening");
        }
    }

    Connection Socket::accept_connection() const {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);

        // Creates new socket for this client while original socket continues listening for more connections
        int client_socket = accept(_sockfd, (struct sockaddr *)&client_address, &client_len);

        if (client_socket < 0) {
            throw std::runtime_error("Error accepting connection");
        }

        // Setting timeout for client socket
        struct timeval timeout;
        timeout.tv_sec = CLIENT_TIMEOUT_SECONDS;
        timeout.tv_usec = 0;

        if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
            throw std::runtime_error("Failed to set socket timeout");
        }        

        return Connection(
            client_socket,
            client_address
        );
    }
}