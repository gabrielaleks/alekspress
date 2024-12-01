#pragma once

#include <stdexcept>
#include <string>
#include <http_server/status_code.hpp>

namespace exceptions {
    class HttpException : public std::runtime_error {
        private:
            int _status_code;
            std::string _message;

        public:
            HttpException(
                int status_code,
                const std::string& message
            ) : 
                std::runtime_error(message),
                _status_code(std::move(status_code)),
                _message(std::move(message)) {}

            int status_code() const { return _status_code; }
            const std::string& message() const { return _message; }

    };
}