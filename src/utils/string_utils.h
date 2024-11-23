#pragma once

#include <string>
#include <iostream>

namespace utils {
    class StringUtils {
        public:
            static std::string to_lowercase(const std::string& str) {
                std::string result = str;
                std::transform(
                    result.begin(),
                    result.end(),
                    result.begin(),
                    [](unsigned char c) { return std::tolower(c); }
                );

                return result;
            }

            static std::string to_uppercase(const std::string& str) {
                std::string result = str;
                std::transform(
                    result.begin(),
                    result.end(),
                    result.begin(),
                    [](unsigned char c) { return std::toupper(c); }
                );

                return result;
            }
    };
}