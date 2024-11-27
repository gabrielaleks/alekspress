#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace internal {
    namespace request {
        class Headers {
            public:
                Headers() = default;

                Headers(std::unordered_map<std::string, std::string> headers);

                std::unordered_map<std::string, std::string> all() const { return _headers; }

                std::string get_header(const std::string &header) const;

                std::string host() const;
                std::string content_length() const;
                std::string content_type() const;
                std::string user_agent() const;
                std::string accept() const;
                
                void print_all();

                static Headers from_vector(const std::vector<std::string>& headers_vector);
            private:
                std::unordered_map<std::string, std::string> _headers;

                static const std::unordered_set<std::string> HEADERS_TO_COMBINE;
                static const std::unordered_set<std::string> MANDATORY_HEADERS;

                void validate() const;
        };
    }
}
