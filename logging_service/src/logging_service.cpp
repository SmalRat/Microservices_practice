#include "common.hpp"
#include "../include/logging_service.hpp"

void put_msg(size_t uuid, const std::string &msg) {
    msg_pool[uuid] = msg;
    std::cout << msg_pool[uuid] << std::endl;
}

std::string get_all_messages() {
    size_t total_size = RESERVED_LETTERS;
    std::string concat;
    for (const auto &p: msg_pool){
        total_size += p.second.size() + 1;
    }
    concat.reserve(total_size);
    for (const auto &p: msg_pool){
        std::cout << p.first << std::endl;
        concat += p.second + "\n";
    }
    return concat;
}

void handle_get_request(const httplib::Request& req, httplib::Response& res) {
#ifdef LOGGING_SERVICE_LOGS_ENABLED
    std::cout << "Got GET request!" << std::endl;
#endif
    res.set_content(get_all_messages(), "text/plain");
}

void handle_post_request(const httplib::Request& req, httplib::Response& res) {
#ifdef LOGGING_SERVICE_LOGS_ENABLED
    std::cout << "Got POST request!" << std::endl;
#endif
    std::string msg;
    int uuid;

    try {
        boost::property_tree::ptree pt;
        std::istringstream jsonStream(req.body);
        read_json(jsonStream, pt);

        msg = pt.get<std::string>("msg");
        uuid = pt.get<int>("uuid");

        std::cout << "Message: " << msg << std::endl;
        std::cout << "UUID: " << uuid << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }

    put_msg(uuid, msg);
}


void handle_request(const httplib::Request& req, httplib::Response& res) {
    if (req.method == "GET" && req.path == "/logging_service") {
        handle_get_request(req, res);
    } else if (req.method == "POST" && req.path == "/logging_service") {
        handle_post_request(req, res);
    } else {
        res.status = NOT_FOUND_STATUS;
    }
}

int main() {
    httplib::Server server;

    server.Get("/logging_service", handle_request);
    server.Post("/logging_service", handle_request);

    server.listen("localhost", 8081);

    return 0;
}
