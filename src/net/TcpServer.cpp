// Copyright © 2023 Camilo Suárez Sandí

#include "TcpServer.hpp"

#include <iostream>

#include "../error.hpp"

TcpServer::TcpServer() {
  size_t count = std::thread::hardware_concurrency() / 2;

  this->thread_pool.start(count);
}

TcpServer::~TcpServer() {
}

int TcpServer::start(const std::string& address, int port) {
  int error = Error::OK;

  error = this->server_socket.create();

  if (!error) {
    error = this->server_socket.bind(address, port);
  }

  if (!error) {
    error = this->server_socket.listen();

    std::cout << "Server running at " << address << ":" << port << "\n";
  }

  return error;
}

int TcpServer::run() {
  int error = Error::OK;

  while (!error) {
    Socket client_socket;

    if (!error) {
      error = this->server_socket.accept(client_socket);
    }

    if (!error) {
      auto task = [&, client_socket]() {
        std::string request;
        std::string response;

        if (!error) {
          error = client_socket.receive(request);
        }

        if (!error) {
          this->route(request, response);

          error = client_socket.send(response);
        }

        client_socket.close();
      };

      this->thread_pool.execute(task);
    }
  }

  return error;
}
