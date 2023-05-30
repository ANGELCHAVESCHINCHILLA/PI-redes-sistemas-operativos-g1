// Copyright © 2023 Camilo Suárez Sandí

#include "Socket.hpp"

#include <string.h>
#include <unistd.h>

#include <iostream>

#include "../error.hpp"

#define BUFFER_SIZE 1024

Socket::Socket() : shared_socket(new SharedSocket()) {
}

Socket::~Socket() {
}

Socket::Socket(const Socket& other) : shared_socket(other.shared_socket) {
}

int Socket::create() {
  int error = Error::OK;

  this->shared_socket->fd = ::socket(AF_INET, SOCK_STREAM, 0);

  if (this->shared_socket->fd == -1) {
    std::cerr << "Can't create the socket.\n";

    error = Error::CANT_CREATE_SOCKET;
  }

  if (!error) {
    int yes = 1;

    error = ::setsockopt(
        this->shared_socket->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  }

  if (!error) {
    int yes = 1;

    error = ::setsockopt(
        this->shared_socket->fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes));
  }

  return error;
}

int Socket::bind(const std::string& address, int port) {
  int error = Error::OK;

  this->shared_socket->addr.sin_family = AF_INET;
  this->shared_socket->addr.sin_port = htons(port);
  this->shared_socket->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // inet_pton(AF_INET, address.c_str(), &this->shared_socket->addr.sin_addr);

  error = ::bind(this->shared_socket->fd,
      (struct sockaddr*) &this->shared_socket->addr,
      sizeof(this->shared_socket->addr));

  if (error == -1) {
    std::cerr << "Can't bind the socket.\n";

    error = Error::CANT_BIND_SOCKET;
  }

  return error;
}

int Socket::listen() const {
  int error = Error::OK;

  error = ::listen(this->shared_socket->fd, SOMAXCONN);

  if (error == -1) {
    std::cerr << "Can't listen to the socket.\n";

    error = Error::CANT_LISTEN_SOCKET;
  }

  return error;
}

int Socket::accept(Socket& socket) const {
  int error = Error::OK;

  struct sockaddr_in addr;
  size_t addrlen = sizeof(addr);

  int fd = ::accept(
      this->shared_socket->fd, (struct sockaddr*) &addr, (socklen_t*) &addrlen);

  if (fd == -1) {
    std::cerr << "Can't accept the connection to the socket.\n";

    error = Error::CANT_ACCEPT_SOCKET;
  }

  if (!error) {
    socket.shared_socket->fd = fd;
  }

  return error;
}

int Socket::connect(const std::string& address, int port) {
  int error = Error::OK;

  this->shared_socket->addr.sin_family = AF_INET;
  this->shared_socket->addr.sin_port = htons(port);
  this->shared_socket->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // inet_pton(AF_INET, address.c_str(), &this->shared_socket->addr.sin_addr);

  error = ::connect(this->shared_socket->fd,
      (struct sockaddr*) &this->shared_socket->addr,
      sizeof(this->shared_socket->addr));

  if (error == -1) {
    std::cerr << "Can't connect to the socket.\n";

    error = Error::CANT_CONNECT_SOCKET;
  }

  return error;
}

int Socket::send(const std::string& data) const {
  int error = Error::OK;

  size_t bytes = ::send(this->shared_socket->fd, data.c_str(), data.size(), 0);

  if (bytes == (size_t) -1) {
    std::cerr << "Can't send the data.\n";

    error = Error::CANT_SEND_DATA;
  }

  return error;
}

int Socket::receive(std::string& data) const {
  int error = Error::OK;

  char buffer[BUFFER_SIZE];

  size_t bytes = ::recv(this->shared_socket->fd, buffer, BUFFER_SIZE - 1, 0);

  if (bytes == (size_t) -1) {
    std::cerr << "Can't receive the data.\n";

    error = Error::CANT_RECEIVE_DATA;
  }

  if (!error) {
    buffer[bytes] = '\0';
    data = buffer;
  }

  return error;
}

void Socket::close() const {
  this->shared_socket->close();
}
