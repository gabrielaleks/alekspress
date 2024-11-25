#pragma once

#include <string>

namespace internal {
    namespace response {
        class Body {
            public:
                Body() = default;

                Body(std::string body);

                std::string serialize() const { return _body; }
            private:
                std::string _body;
        };
    }
}
