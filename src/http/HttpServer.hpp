// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_SERVER_HPP_
#define HTTP_SERVER_HPP_

#include <vector>

#include "../net/TcpServer.hpp"
#include "HttpApp.hpp"

class HttpServer : public TcpServer {
 private:
  std::vector<HttpApp*> apps;

 public:
  /**
   * @brief Default constructor.
   *
   */
  HttpServer();

  /**
   * @brief Destructor.
   *
   */
  ~HttpServer();

  // Copy Constructor
  HttpServer(const HttpServer& other) = delete;

  // Copy Assignment Operator
  HttpServer& operator=(const HttpServer& other) = delete;

  // Move Constructor
  HttpServer(HttpServer&& other) = delete;

  // Move Assignment Operator
  HttpServer& operator=(HttpServer&& other) = delete;

  int start(const std::string& address, int port) override;

  void handleClientConnection(const std::string& request, std::string& response
    , Socket& client) override;

  bool route(const HttpRequest& request, HttpResponse& response);
};

#endif  // HTTP_SERVER_HPP_
