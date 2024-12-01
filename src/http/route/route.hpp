// Public router interface
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <regex>

namespace internal {
    class Route {
        public:
            Route(const std::string& pattern);
            bool matches(const std::string& path) const;
            std::unordered_map<std::string, std::string> extract_params(const std::string& path) const;

        private:
            std::string _pattern; // e.g.: "users/:id"
            std::vector<std::string> _param_names;  // e.g.: ["id"]
            std::regex _regex; // e.g.: "^/users/([^/]+)$"

            void parse_pattern();
    };
}