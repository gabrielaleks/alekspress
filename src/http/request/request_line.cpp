#include "request_line.hpp"
#include <iostream>
#include <exceptions/http_exceptions.hpp>

namespace internal {
    namespace request {
        const std::unordered_set<std::string> RequestLine::SUPPORTED_METHODS = {
            "GET",
            "POST",
            "PUT",
            "PATCH",
            "DELETE",
            "OPTIONS",
            "HEAD"
        };

        const std::unordered_set<std::string> RequestLine::SUPPORTED_HTTP_VERSIONS = {
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
            if (!is_supported_method(_method)) {
                throw exceptions::BadRequestException("Invalid HTTP method: " + std::string(_method));
            }
            if (!is_supported_http_version(_http_version)) {
                throw exceptions::HttpVersionNotSupportedException("HTTP version not supported: " + std::string(_http_version));
            }
        }

        RequestLine RequestLine::from_string(const std::string& request_line_string) {
            if (request_line_string.empty()) {
                throw exceptions::BadRequestException("Request line cannot be empty");
            }

            size_t space_count = std::count(request_line_string.begin(), request_line_string.end(), ' ');
            if (space_count != 2) {
                throw exceptions::BadRequestException("Request line must contain exactly three parts separated by spaces.\nReceived: " + request_line_string);
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
                throw exceptions::BadRequestException("Invalid HTTP request line due to missing elements.\nReceived: " + request_line_string);
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

        bool RequestLine::is_supported_method(const std::string_view& method) {
            return SUPPORTED_METHODS.find(std::string(method)) != SUPPORTED_METHODS.end();
        }

        bool RequestLine::is_supported_http_version(const std::string_view& http_version) {
            return SUPPORTED_HTTP_VERSIONS.find(std::string(http_version)) != SUPPORTED_HTTP_VERSIONS.end();
        }
    } // namespace request
}  // namespace internal