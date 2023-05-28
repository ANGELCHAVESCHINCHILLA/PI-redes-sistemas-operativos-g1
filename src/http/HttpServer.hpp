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

  /**
   * @brief Create the server socket with address IP and port. Then start to
   * listen for connections.
   * 
   * @param address 
   * @param port 
   * @return int 
   */
  int start(const std::string& address, int port) override;

  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @param client 
   */
  void handleClientConnection(const std::string& request, std::string& response
    , Socket& client) override;

  /**
   * @brief For each app in this server, aks to each one if the request can be
   * handle by that specific app.
   * 
   * @param request
   * @param response 
   * @return true if an app could handle the request.
   * @return false another case.
   */
  bool route(const HttpRequest& request, HttpResponse& response);
};

#endif  // HTTP_SERVER_HPP_
