#include "common.hpp"
#include "../include/messages_service.hpp"

std::string get_message(){
    return PHONY;
}

void handle_get_request(const httplib::Request& req, httplib::Response& res) {
#ifdef MESSAGE_SERVICE_LOGS_ENABLED
    std::cout << "Got GET request!" << std::endl;
#endif
    res.set_content(get_message(), "text/plain");
}

void handle_post_request(const httplib::Request& req, httplib::Response& res) {
#ifdef MESSAGE_SERVICE_LOGS_ENABLED
    std::cout << "Got POST request!" << std::endl;
#endif
}

void handle_request(const httplib::Request& req, httplib::Response& res) {
    if (req.method == "GET" && req.path == "/messages_service") {
        handle_get_request(req, res);
    } else if (req.method == "POST" && req.path == "/messages_service") {
        handle_post_request(req, res);
    } else {
        res.status = NOT_FOUND_STATUS;
    }
}

int main() {
    httplib::Server server;

    server.Get("/messages_service", handle_request);
    server.Post("/messages_service", handle_request);

    std::cout << "Starting messages service!" << std::endl;

    server.listen("localhost", 8082);

    return 0;
}
