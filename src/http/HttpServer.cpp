// Copyright © 2023 Camilo Suárez Sandí

#include "HttpServer.hpp"

#include <iostream>

HttpServer::HttpServer() {
  //
}

HttpServer::~HttpServer() {
  //
}

void HttpServer::run(const std::string& request, std::string& response) {
  std::cout << request << "\n";

  response = "HTTP/1.1 200 OK\n\nHello, World!";
};
