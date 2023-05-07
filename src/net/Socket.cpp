// Copyright © 2023 Camilo Suárez Sandí

#include "Socket.hpp"

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#define BUFFER_SIZE 1024

Socket::Socket() {
  ::memset(&this->bind_addr, 0, sizeof(this->bind_addr));
  ::memset(&this->connect_addr, 0, sizeof(this->connect_addr));
}

Socket::~Socket() {
  //
  this->close();
}

int Socket::create() {
  int error = SocketError::OK;

  this->fd = ::socket(AF_INET, SOCK_STREAM, 0);

  if (this->fd == -1) {
    std::cerr << "Can't create the socket.\n";

    error = SocketError::CANT_CREATE_SOCKET;
  }

  return error;
}

int Socket::bind(const std::string& host, int port) {
  int error = SocketError::OK;

  this->bind_addr.sin_family = AF_INET;
  this->bind_addr.sin_port = htons(port);
  this->bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // inet_pton(AF_INET, host, &this->bind_addr.sin_addr);

  error = ::bind(
      this->fd, (struct sockaddr*) &this->bind_addr, sizeof(this->bind_addr));

  if (error == -1) {
    std::cerr << "Can't bind the socket.\n";

    error = SocketError::CANT_BIND_SOCKET;
  }

  return error;
}

int Socket::listen() {
  int error = SocketError::OK;

  error = ::listen(this->fd, SOMAXCONN);

  if (error == -1) {
    std::cerr << "Can't listen to the socket.\n";

    error = SocketError::CANT_LISTEN_SOCKET;
  }

  return error;
}

// TODO: Fix accept
int Socket::accept() {
  int error = SocketError::OK;

  int fd = ::accept(this->fd, (struct sockaddr*) 0, 0);

  if (fd == -1) {
    std::cerr << "Can't accept the connection to the socket.\n";

    error = SocketError::CANT_ACCEPT_SOCKET;
  }

  return error;
}

int Socket::connect(const std::string& host, int port) {
  int error = SocketError::OK;

  this->connect_addr.sin_family = AF_INET;
  this->connect_addr.sin_port = htons(port);
  this->connect_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // inet_pton(AF_INET, host, &this->connect_addr.sin_addr);

  error = ::connect(this->fd, (struct sockaddr*) &this->connect_addr,
      sizeof(this->connect_addr));

  if (error == -1) {
    std::cerr << "Can't connect to the socket.\n";

    error == SocketError::CANT_CONNECT_SOCKET;
  }

  return error;
}

int Socket::send(const std::string& data) {
  int error = SocketError::OK;

  size_t bytes = ::send(this->fd, data.c_str(), data.size(), 0);

  if (bytes == -1) {
    std::cerr << "Can't send the data.\n";

    error = SocketError::CANT_SEND_DATA;
  }

  return error;
}

int Socket::receive(std::string& data) {
  int error = SocketError::OK;

  char buffer[BUFFER_SIZE];

  size_t bytes = ::recv(this->fd, buffer, BUFFER_SIZE - 1, 0);

  if (bytes == -1) {
    std::cerr << "Can't receive the data.\n";

    error = SocketError::CANT_RECEIVE_DATA;
  }

  if (!error) {
    buffer[bytes] = '\0';
    data = buffer;
  }

  return error;
}

void Socket::close() {
  //
  ::close(this->fd);
}
