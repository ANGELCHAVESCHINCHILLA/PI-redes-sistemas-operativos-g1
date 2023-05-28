// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include "Socket.hpp"

#include <string.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

#define BUFFER_SIZE 1024

struct SharedSocket {
  /// Cannot be coppied
  DISABLE_COPY(SharedSocket);

 public:
  int fileDescriptor;
  /// IPv4 address of the peer on the other side of the connection
  struct sockaddr_in addr;
  /// Buffer to extract data before a read of received data
  std::ostringstream output;
  /// Buffer to store data in memory before sending to the peer
  std::ostringstream input;

 public:
  // Constructor
  SharedSocket() {
    ::memset(&this->addr, 0, sizeof(this->addr));
  }

  /// Destructor. Closes the socket file descriptor
  ~SharedSocket() {
    this->close();
  }

  /// CLose the socket file descrtpr
  void close() {
    if (this->fileDescriptor > 0) {
      ::close(this->fileDescriptor);

      // En caso de manejar reportes, aquí se reporta el socket que se ha
      // cerrado. 

      this->fileDescriptor = -1;
    }
  }

  int create() {
    int error = SocketError::OK;

    this->fileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0);

    if (this->fileDescriptor == -1) {
      std::cerr << "Can't create the socket.\n";

      error = SocketError::CANT_CREATE_SOCKET;
    }

    return error;
  }

  int bind(const std::string& address, int port) {
    int error = SocketError::OK;

    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, address, &this->addr.sin_addr);

    error = ::bind(this->fileDescriptor, (struct sockaddr*) &this->addr
                  , sizeof(this->addr));

    if (error == -1) {
      std::cerr << "Can't bind the socket.\n";

      error = SocketError::CANT_BIND_SOCKET;
    }

    return error;
  }

  int listen() {
    int error = SocketError::OK;

    error = ::listen(this->fileDescriptor, SOMAXCONN);

    if (error == -1) {
      std::cerr << "Can't listen to the socket.\n";

      error = SocketError::CANT_LISTEN_SOCKET;
    }

    return error;
  }

  int accept(Socket& socket) {
    int error = SocketError::OK;

    struct sockaddr_in addr;
    size_t addrlen = sizeof(addr);

    int fd = ::accept(this->fileDescriptor, (struct sockaddr*) &addr
              , (socklen_t*) &addrlen);

    if (fd == -1) {
      std::cerr << "Can't accept the connection to the socket.\n";

      error = SocketError::CANT_ACCEPT_SOCKET;
    }

    if (!error) {
      socket.setFileDescriptor(fd);
    }

    return error;
  }

  int connect(const std::string& address, int port) {
    int error = SocketError::OK;

    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, address, &this->addr.sin_addr);

    error = ::connect(this->fileDescriptor, (struct sockaddr*) &this->addr
            , sizeof(this->addr));

    if (error == -1) {
      std::cerr << "Can't connect to the socket.\n";

      error = SocketError::CANT_CONNECT_SOCKET;
    }

    return error;
  }

  int send(const std::string& data) {
    int error = SocketError::OK;

    size_t bytes = ::send(this->fileDescriptor, data.c_str(), data.size(), 0);

    if (bytes == (size_t) -1) {
      std::cerr << "Can't send the data.\n";

      error = SocketError::CANT_SEND_DATA;
    }

    return error;
  }

  int receive(std::string& data) {
    int error = SocketError::OK;

    char buffer[BUFFER_SIZE];

    size_t bytes = ::recv(this->fileDescriptor, buffer, BUFFER_SIZE - 1, 0);

    if (bytes == (size_t) -1) {
      std::cerr << "Can't receive the data.\n";

      error = SocketError::CANT_RECEIVE_DATA;
    }

    if (!error) {
      buffer[bytes] = '\0';
      data = buffer;
    }

    return error;
  }
};

Socket::Socket()
  : sharedSocket(new SharedSocket()) {
}

void Socket::close() {
  this->sharedSocket->close();
}

int Socket::create() {
  return this->sharedSocket->create();
}

int Socket::getFileDescriptor() const {
  return this->sharedSocket->fileDescriptor;
}

void Socket::setFileDescriptor(int fd) {
  this->sharedSocket->fileDescriptor = fd;
}


int Socket::bind(const std::string& address, int port) {
  return this->sharedSocket->bind(address, port);
}

int Socket::listen() {
  return this->sharedSocket->listen();
}

int Socket::accept(Socket& socket) {
  return this->sharedSocket->accept(socket);
}

int Socket::connect(const std::string& address, int port) {
  return this->sharedSocket->connect(address, port);
}

int Socket::send(const std::string& data) {
  return this->sharedSocket->send(data);
}

int Socket::receive(std::string& data) {
  return this->sharedSocket->receive(data);

}
