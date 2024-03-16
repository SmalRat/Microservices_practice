#ifndef MICROSERVICES_COMMON_H
#define MICROSERVICES_COMMON_H

#include <string>
#include <httplib.h>

const std::string FACADE_PATH = "http://localhost:8080";
const std::string LOGGING_PATH = "http://localhost:8081";
const std::string MESSAGES_PATH = "http://localhost:8082";

inline constexpr int NOT_FOUND_STATUS = 404;
inline constexpr int ALL_OK_STATUS = 200;

const std::string POST_FAIL_RESPONSE = "Failed to send POST request";
const std::string GET_FAIL_RESPONSE = "Failed to send GET request";


void send_post_request(const std::string &url, const std::string &path, const std::string &data, std::string &response) {
    httplib::Client client(url);
    auto res = client.Post(path, data, "application/json");

    if (res && res->status == ALL_OK_STATUS) {
        response = res->body;
    } else {
        response = POST_FAIL_RESPONSE;
    }
}

void send_get_request(const std::string &url, const std::string &path, std::string &response) {
    httplib::Client client(url);
//    std::cout << url;
    auto res = client.Get(path);
    //std::cout << "Messages service response code: " << res << std::endl;
    if (res && res->status == ALL_OK_STATUS) {
        response = res->body;
    } else {
        response = GET_FAIL_RESPONSE;
    }
}

#endif //MICROSERVICES_COMMON_H