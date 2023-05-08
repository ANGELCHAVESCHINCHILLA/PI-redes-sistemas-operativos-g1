// Copyright © 2023 Camilo Suárez Sandí

#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include "Socket.hpp"

class TcpServer {
 private:
  Socket server_socket;
  Socket client_socket;

 public:
  // Default Constructor
  TcpServer();

  // Destructor
  ~TcpServer();

  // Copy Constructor
  TcpServer(const TcpServer& other) = delete;

  // Copy Assignment Operator
  TcpServer& operator=(const TcpServer& other) = delete;

  // Move Constructor
  TcpServer(TcpServer&& other) = delete;

  // Move Assignment Operator
  TcpServer& operator=(TcpServer&& other) = delete;

  int start(const std::string& address, int port);

  virtual std::string run(const std::string& request) = 0;
};

#endif  // TCP_SERVER_HPP_
