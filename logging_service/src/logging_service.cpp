#include "common.hpp"
#include "../include/logging_service.hpp"


void put_msg(boost::uuids::uuid uuid, const std::string &msg) {
    msg_pool[uuid] = msg;
}

std::string get_all_messages() {
    size_t total_size = RESERVED_LETTERS;
    std::string concat;
    for (const auto &p: msg_pool){
        total_size += p.second.size() + 1;
    }
    concat.reserve(total_size);
    for (const auto &p: msg_pool){
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

    const auto &json_str = req.body;
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    Json::Value json_data;
    std::string errors;

    bool parsingSuccessful = reader->parse(json_str.c_str(), json_str.c_str() + json_str.length(), &json_data, &errors);
    delete reader;

    if (!parsingSuccessful) {
        std::stringstream error_msg;
        error_msg << "Error parsing JSON: " << errors << std::endl;
        throw std::runtime_error(error_msg.str());
    }

    std::string uuidStr = json_data["uuid"].asString();
    std::string msg = json_data["msg"].asString();
    boost::uuids::string_generator gen;
    boost::uuids::uuid uuid = gen(uuidStr);

    std::cout << "JSON content: " << std::endl << std::endl;
    std::cout << "UUID: " << uuidStr << std::endl;
    std::cout << "Message: " << msg << std::endl;

    put_msg(uuid, msg);

    res.set_content("Message logged!", "text/plain");
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

    std::cout << "Starting logging service!" << std::endl;

    server.listen("localhost", 8081);

    return 0;
}
