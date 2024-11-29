#pragma once

#include "http_base_exception.hpp"

// 4xx exceptions 
namespace exceptions {
    class BadRequestException : public HttpException {
        public:
            BadRequestException(
                const std::string& message = "Bad request"
            ) : HttpException(alekspress::StatusCode::BAD_REQUEST, message) {}
    };
    
    class NotFoundException : public HttpException {
        public:
            NotFoundException(
                const std::string& message = "Resource not found"
            ) : HttpException(alekspress::StatusCode::NOT_FOUND, message) {}
    };
    
    class RequestTimeoutException : public HttpException {
        public:
            RequestTimeoutException(
                const std::string& message = "Request timeout"
            ) : HttpException(alekspress::StatusCode::REQUEST_TIMEOUT, message) {}
    };
    
    class LengthRequiredException : public HttpException {
        public:
            LengthRequiredException(
                const std::string& message = "Content-Length required"
            ) : HttpException(alekspress::StatusCode::LENGTH_REQUIRED, message) {}
    };
    
    class ContentTooLargeException : public HttpException {
        public:
            ContentTooLargeException(
                const std::string& message = "Content too large"
            ) : HttpException(alekspress::StatusCode::CONTENT_TOO_LARGE, message) {}
    };
}