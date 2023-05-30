// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_SERVER_HPP_
#define HTTP_SERVER_HPP_

#include <vector>

#include "../net/TcpServer.hpp"
#include "HttpApp.hpp"

class HttpServer : public TcpServer {
 private:
  static HttpServer* instance;

  std::vector<HttpApp*> apps;

 public:
  static HttpServer* getInstance();

  static void onSignal(int signal);

 private:
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

 public:
  void stop() override;

  void route(const std::string& request, std::string& response) override;

  void addApp(HttpApp* app);
};

#endif  // HTTP_SERVER_HPP_
