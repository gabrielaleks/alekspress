#include "headers.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

namespace internal {
    namespace response {
        void Headers::add(const std::string& key, const std::string& value) {
            _headers[key] = value;
        }

        void Headers::add_default_headers(size_t body_length) {
            add("Server", SERVER_NAME_AND_VERSION);
            add("Date", get_http_date());
            add("Content-Length", std::to_string(body_length));
            add("Content-Type", "Content-Type: text/plain; charset=utf-8");
            add("Connection", "keep-alive");
        }

        std::string Headers::get_http_date() {
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::tm gmt = *std::gmtime(&now_time);

            std::ostringstream date_stream;
            date_stream << std::put_time(&gmt, "%a, %d %b %Y %H:%M:%S GMT");
            return date_stream.str();
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