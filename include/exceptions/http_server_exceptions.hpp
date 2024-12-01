#pragma once

#include "http_base_exception.hpp"

// 5xx exceptions
namespace exceptions {
    class InternalServerErrorException : public HttpException {
        public:
            InternalServerErrorException(
                const std::string& message = "The server was unable to complete the request"
            ) : HttpException(alekspress::StatusCode::INTERNAL_SERVER_ERROR, message) {}
    };

    class HttpVersionNotSupportedException : public HttpException {
        public:
            HttpVersionNotSupportedException(
                const std::string& message = "HTTP version not supported"
            ) : HttpException(alekspress::StatusCode::HTTP_VERSION_NOT_SUPPORTED, message) {}
    };
}