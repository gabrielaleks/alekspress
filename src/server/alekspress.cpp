#include <http_server/alekspress.hpp>
#include <http_server/request.hpp>
#include <exceptions/http_exceptions.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

#include "http/request/request.hpp"
#include "http/response/response.hpp"
#include "http/response/status_line.hpp"
#include "http/response/headers.hpp"
#include "http/response/body.hpp"

namespace alekspress {
    Alekspress::Alekspress(int port) : _port(std::move(port)), _socket(std::move(_port)) {
    }

    void Alekspress::get(const std::string& path, HandlerFunction handler) {
        _handlers["GET"].push_back({internal::Route(path), handler});
    }

    void Alekspress::post(const std::string& path, HandlerFunction handler) {
        _handlers["POST"].push_back({internal::Route(path), handler});
    }

    void Alekspress::put(const std::string& path, HandlerFunction handler) {
        _handlers["PUT"].push_back({internal::Route(path), handler});
    }

    void Alekspress::patch(const std::string& path, HandlerFunction handler) {
        _handlers["PATCH"].push_back({internal::Route(path), handler});
    }

    void Alekspress::del(const std::string& path, HandlerFunction handler) {
        _handlers["DELETE"].push_back({internal::Route(path), handler});
    }

    void Alekspress::options(const std::string& path, HandlerFunction handler) {
        _handlers["OPTIONS"].push_back({internal::Route(path), handler});
    }

    void Alekspress::head(const std::string& path, HandlerFunction handler) {
        _handlers["HEAD"].push_back({internal::Route(path), handler});
    }

    std::pair<HandlerFunction, std::unordered_map<std::string, std::string>> Alekspress::find_handler(
        const std::string& method,
        const std::string& path
    ) {
        for (const auto& route_handler : _handlers[method]) {
            if (route_handler.route.matches(path)) {
                auto params = route_handler.route.extract_params(path);
                return {route_handler.handler, params};
            }
        }
        return {};
    }

    void Alekspress::handle_connections() {
        auto connection = _socket.accept_connection();

        try {
            Parser parser;
            while (true) {
                char buffer[Parser::READ_BUFFER_SIZE] = {0};
                ssize_t bytes_read = connection.read(buffer, sizeof(buffer));

                // Check for error on read()
                if (bytes_read < 0) {
                    // Check for timeout
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        throw exceptions::RequestTimeoutException("Socket read timeout");
                        // Could also include Connection: close header
                    } else {
                        throw exceptions::InternalServerErrorException("Socket read failed");
                    }
                } else if (bytes_read == 0) {
                    throw exceptions::BadRequestException("Client closed the connection prematurely");
                }

                parser.append_to_request(buffer, bytes_read);
                if (parser.is_request_complete()) {
                    break;
                }
            }
            auto raw_request = RawRequest::from_string(parser.complete_request());

            auto [handler, params] = find_handler(
                raw_request.request_line().method(),
                raw_request.request_line().path()
            );

            if (!handler) {
                throw exceptions::NotFoundException("Requested resource not found: " + raw_request.request_line().path());
            }

            // FROM raw request TO user request
            UserRequest user_request = UserRequest::from_raw_request(raw_request, params);

            // Execute handler with user request, generating user response
            UserResponse user_response = handler(user_request);
            
            // FROM user response TO raw response
            RawResponse raw_response = RawResponse::from_user_response(user_response);

            // Serialize raw response and write it
            std::string raw_response_serialized = raw_response.serialize();
            connection.write(raw_response_serialized.c_str(), raw_response_serialized.length());
        } catch (exceptions::HttpException& e) {
            // Add logging feature
            // Maybe add config allowing user to choose path to which save the logs?
            // std::cout << "[" << e.status_code() << "]" << ": " << e.message() << std::endl;

            RawResponse raw_response = RawResponse::from_exception(e);
            std::string raw_response_serialized = raw_response.serialize();
            connection.write(raw_response_serialized.c_str(), raw_response_serialized.length());
        }
    }

    void Alekspress::run() {
        _socket.create();
        _socket.bind();
        _socket.listen();
        printf("Server running on port %d!\n", _port);

        while (true) {
            handle_connections();
        }
    }
}