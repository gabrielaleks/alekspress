#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace internal {
    namespace response {
        class Headers {
            public:
                Headers() = default;

                void add(const std::string& key, const std::string& value);

                void add_default_headers(size_t body_length);

                std::string serialize();
            private:
                std::unordered_map<std::string, std::string> _headers;

                std::string const SERVER_NAME_AND_VERSION = "Alekspress/1.0";

                std::string get_http_date();
                // void validate() const;
        };
    }
}
