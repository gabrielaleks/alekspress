#include "headers.hpp"
#include <iostream>

namespace http {
    namespace request {
        Headers::Headers(
            std::unordered_map<std::string, std::string> headers
        ) : _headers(std::move(headers)) {
        }

        /**
         * To do: 
         *  - Handle lower and upper casing (headers are case-insensitive)
         *  - Implement validation for required and common headers
         *  - Handle repeated headers: some should be combined, some should remain separate and some should use the last value
         */
        Headers Headers::from_vector(std::vector<std::string> headers_vector) {
            Headers headers;
            std::unordered_map<std::string, std::string> headers_map;
            for (const auto& line : headers_vector) {
                size_t keyEnd = line.find(": ", 0);

                if (keyEnd == std::string::npos) {
                    throw std::invalid_argument("Invalid HTTP header: " + line);
                }

                std::string key = line.substr(0, keyEnd);
                std::string value = line.substr(keyEnd + 2);
                headers_map[key] = value;
            }
            return Headers(headers_map);
        }

        void Headers::printAll() {
            for (const auto& [key, value] : _headers) {
                std::cout << key << ": " << value << std::endl;
            }
        }
    }
}