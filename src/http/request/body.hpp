#ifndef BODY_HPP
#define BODY_HPP

#include <string>

namespace http {
    namespace request {
        class Body {
            public:
                Body() = default;

                Body(std::string body);

                std::string content() const { return _body; }

                static Body from_string(std::string body_string);
            private:
                std::string _body;
        };
    }
}

#endif