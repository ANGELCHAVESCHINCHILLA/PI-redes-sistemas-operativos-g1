// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_SERVER_HPP_
#define HTTP_SERVER_HPP_

#include <future>
#include <vector>

#include "../common/common.hpp"
#include "../net/TcpServer.hpp"
#include "HttpApp.hpp"

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

  static void stopServer(int signal);

  void stop();

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
  void handleClientConnection(const std::string& request, std::string& response,
      Socket& client) override;

  /**
   * @brief For each app in this server, aks to each one if the request can be
   * handle by that specific app.
   *
   * @param request
   * @param response
   * @return true if an app could handle the request.
   * @return false another case.
   */
  bool route(HttpRequest& request, HttpResponse& response);

  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);

  int appendApp(HttpApp* application);

 private:
  /**
   * @brief Creates a client socket to send a request and receive a response.
   * Throws an error if there's a network error.
   *
   * @param request The request to send.
   * @return HttpResponse The response to receive.
   */
  static HttpResponse privateFetch(HttpRequest& request);

 public:
  /**
   * @brief Returns the future of a fetch. Use .get() to wait to execute the
   * fetch.
   *
   * @param request The request to send.
   * @return std::future<HttpResponse> The response to receive.
   */
  static std::future<HttpResponse> fetch(HttpRequest& request);
};

#endif  // HTTP_SERVER_HPP_
