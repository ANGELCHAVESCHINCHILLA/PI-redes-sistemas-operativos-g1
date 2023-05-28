// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla


#ifndef HTTP_SERVER_HPP_
#define HTTP_SERVER_HPP_

#include <vector>

#include "../net/TcpServer.hpp"
#include "HttpApp.hpp"
#include "../common/common.hpp"

class HttpServer : public TcpServer {
  DISABLE_COPY(HttpServer);

 private:
  std::vector<HttpApp*> apps;

 private:
  /// Constructor
  HttpServer();

 public:
  /// Get instance (Singleton pattern)
  static HttpServer& getInstance();

  /**
   * @brief Destructor.
   *
   */
  ~HttpServer();

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
