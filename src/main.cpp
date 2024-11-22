#include <arpa/inet.h>   // For inet_addr, inet_ntoa
#include <errno.h>       // For errno and error constants
#include <netinet/in.h>  // For sockaddr_in
#include <string.h>      // For strerror()
#include <sys/socket.h>  // For socket functions
#include <unistd.h>      // For close()

#include <iostream>
#include "http/request/http_request.hpp"
#include "http/request/request_parser.hpp"

// int main() {
//     char buffer[1024] = "GET / HTTP/1.1\r\nHost: localhost:8080\r\nContent-Type: text/plain\r\nContent-Length: 0\r\nUser-Agent: insomnia/10.1.1\r\nAccept: text/html\r\nAccept: application/json\r\n\r\nHelloWorlda  a \r\n!asda asd";

//     http::request::HttpRequest http_request = http::request::HttpRequest::from_char_buffer(buffer);

//     std::cout << "--- HTTP Request Line ---" << std::endl;
//     std::cout << http_request.request_line().method() << std::endl;
//     std::cout << http_request.request_line().path() << std::endl;
//     std::cout << http_request.request_line().http_version() << std::endl;
//     std::cout << "--- HTTP Request Headers ---" << std::endl;
//     std::cout << "Host: " << http_request.headers().host() << std::endl;
//     std::cout << "Content-Length: " << http_request.headers().content_length() << std::endl;
//     std::cout << "Content-Type: " << http_request.headers().content_type() << std::endl;
//     std::cout << "User-Agent: " << http_request.headers().user_agent() << std::endl;
//     std::cout << "Accept: " << http_request.headers().accept() << std::endl;
//     std::cout << "--- HTTP Request Body ---" << std::endl;
//     std::cout << http_request.body().content() << std::endl;
// }

int main() {
    /**
     * Creating a socket file descriptor (sockfd)
     * AF_INET: IPv4 internet protocols
     * SOCK_STREAM: TCP socket type
     * 0: Default protocol (TCP for SOCK_STREAM)
     *
     * The function will return either:
     * - a positive integer on success
     * - -1 on error
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /**
     * Creating a structure to hold the address information.
     * AF_INET: IPv4
     * INADDR_ANY: Accept connections from any network interface
     * htons(8080): Port number (htons converts port number from host to network byte order)
     */
    int port = 8080;
    struct sockaddr_in address{
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(port)};

    /**
     * Binding the socket we just created with the address we want to use
     * We should always check bind()'s return value (-1 indicates error).
     * A common error is "address already in use". Also, ports below 1024 require root privilege.
     */
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Error on binding: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    /**
     * Listening for incoming connections
     * The listen function accepts two parameters:
     * - sockfd: oiur socket file descriptor
     * - The second parameter is the backlog size (maximum length of the pending connections queue)
     */
    if (listen(sockfd, SOMAXCONN) < 0) {
        std::cerr << "Error on listening: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    printf("Now listening on port %d!\n", port);

    while (true) {
        /**
         * Accepting incoming connections
         * accept() creates a new socket specifically for this client
         * The original socket continues listening for more connections
         */
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(sockfd, (struct sockaddr *)&client_address, &client_len);

        // Getting client information from client_address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_address.sin_port);
        printf("New connection from %s:%d\n", client_ip, client_port);

        /**
         * Read data from client
         * read() returns:
         * - number of bytes read.
         * - 0 if client closed connection
         * - -1 on error
         * Also, might not read all data at once. For HTTP, we need to read until we get the complete request
         */
        http::request::RequestParser parser;
        while (true) {
            const int BUFFER_SIZE = 10;
            char buffer[BUFFER_SIZE] = {0};
            ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer));
            // printf("Number of bytes read: %zd\n", bytes_read);
            parser.append_to_request(buffer, bytes_read);
            if (parser.is_request_complete()) {
                break;
            }
        }
        http::request::HttpRequest http_request = http::request::HttpRequest::from_string(parser.complete_request());

        std::cout << "--- HTTP Request Line ---" << std::endl;
        std::cout << http_request.request_line().method() << std::endl;
        std::cout << http_request.request_line().path() << std::endl;
        std::cout << http_request.request_line().http_version() << std::endl;
        std::cout << "--- HTTP Request Headers ---" << std::endl;
        std::cout << "Host: " << http_request.headers().host() << std::endl;
        std::cout << "Content-Length: " << http_request.headers().content_length() << std::endl;
        std::cout << "Content-Type: " << http_request.headers().content_type() << std::endl;
        std::cout << "User-Agent: " << http_request.headers().user_agent() << std::endl;
        std::cout << "Accept: " << http_request.headers().accept() << std::endl;
        std::cout << "--- HTTP Request Body ---" << std::endl;
        std::cout << http_request.body().content() << std::endl;
        
        /**
         * Send response to client
         */
        const char *response = "Hello from server\n";
        write(client_socket, response, strlen(response));

        /**
         * Close client socket
         */
        close(client_socket);
    }
}