#include "common.hpp"
#include "../include/facade_service.hpp"

std::string concat_responses(const std::string &log_service_response, const std::string &message_service_response){
    std::string concat{};
    concat.reserve(RESERVED_LETTERS + log_service_response.size() + message_service_response.size() + 1);
    concat += "Logging service response: \n";
    concat += log_service_response;
    concat += "\nMessage service response: \n";
    concat += message_service_response;
    concat += "\n";
    return concat;
}

void handle_get_request(const httplib::Request& req, httplib::Response& res) {
#ifdef FACADE_SERVICE_LOGS_ENABLED
    std::cout << "Got GET request!" << std::endl;
#endif
    std::string logging_service_response;
    std::string message_service_response;
    send_get_request(LOGGING_PATH, "/logging_service", logging_service_response);
    send_get_request(MESSAGES_PATH, "/messages_service", message_service_response);

    res.set_content(concat_responses(logging_service_response, message_service_response), "text/plain");
}

void handle_post_request(const httplib::Request& req, httplib::Response& res) {
#ifdef FACADE_SERVICE_LOGS_ENABLED
    std::cout << "Got POST request!" << std::endl;
#endif
    std::string msg = req.body;
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string uuidStr = boost::uuids::to_string(uuid);

    Json::Value json_data;
    json_data["uuid"] = uuidStr;
    json_data["msg"] = msg;

    std::string json_str = Json::writeString(Json::StreamWriterBuilder(), json_data);

    std::string response;

#ifdef FACADE_SERVICE_LOGS_ENABLED
    std::cout << "Sending json to the logging service: " << std::endl;
    std::cout << json_str << std::endl;
#endif

    send_post_request(LOGGING_PATH, "/logging_service", json_str, response);

#ifdef FACADE_SERVICE_LOGS_ENABLED
    std::cout << "Got response from the logging service: " << std::endl;
    std::cout << response << std::endl;
#endif

    res.set_content("Received msg: " + req.body, "text/plain");
}

void handle_request(const httplib::Request& req, httplib::Response& res) {
    if (req.method == "GET" && req.path == "/facade_service") {
        handle_get_request(req, res);
    } else if (req.method == "POST" && req.path == "/facade_service") {
        handle_post_request(req, res);
    } else {
        res.status = NOT_FOUND_STATUS;
    }
}

int main() {
    httplib::Server server;

    server.Get("/facade_service", handle_request);
    server.Post("/facade_service", handle_request);

    std::cout << "Starting facade service!" << std::endl;

    server.listen("localhost", 8080);

    return 0;
}
