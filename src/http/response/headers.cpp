#include "headers.hpp"

namespace internal {
    namespace response {
        void Headers::add(const std::string& key, const std::string& value) {
            _headers[key] = value;
        }

        std::string Headers::serialize() {
            std::string headers_string;
            for (const auto& [key, value] : _headers) {
                headers_string.append(key + ": " + value + "\r\n");
            }
            return headers_string;
        }
    }
}