#include <iostream>
#include "httplib.h"

std::string sendPostRequest(const std::string& host, const std::string& path, const std::string& message) {
    httplib::Client client(host.c_str());
    auto res = client.Post(path.c_str(), message, "text/plain");

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <message>\n";
        return 1;
    }

    std::string host = "http://localhost:8080";
    std::string path = "/facade_service";
    std::string message = argv[1];

    std::string response = sendPostRequest(host, path, message);
    std::cout << "Response:\n" << response << std::endl;

    return 0;
}
