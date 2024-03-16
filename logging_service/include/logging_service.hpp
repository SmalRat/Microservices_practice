#ifndef MICROSERVICES_LOGGING_SERVICE_H
#define MICROSERVICES_LOGGING_SERVICE_H

#include <iostream>
#include <map>
#include "httplib.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

static std::map<boost::uuids::uuid, std::string> msg_pool = {};
constexpr size_t RESERVED_LETTERS = 3;

void put_msg(boost::uuids::uuid uuid, const std::string &msg);
std::string get_all_messages();

void handle_request(const httplib::Request& req, httplib::Response& res);
void handle_get_request(const httplib::Request& req, httplib::Response& res);
void handle_post_request(const httplib::Request& req, httplib::Response& res);

#endif //MICROSERVICES_LOGGING_SERVICE_H
