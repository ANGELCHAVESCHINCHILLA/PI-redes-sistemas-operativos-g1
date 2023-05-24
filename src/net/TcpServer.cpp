// Copyright © 2023 Camilo Suárez Sandí

#include "TcpServer.hpp"

TcpServer::TcpServer() {
  size_t count = std::thread::hardware_concurrency() / 2;

  this->thread_pool.start(count);
}

TcpServer::~TcpServer() {
  //
}

int TcpServer::start(const std::string& address, int port) {
  int error = SocketError::OK;

  error = this->server_socket.create();

  if (!error) {
    error = this->server_socket.bind(address, port);
  }

  if (!error) {
    error = this->server_socket.listen();
  }

  while (!error) {
    this->thread_pool.execute([this]() {
      int error = SocketError::OK;

      Socket client_socket;

      if (!error) {
        error = this->server_socket.accept(client_socket);
      }

      std::string request;

      if (!error) {
        error = client_socket.receive(request);
      }

      if (!error) {
        std::string response = this->run(request);

        error = client_socket.send(response);
      }

      client_socket.close();

      if (error) {
        return;
      }
    });
  }

  return error;
}
