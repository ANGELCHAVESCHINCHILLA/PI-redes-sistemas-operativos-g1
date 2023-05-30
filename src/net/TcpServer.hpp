// Copyright © 2023 Camilo Suárez Sandí

#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include "../concurrent/ThreadPool.hpp"
#include "Socket.hpp"

class TcpServer {
 protected:
  Socket server_socket;

 private:
  ThreadPool thread_pool;

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

  int run();

  virtual void stop() = 0;

  virtual void route(const std::string& request, std::string& response) = 0;
};

#endif  // TCP_SERVER_HPP_
