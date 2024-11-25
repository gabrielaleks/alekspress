#include "status_line.hpp"
#include <iostream>

namespace internal {
    namespace response {
        StatusLine::StatusLine(
            std::string http_version,
            int status_code
        ) : 
            _http_version(std::move(http_version)),
            _status_code(std::move(status_code)) {
        }

        void StatusLine::set_http_version(std::string http_version) {
            _http_version = http_version;
        }

        void StatusLine::set_status_code(int status_code) {
            _status_code = status_code;
        }

        std::string StatusLine::serialize() {
            return _http_version
                + " "
                + std::to_string(_status_code)
                + " "
                + STATUS_TEXTS.at(_status_code)
                + "\r\n";
        }

        const std::unordered_map<int, std::string> StatusLine::STATUS_TEXTS {
            {100, "Continue"},
            {200, "OK"},
            {202, "Accepted"},
        };
    }
}