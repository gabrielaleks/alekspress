#include "request_parser.hpp"
#include <iostream>
#include "utils/string_utils.h"

namespace http {
    namespace request {
        void RequestParser::append_to_request(const char* buffer, ssize_t bytes_read) {
            _complete_request.append(buffer, bytes_read);

            if (_complete_request.length() > MAX_REQUEST_SIZE) {
                throw std::length_error("Request exceeded maximum size: " + std::to_string(MAX_REQUEST_SIZE) + " bytes");
                // Could throw specialized exception that returns a 413 content too large
            }

            if (!_is_headers_complete) {
                size_t headers_end = _complete_request.find("\r\n\r\n");

                if (headers_end != std::string::npos) {
                    _is_headers_complete = true;

                    std::string headers_lowercased = utils::StringUtils::to_lowercase(_complete_request);

                    _expected_content_length = parse_content_length(headers_lowercased);

                    if (_expected_content_length > 0) {
                        _method = parse_method(headers_lowercased);
                        if (is_method_without_body(_method)) {
                            throw std::invalid_argument(
                                "Body not allowed in " + utils::StringUtils::to_uppercase(_method) + " request"
                            );
                            // Could throw specialized exception that returns a 400 bad request
                        }
                    }

                    _body_bytes_received = _complete_request.length() - (headers_end + 4);
                }
            } else {
                _body_bytes_received += bytes_read;
            }

            if (_is_headers_complete) {
                if (_expected_content_length > 0) {
                    _is_request_complete = (_body_bytes_received >= _expected_content_length);
                } else {
                    _is_request_complete = true;
                }
            }
        }

        bool RequestParser::is_request_complete() {
            return _is_request_complete;
        }

        bool RequestParser::is_method_without_body(const std::string& method) {
            if (method == "get" || method == "head" || method == "delete") {
                return true;
            }
            return false;
        }

        int RequestParser::parse_content_length(const std::string& headers_lowercased) {
            std::string headers = headers_lowercased.substr(0, headers_lowercased.find("\r\n\r\n"));
            
            std::string to_find = "content-length:";
            size_t content_length_start_position = headers.find(to_find);

            if (content_length_start_position != std::string::npos) {
                content_length_start_position += to_find.length();

                size_t content_length_end_position = headers.find("\r\n", content_length_start_position);

                std::string content_length_str = headers.substr(
                    content_length_start_position,
                    content_length_end_position - content_length_start_position
                );

                try {
                    int content_length = std::stoi(content_length_str);
                    return content_length;
                } catch(const std::exception& e) {
                    return -1;
                }
            }

            return -1;
        }

        std::string RequestParser::parse_method(const std::string& headers_lowercased) {
            size_t method_end = headers_lowercased.find(" ");

            if (method_end == std::string::npos) {
                throw std::invalid_argument("Invalid request: " + headers_lowercased);
            }
            
            std::string method = headers_lowercased.substr(0, method_end);
            return method;
        }
    }
}