#ifndef MICROSERVICES_FACADE_SERVICE_H
#define MICROSERVICES_FACADE_SERVICE_H

#include <iostream>
#include "httplib.h"
#include "json/json.h"

inline static size_t LAST_UUID = 0;
inline constexpr size_t RESERVED_LETTERS = 150;

size_t gen_uuid();
std::string concat_responses(const std::string &log_service_response, const std::string &message_service_response);

void handle_request(const httplib::Request& req, httplib::Response& res);
void handle_get_request(const httplib::Request& req, httplib::Response& res);
void handle_post_request(const httplib::Request& req, httplib::Response& res);


#endif //MICROSERVICES_FACADE_SERVICE_H
