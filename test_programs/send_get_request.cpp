#include <iostream>
#include "httplib.h"

std::string sendGetRequest(const std::string& host, const std::string& path) {
    httplib::Client client(host.c_str());
    auto res = client.Get(path.c_str());

    if (!res) {
        std::cerr << "Error: Connection failed\n";
        return "";
    }

    if (res->status != 200) {
        std::cerr << "Error: HTTP status code " << res->status << std::endl;
        return "";
    }

    return res->body;
}

int main() {
    std::string host = "http://localhost:8080";
    std::string path = "/facade_service";

    std::string response = sendGetRequest(host, path);
    std::cout << "Response:\n" << response << std::endl;

    return 0;
}
