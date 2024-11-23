#include "request_line.hpp"
#include <iostream>

namespace http {
    namespace request {
        const std::unordered_set<std::string> RequestLine::validMethods = {
            "GET",
            "POST",
            "PUT",
            "PATCH",
            "DELETE",
            "OPTIONS",
            "HEAD"
        };

        const std::unordered_set<std::string> RequestLine::validHttpVersions = {
            "HTTP/1.1"
        };

        RequestLine::RequestLine(
            std::string method,
            std::string path,
            std::string http_version
        ) : _method(std::move(method)), _path(std::move(path)), _http_version(std::move(http_version)) {
            validate();
        }

        void RequestLine::validate() const {
            if (!is_valid_method(_method)) {
                throw std::invalid_argument("Invalid HTTP method: " + std::string(_method));
            }
            if (!is_valid_http_version(_http_version)) {
                throw std::invalid_argument("Invalid HTTP version: " + std::string(_http_version));
            }
        }

        RequestLine RequestLine::from_string(const std::string& request_line_string) {
            if (request_line_string.empty()) {
                throw std::invalid_argument("Request line cannot be empty");
            }

            size_t space_count = std::count(request_line_string.begin(), request_line_string.end(), ' ');
            if (space_count != 2) {
                throw std::invalid_argument("Request line must contain exactly three parts separated by spaces");
            }
            
            size_t start = 0, end = 0;

            // Extract method
            end = request_line_string.find(" ", start);
            std::string method = request_line_string.substr(start, end - start);
            start = end + 1;

            // Extract path
            end = request_line_string.find(" ", start);
            std::string path = request_line_string.substr(start, end - start);
            start = end + 1;

            // Extract HTTP version
            if (start >= request_line_string.size()) {
                throw std::invalid_argument("Invalid HTTP request line: missing elements");
            }
            std::string http_version = request_line_string.substr(start);

            return RequestLine(
                method,
                path,
                http_version
            );
        }

        std::string RequestLine::to_string() const {
            return std::string(_method) + " " + std::string(_path) + " " + std::string(_http_version);
        }

        bool RequestLine::is_valid_method(const std::string_view& method) {
            return validMethods.find(std::string(method)) != validMethods.end();
        }

        bool RequestLine::is_valid_http_version(const std::string_view& http_version) {
            return validHttpVersions.find(std::string(http_version)) != validHttpVersions.end();
        }
    } // namespace request
}  // namespace http