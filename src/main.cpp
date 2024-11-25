#include <iostream>
#include <http_server/alekspress.hpp>

int main() {
    alekspress::Alekspress app(8080);

    app.get("/hello", [](const alekspress::Request&) -> alekspress::Response {
        return alekspress::Response::ok("Hello world!");
    });

    app.post("/", [](const alekspress::Request& req) -> alekspress::Response {
        alekspress::Response resp;

        resp.set_body(req.body());

        return resp;
    });

    app.run();
}
