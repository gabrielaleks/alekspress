#include "request_line.hpp"

namespace http {
    namespace request {
        const std::unordered_set<std::string> RequestLine::validMethods = {
            "GET"
        };

        const std::unordered_set<std::string> RequestLine::validHttpVersions = {
            "HTTP/1.1"
        };

        RequestLine::RequestLine(
            std::string method,
            std::string path,
            std::string http_version
        ) : _method(std::move(method)), _path(std::move(path)), _http_version(std::move(http_version)) {
        }

        RequestLine RequestLine::from_string(std::string_view request_line_string) {
            size_t start = 0, end = 0;
            RequestLine request_line;

            // Extract method
            end = request_line_string.find(" ", start);
            if (end == std::string::npos) {
                throw std::invalid_argument("Invalid HTTP request line: missing elements");
            }
            request_line._method = request_line_string.substr(start, end - start);
            start = end + 1;

            // Extract path
            end = request_line_string.find(" ", start);
            if (end == std::string::npos) {
                throw std::invalid_argument("Invalid HTTP request line: missing elements");
            }
            request_line._path = request_line_string.substr(start, end - start);
            start = end + 1;

            // Extract HTTP version
            if (start >= request_line_string.size()) {
                throw std::invalid_argument("Invalid HTTP request line: missing elements");
            }
            request_line._http_version = request_line_string.substr(start);

            // Validations
            if (!is_valid_method(request_line._method)) {
                throw std::invalid_argument("Invalid HTTP method: " + request_line._method);
            }

            if (!is_valid_http_version(request_line._http_version)) {
                throw std::invalid_argument("Invalid HTTP version: " + request_line._http_version);
            }

            return request_line;
        }

        std::string RequestLine::to_string() const {
            return _method + " " + _path + " " + _http_version;
        }

        bool RequestLine::is_valid_method(const std::string_view method) {
            return validMethods.find(std::string(method)) != validMethods.end();
        }

        bool RequestLine::is_valid_http_version(const std::string_view http_version) {
            return validHttpVersions.find(std::string(http_version)) != validHttpVersions.end();
        }
    } // namespace request
}  // namespace http