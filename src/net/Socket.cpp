// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include "Socket.hpp"

#include <sys/socket.h>
#include <cassert>
#include <netdb.h>
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
  SharedSocket() 
    : fileDescriptor(-1) {
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
    int error = SocketError::OK_SOCKET;

    this->fileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0);

    if (this->fileDescriptor == -1) {
      std::cerr << "Can't create the socket.\n";

      error = SocketError::CANT_CREATE_SOCKET;
    }

    return error;
  }

  int create(const struct addrinfo* address) {
    int error = SocketError::OK_SOCKET;

    this->fileDescriptor = ::socket(address->ai_family, address->ai_socktype
            , address->ai_protocol);

    if (this->fileDescriptor == -1) {
      std::cerr << "Can't create the socket.\n";

      error = SocketError::CANT_CREATE_SOCKET;
    }

    return error;
  }

  int bind(const std::string& address, int port) {
    int error = SocketError::OK_SOCKET;

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

  int bind(const struct addrinfo* address) {
    int error = SocketError::OK_SOCKET;

    error = ::bind(this->fileDescriptor, address->ai_addr, address->ai_addrlen);

    if (error == -1) {
      std::cerr << "Can't bind the socket.\n";

      error = SocketError::CANT_BIND_SOCKET;
    }

    return error;
  }

  int listen() {
    int error = SocketError::OK_SOCKET;

    error = ::listen(this->fileDescriptor, SOMAXCONN);

    if (error == -1) {
      std::cerr << "Can't listen to the socket.\n";

      error = SocketError::CANT_LISTEN_SOCKET;
    }

    return error;
  }

  int accept(Socket& socket) {
    int error = SocketError::OK_SOCKET;

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    int fd = ::accept(this->fileDescriptor, (struct sockaddr*) &addr
              , &addrlen);

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
    int error = SocketError::OK_SOCKET;

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

  int connect(const struct addrinfo* address) {
    assert(address);
    int error = ::connect(this->fileDescriptor, address->ai_addr
                    , address->ai_addrlen);
    if (error == -1) {
      return SocketError::CANT_CONNECT_SOCKET;
    } else {
      return SocketError::OK_SOCKET;
    }
  }

  int send(const std::string& data) {
    int error = SocketError::OK_SOCKET;
    const char* buffer = data.c_str();
    const size_t length = data.length();
    ssize_t sent = 0;

    // Try and retry to send the data until all data is sent to peer
    while (!error && size_t(sent) < length) {
      size_t bytes = ::send(this->fileDescriptor, buffer + sent, length - sent, 0);

      if (bytes == (size_t) -1) {
        std::cerr << "Can't send the data.\n";

        error = SocketError::CANT_SEND_DATA;
      } else {
        sent += bytes;
      }

    }

    return error;
  }

  int receive(std::string& data) {
    int error = SocketError::OK_SOCKET;

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

  int allowReuse() {
    int yes = 1;
    int error = ::setsockopt(this->fileDescriptor, SOL_SOCKET, SO_REUSEADDR
                , &yes, sizeof(yes));
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

int Socket::create(const struct addrinfo* address) {
  return this->sharedSocket->create(address);
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

int Socket::bind(const struct addrinfo* address) {
  return this->sharedSocket->bind(address);
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

int Socket::connect(const struct addrinfo* address) {
  return this->sharedSocket->connect(address);
}

int Socket::send(const std::string& data) {
  return this->sharedSocket->send(data);
}

int Socket::receive(std::string& data) {
  return this->sharedSocket->receive(data);
}

int Socket::allowReuse() {
  return this->sharedSocket->allowReuse();
}
