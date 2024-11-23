#include <iostream>
#include <http_server/alekspress.hpp>

int main() {
    server::Alekspress app(8080);
    app.run();
}
