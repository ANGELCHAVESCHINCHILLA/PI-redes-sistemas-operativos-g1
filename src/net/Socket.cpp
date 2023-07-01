// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include "Socket.hpp"

#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cassert>
#include <iostream>
#include <sstream>

#include "../common/Log.hpp"
#include "../configuration.hpp"

#define BUFFER_SIZE 4096

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

  SSL_CTX* ssl_ctx;

 public:
  // Constructor
  SharedSocket() : fileDescriptor(-1) {
    ::memset(&this->addr, 0, sizeof(this->addr));

    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
  }

  /// Destructor. Closes the socket file descriptor
  ~SharedSocket() {
    this->close();
  }

  /// CLose the socket file descrtpr
  void close() {
    // if (this->ssl != nullptr) {
    //   SSL_shutdown(this->ssl);
    //   SSL_free(this->ssl);
    //   this->ssl = nullptr;
    // }

    if (this->ssl_ctx != nullptr) {
      SSL_CTX_free(this->ssl_ctx);
      this->ssl_ctx = nullptr;
    }

    if (this->fileDescriptor > 0) {
      ::close(this->fileDescriptor);

      // En caso de manejar reportes, aquí se reporta el socket que se ha
      // cerrado.

      this->fileDescriptor = -1;
    }

    ERR_free_strings();
    EVP_cleanup();
  }

  int create() {
    int error = SocketError::OK_SOCKET;

    this->fileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0);

    if (this->fileDescriptor == -1) {
      Log::getInstance().write(Log::ERROR, "Socket", "Can't create the socket");

      error = SocketError::CANT_CREATE_SOCKET;
    }

    return error;
  }

  int create(const struct addrinfo* address, SSL* ssl_out) {
    int error = SocketError::OK_SOCKET;

    Configuration& configuration = Configuration::getInstance();

    this->fileDescriptor = ::socket(
        address->ai_family, address->ai_socktype, address->ai_protocol);

    if (this->fileDescriptor == -1) {
      Log::getInstance().write(Log::ERROR, "Socket", "Can't create the socket");

      error = SocketError::CANT_CREATE_SOCKET;
    }

    if (!error) {
      this->ssl_ctx = SSL_CTX_new(SSLv23_method());

      if (this->ssl_ctx == nullptr) {
        error = SocketError::NOT_OK_SOCKET;
        Log::getInstance().write(
            Log::ERROR, "Socket", "Can't create SSL context");
        ERR_print_errors_fp(stderr);
      }
    }

    if (!error) {
      const char* certificate_file_path =
          configuration.certificate_file_path.c_str();

      if (SSL_CTX_use_certificate_file(
              this->ssl_ctx, certificate_file_path, SSL_FILETYPE_PEM) != 1) {
        ERR_print_errors_fp(stderr);

        error = SocketError::NOT_OK_SOCKET;
      }
    }

    if (!error) {
      const char* private_key_file_path =
          configuration.private_key_file_path.c_str();

      if (SSL_CTX_use_PrivateKey_file(
              this->ssl_ctx, private_key_file_path, SSL_FILETYPE_PEM) != 1) {
        ERR_print_errors_fp(stderr);

        error = SocketError::NOT_OK_SOCKET;
      }
    }

    if (!error) {
      ssl_out = SSL_new(this->ssl_ctx);

      if (ssl_out == nullptr) {
        error = SocketError::NOT_OK_SOCKET;
        Log::getInstance().write(Log::ERROR, "Socket", "Can't create SSL");
        ERR_print_errors_fp(stderr);
      }
    }

    if (error) {
      ssl_out = nullptr;
    }

    return error;
  }

  int bind(const std::string& address, int port) {
    (void) address;

    int error = SocketError::OK_SOCKET;

    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, address, &this->addr.sin_addr);

    error = ::bind(this->fileDescriptor, (struct sockaddr*) &this->addr,
        sizeof(this->addr));

    if (error == -1) {
      Log::getInstance().write(Log::ERROR, "Socket", "Can't bind the socket");

      error = SocketError::CANT_BIND_SOCKET;
    }

    return error;
  }

  int bind(const struct addrinfo* address) {
    int error = SocketError::OK_SOCKET;

    error = ::bind(this->fileDescriptor, address->ai_addr, address->ai_addrlen);

    if (error == -1) {
      Log::getInstance().write(Log::ERROR, "Socket", "Can't bind the socket");

      error = SocketError::CANT_BIND_SOCKET;
    }

    return error;
  }

  int listen() {
    int error = SocketError::OK_SOCKET;

    error = ::listen(this->fileDescriptor, SOMAXCONN);

    if (error == -1) {
      Log::getInstance().write(
          Log::ERROR, "Socket", "Can't listen to the socket");

      error = SocketError::CANT_LISTEN_SOCKET;
    }

    return error;
  }

  int accept(Socket& socket) {
    int error = SocketError::OK_SOCKET;

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    int fd = ::accept(this->fileDescriptor, (struct sockaddr*) &addr, &addrlen);

    if (fd == -1) {
      Log::getInstance().write(
          Log::ERROR, "Socket", "Can't accept the connection to the socket");

      error = SocketError::CANT_ACCEPT_SOCKET;
    }

    SSL* new_ssl;

    if (!error) {
      new_ssl = SSL_new(this->ssl_ctx);

      if (new_ssl == nullptr) {
        Log::getInstance().write(
            Log::ERROR, "Socket", "Can't accept the connection to the socket");

        error = SocketError::CANT_ACCEPT_SOCKET;
      }
    }

    if (!error) {
      if (SSL_set_fd(new_ssl, fd) != 1) {
        error = SocketError::CANT_CONNECT_SOCKET;
        SSL_free(new_ssl);
        ERR_print_errors_fp(stderr);
      }
    }

    if (!error) {
      if (SSL_accept(new_ssl) != 1) {
        error = SocketError::CANT_CONNECT_SOCKET;
        SSL_free(new_ssl);
        ERR_print_errors_fp(stderr);
      }
    }

    if (!error) {
      socket.setFileDescriptor(fd);
      socket.ssl = new_ssl;
    }

    return error;
  }

  // DO NOT USE THIS FUNCTION
  int connect(const std::string& address, int port) {
    (void) address;

    int error = SocketError::OK_SOCKET;

    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, address, &this->addr.sin_addr);

    error = ::connect(this->fileDescriptor, (struct sockaddr*) &this->addr,
        sizeof(this->addr));

    if (error) {
      Log::getInstance().write(
          Log::ERROR, "Socket", "Can't connect to the socket");

      error = SocketError::CANT_CONNECT_SOCKET;
    }

    return error;
  }

  int connect(const struct addrinfo* address, SSL* ssl) {
    assert(address);
    int error = SocketError::OK_SOCKET;

    // error =
    //     ::connect(this->fileDescriptor, address->ai_addr,
    //     address->ai_addrlen);

    // if (error) {
    //   Log::getInstance().write(
    //       Log::ERROR, "Socket", "Can't connect to the socket");

    //   error = SocketError::CANT_CONNECT_SOCKET;
    // }

    if (SSL_set_fd(ssl, this->fileDescriptor) != 1) {
      error = SocketError::CANT_CONNECT_SOCKET;
      ERR_print_errors_fp(stderr);
    }

    if (!error) {
      if (SSL_connect(ssl) != 1) {
        error = SocketError::CANT_CONNECT_SOCKET;
        ERR_print_errors_fp(stderr);
      }
    }

    return error;
  }

  int send(const std::string& data, SSL* ssl) {
    int error = SocketError::OK_SOCKET;

    // const char* buffer = data.c_str();
    // const size_t length = data.length();
    // ssize_t sent = 0;

    // // Try and retry to send the data until all data is sent to peer
    // while (!error && size_t(sent) < length) {
    //   size_t bytes =
    //       ::send(this->fileDescriptor, buffer + sent, length - sent, 0);

    //   if (bytes == (size_t) -1) {
    //     Log::getInstance().write(Log::ERROR, "Socket", "Can't send the
    //     data");

    //     error = SocketError::CANT_SEND_DATA;
    //   } else {
    //     sent += bytes;
    //   }
    // }

    const char* buffer = data.c_str();
    const size_t length = data.length();

    int bytes = SSL_write(ssl, buffer, length);

    if (bytes < 0) {
      error = SocketError::CANT_SEND_DATA;
      ERR_print_errors_fp(stderr);
    }

    return error;
  }

  int receive(std::string& data, SSL* ssl) {
    int error = SocketError::OK_SOCKET;

    // char buffer[BUFFER_SIZE];

    // size_t bytes = ::recv(this->fileDescriptor, buffer, BUFFER_SIZE - 1, 0);

    // if (bytes == (size_t) -1) {
    //   Log::getInstance().write(Log::ERROR, "Socket", "Can't receive the
    //   data");

    //   error = SocketError::CANT_RECEIVE_DATA;
    // }

    // if (!error) {
    //   buffer[bytes] = '\0';
    //   data = buffer;
    // }

    char buffer[BUFFER_SIZE];
    const size_t length = BUFFER_SIZE - 1;

    int bytes = SSL_read(ssl, buffer, length);

    if (bytes < 0) {
      error = SocketError::CANT_SEND_DATA;
      ERR_print_errors_fp(stderr);
    }

    return error;
  }

  int allowReuse() {
    int yes = 1;
    int error = ::setsockopt(
        this->fileDescriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    return error;
  }
};

Socket::Socket() : sharedSocket(new SharedSocket()), ssl(nullptr) {
}

void Socket::close() {
  if (this->ssl != nullptr) {
    SSL_shutdown(this->ssl);
    SSL_free(this->ssl);
    this->ssl = nullptr;
  }

  this->sharedSocket->close();
}

int Socket::create() {
  return this->sharedSocket->create();
}

int Socket::create(const struct addrinfo* address) {
  int error = SocketError::OK_SOCKET;

  SSL* ssl;

  error = this->sharedSocket->create(address, ssl);

  if (!error && ssl != nullptr) {
    this->ssl = ssl;
  }

  return error;
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
  if (this->ssl != nullptr) {
    return this->sharedSocket->accept(socket);
  } else {
    Log::getInstance().write(Log::ERROR, "Socket", "Accept...");
    return SocketError::CANT_ACCEPT_SOCKET;
  }
}

int Socket::connect(const std::string& address, int port) {
  return this->sharedSocket->connect(address, port);
}

int Socket::connect(const struct addrinfo* address) {
  if (this->ssl != nullptr) {
    return this->sharedSocket->connect(address, this->ssl);
  } else {
    Log::getInstance().write(Log::ERROR, "Socket", "Connect...");
    return SocketError::CANT_ACCEPT_SOCKET;
  }
}

int Socket::send(const std::string& data) {
  if (this->ssl != nullptr) {
    return this->sharedSocket->send(data, this->ssl);
  } else {
    Log::getInstance().write(Log::ERROR, "Socket", "Send...");
    return SocketError::CANT_ACCEPT_SOCKET;
  }
}

int Socket::receive(std::string& data) {
  if (this->ssl != nullptr) {
    return this->sharedSocket->receive(data, this->ssl);
  } else {
    Log::getInstance().write(Log::ERROR, "Socket", "Receive...");
    return SocketError::CANT_ACCEPT_SOCKET;
  }
}

int Socket::allowReuse() {
  return this->sharedSocket->allowReuse();
}
