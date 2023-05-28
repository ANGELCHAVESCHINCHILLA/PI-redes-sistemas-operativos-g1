// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

// #include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "../concurrent/ThreadPool.hpp"
#include "Socket.hpp"

class TcpServer {
 protected:
  Socket server_socket;

  ThreadPool thread_pool;

  struct addrinfo serverSocketSettings;

  struct addrinfo* possibleAddresses = nullptr;


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

  void stopListening();

  virtual int start(const std::string& address, int port) = 0;

  virtual void handleClientConnection(const std::string& request, std::string& response
    , Socket& client) = 0;
  
  int fetchPossibleAddresses(const char* port);

  int openServerSocket();

  int acceptConnections();
};

#endif  // TCP_SERVER_HPP_
