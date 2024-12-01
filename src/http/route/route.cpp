#include "route.hpp"

namespace internal {
    Route::Route(
        const std::string& pattern
    ) : _pattern(std::move(pattern)) {
        parse_pattern();
    }

    void Route::parse_pattern() {
        std::string regex_pattern = _pattern;
        std::regex param_regex(":[a-zA-Z]+");
        
        // Convert "/users/:id" to "^/users/([^/]+)$" and store parameter names
        std::string::const_iterator search_start(regex_pattern.cbegin());
        std::smatch match;
        while (std::regex_search(search_start, regex_pattern.cend(), match, param_regex)) {
            std::string param_name = match.str().substr(1); // Remove ':'
            _param_names.push_back(param_name);
            
            // Replace :param with regex capture group
            regex_pattern.replace(match.position(), match.length(), "([^/]+)");
            search_start = regex_pattern.cbegin() + match.position() + 7;
        }
        
        _regex = std::regex("^" + regex_pattern + "$");
    }

    bool Route::matches(const std::string& path) const {
        return std::regex_match(path, _regex);
    }

    std::unordered_map<std::string, std::string> Route::extract_params(const std::string& path) const {
        std::unordered_map<std::string, std::string> params;
        std::smatch matches;

        if (std::regex_match(path, matches, _regex)) {
            for (size_t i = 0; i < _param_names.size(); i++) {
                params[_param_names[i]] = matches[i + 1].str();
            }
        }

        return params;
    }
}