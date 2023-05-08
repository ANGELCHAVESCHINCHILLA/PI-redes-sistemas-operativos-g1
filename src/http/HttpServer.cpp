// Copyright © 2023 Camilo Suárez Sandí

#include "HttpServer.hpp"

#include <iostream>

std::string HttpServer::run(const std::string& request) {
  std::cout << request << "\n";

  return "HTTP/1.1 200 OK\n\nHello, World!";
};
