#include "connection.hpp"
#include <unistd.h> // For close
#include <arpa/inet.h>   // For inet_addr, inet_ntoa
#include <iostream>

namespace network {
    Connection::Connection(
        int client_socket,
        sockaddr_in client_address
    ) : _client_socket(std::move(client_socket)), _client_address(std::move(client_address)) {
    }

    Connection::~Connection() {
        if (_client_socket >= 0) {
            ::close(_client_socket);
        }
    }

    std::string Connection::ip() const {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &_client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
        return std::string(client_ip);
    }

    int Connection::port() const {
        return ntohs(_client_address.sin_port);
    }

    ssize_t Connection::read(char* buffer, size_t size) {
        return ::read(_client_socket, buffer, size);
    }

    void Connection::write(const char* data, size_t size) {
        if (::write(_client_socket, data, size) < 0) {
            throw std::runtime_error("Could not write data");
        }
    }
}