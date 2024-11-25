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

                std::string serialize();
            private:
                std::unordered_map<std::string, std::string> _headers;

                // void validate() const;
        };
    }
}
