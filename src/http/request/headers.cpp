#include "headers.hpp"
#include "utils/string_utils.h"
#include <iostream>

namespace http {
    namespace request {
        const std::unordered_set<std::string> Headers::headers_to_combine = {
            "accept",
            "connection"
        };

        const std::unordered_set<std::string> Headers::mandatory_headers {
            "host"
        };
        
        Headers::Headers(
            std::unordered_map<std::string, std::string> headers
        ) : _headers(std::move(headers)) {
            validate();
        }

        void Headers::validate() const {
            for (const auto& mandatory_header : mandatory_headers) {
                if (_headers.find(mandatory_header) == _headers.end()) {
                    throw std::invalid_argument("Missing mandatory header: " + mandatory_header);
                }
            }
        }

        Headers Headers::from_vector(const std::vector<std::string>& headers_vector) {
            if (headers_vector.empty()) {
                throw std::invalid_argument("Headers vector cannot be empty");
            }
            
            Headers headers;
            std::unordered_map<std::string, std::string> headers_map;
            for (const auto& line : headers_vector) {
                size_t keyEnd = line.find(": ");

                if (keyEnd == std::string::npos) {
                    throw std::invalid_argument("Invalid HTTP header: " + line);
                }

                std::string key = utils::StringUtils::to_lowercase(line.substr(0, keyEnd));
                
                std::string value = line.substr(keyEnd + 2);

                // Check for key's existence in map
                if (headers_map.find(key) != headers_map.end()) {
                    // Case 1: comma-separated headers
                    if (Headers::headers_to_combine.find(key) != Headers::headers_to_combine.end()) {
                        value = headers_map[key] + ", " + value;
                    }
                }
                headers_map[std::move(key)] = std::move(value);
            }

            return Headers(headers_map);
        }

        void Headers::print_all() {
            for (const auto& [key, value] : _headers) {
                std::cout << key << ": " << value << std::endl;
            }
        }

        std::string Headers::get_header(const std::string &header) const {
            auto it = _headers.find(utils::StringUtils::to_lowercase(header));
            return it != _headers.end() ? it->second : "";
        }

        std::string Headers::host() const {
            return get_header("host");
        }

        std::string Headers::content_length() const {
            return get_header("content-length");
        }

        std::string Headers::content_type() const {
            return get_header("content-type");
        }

        std::string Headers::user_agent() const {
            return get_header("user-agent");
        }

        std::string Headers::accept() const {
            return get_header("accept");
        }
    }
}