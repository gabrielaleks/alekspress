#pragma once

#include <string>
#include <iostream>

namespace utils {
    class StringUtils {
        public:
            static std::string to_lowercase(std::string& str) {
                std::transform(
                    str.begin(),
                    str.end(),
                    str.begin(),
                    [](unsigned char c) { return std::tolower(c); }
                );

                return str;
            }
    };
}