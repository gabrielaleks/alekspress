#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace http {
    namespace request {
        class Headers {
            public:
                Headers() = default;

                Headers(std::unordered_map<std::string, std::string> headers);

                std::unordered_map<std::string, std::string> all() const { return _headers; }
                void print_all();

                static Headers from_vector(std::vector<std::string> headers_vector);
            private:
                std::unordered_map<std::string, std::string> _headers;
        };
    }
}
