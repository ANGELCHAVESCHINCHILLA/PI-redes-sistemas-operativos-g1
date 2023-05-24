// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_SERVER_HPP_
#define HTTP_SERVER_HPP_

#include "../net/TcpServer.hpp"

class HttpServer : public TcpServer {
 private:
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

  void run(const std::string& request, std::string& response) override;
};

#endif  // HTTP_SERVER_HPP_
