// Copyright © 2023 Camilo Suárez Sandí

#include "TcpServer.hpp"

TcpServer::TcpServer() {
  //
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

  while (!error && true) {
    error = this->server_socket.accept(client_socket);

    std::string request;

    if (!error) {
      error = this->client_socket.receive(request);
    }

    if (!error) {
      std::string response = this->run(request);

      error = this->client_socket.send(response);
    }
  }

  return error;
}
