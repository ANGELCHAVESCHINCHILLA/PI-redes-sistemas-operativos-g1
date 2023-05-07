// Copyright © 2023 Camilo Suárez Sandí

#include "Socket.hpp"

#include <string.h>
#include <unistd.h>

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
    error = SocketError::CANT_CREATE_SOCKET;
  }

  return error;
}

int Socket::bind(char* host, int port) {
  int error = SocketError::OK;

  this->bind_addr.sin_family = AF_INET;
  this->bind_addr.sin_port = htons(port);
  this->bind_addr.sin_addr.s_addr = htons(INADDR_ANY);
  // inet_pton(AF_INET, host, &this->bind_addr.sin_addr);

  error = ::bind(
      this->fd, (struct sockaddr*) &this->bind_addr, sizeof(this->bind_addr));

  if (error == -1) {
    error = SocketError::CANT_BIND_SOCKET;
  }

  return error;
}

int Socket::listen() {
  int error = SocketError::OK;

  error = ::listen(this->fd, SOMAXCONN);

  if (error == -1) {
    error = SocketError::CANT_LISTEN_SOCKET;
  }

  return error;
}

int Socket::accept() {
  int error = SocketError::OK;

  socklen_t addrlen = sizeof(this->bind_addr);

  error = ::accept(this->fd, (struct sockaddr*) &this->bind_addr, &addrlen);

  if (error == -1) {
    error = SocketError::CANT_ACCEPT_SOCKET;
  }

  return error;
}

int Socket::connect(char* host, int port) {
  int error = SocketError::OK;

  this->connect_addr.sin_family = AF_INET;
  this->connect_addr.sin_port = htons(port);
  this->connect_addr.sin_addr.s_addr = htons(INADDR_ANY);
  // inet_pton(AF_INET, host, &this->connect_addr.sin_addr);

  error = ::connect(this->fd, (struct sockaddr*) &this->connect_addr,
      sizeof(this->connect_addr));

  if (error == -1) {
    error == SocketError::CANT_CONNECT_SOCKET;
  }

  return error;
}

void Socket::close() {
  //
  ::close(this->fd);
}
