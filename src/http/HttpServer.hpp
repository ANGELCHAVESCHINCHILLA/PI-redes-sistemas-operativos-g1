// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_SERVER_HPP_
#define HTTP_SERVER_HPP_

#include "../net/TcpServer.hpp"

class HttpServer : public TcpServer {
 private:
 public:
  std::string run(const std::string& request) override;
};

#endif  // HTTP_SERVER_HPP_
