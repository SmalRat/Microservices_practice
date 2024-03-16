#ifndef MICROSERVICES_MESSAGES_SERVICE_H
#define MICROSERVICES_MESSAGES_SERVICE_H

#include <iostream>
#include "httplib.h"

const std::string PHONY = "Not implemented yet!";

std::string get_message();

void handle_request(const httplib::Request& req, httplib::Response& res);
void handle_get_request(const httplib::Request& req, httplib::Response& res);
void handle_post_request(const httplib::Request& req, httplib::Response& res);

#endif //MICROSERVICES_MESSAGES_SERVICE_H
