#pragma once

#include <string>
#include <unordered_map>

namespace internal {
    namespace response {
        class StatusLine {
            public:
                StatusLine() = default;

                StatusLine(std::string http_version, int status_code);

                std::string http_version() const { return _http_version; }
                int status_code() const { return _status_code; }

                void set_http_version(std::string http_version);
                void set_status_code(int status_code);

                static const std::string& get_status_text_from_status_code(int code);

                std::string serialize();

                static constexpr std::string DEFAULT_HTTP_VERSION = "HTTP/1.1";
            private:
                std::string _http_version;
                int _status_code;
                static const std::unordered_map<int, std::string> STATUS_TEXTS;
        };
    }
}
