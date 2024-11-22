#pragma once

#include <string>

namespace http {
    namespace request {
        class Body {
            public:
                Body() = default;

                Body(std::string body);

                std::string content() const { return _body; }

                static Body from_string(const std::string& body_string);
            private:
                std::string _body;
        };
    }
}
