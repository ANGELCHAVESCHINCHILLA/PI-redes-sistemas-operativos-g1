// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include <cassert>
#include <iostream>

#include "TcpServer.hpp"

TcpServer::TcpServer() {
  // size_t count = std::thread::hardware_concurrency() / 2;

  this->serverSocketSettings.ai_flags = AI_PASSIVE;  // Fill with my local IP
  this->serverSocketSettings.ai_family = AF_UNSPEC;
  this->serverSocketSettings.ai_socktype = SOCK_STREAM; 

  // this->thread_pool.start(count);
}

TcpServer::~TcpServer() {
  //
}

int TcpServer::acceptConnections () {
  std::cout << "Voy a aceptar conexiones";   // para debug
  int error = SocketError::OK_SOCKET;

  while (true/*!error*/) {
    error = SocketError::OK_SOCKET;
    Socket client_socket;

    // Accept conection with client
    error = this->server_socket.accept(client_socket);

    std::string request;
    std::string response;

    if (!error) {
      // Impresión para debug
      std::cout << "Logré establecer conexión con "
        << client_socket.getFileDescriptor() << std::endl;

      // Receive data from client
      error = client_socket.receive(request);
    } else {
      throw std::runtime_error("could not accept client connection");      
    }

    if (!error) {
      // Handle the client connection
      this->handleClientConnection(request, response, client_socket);
    }
  }

  return error;
}

void TcpServer::stopListening() {
  // An ugly way to stop incoming connections is closing the socket
  if (this->server_socket.getFileDescriptor() >= 0) {
    this->server_socket.close();
  }
}

int TcpServer::fetchPossibleAddresses(const char* port) {
  // This function is designed to be called once
  assert(this->possibleAddresses == nullptr);
  // Fetch all available addresses and store results in object attributes
  int error = ::getaddrinfo(nullptr, port, &this->serverSocketSettings
    , &this->possibleAddresses);
  // If getaddrinfo failed, raise an exception
  if (error) {
    error = SocketError::CANT_FETCH_ADDRESSES;
  } else {
    error = SocketError::OK_SOCKET;
  }
  return error;
}

int TcpServer::openServerSocket() {
  int error = SocketError::OK_SOCKET;
  assert(this->server_socket.getFileDescriptor() == -1);
  // Traverse the available addresses and select the first one that works
  for (const struct addrinfo* address = this->possibleAddresses; address;
      address = address->ai_next) {
    // Try to open a socket using this address result
    error = this->server_socket.create(address);

    // If we could open the socket
    if (!error) {
      // Allow the socket to reuse the local IP for other connections
      error = this->server_socket.allowReuse();
      if (!error) {
        // Bind the socket to the port we passed in to getaddrinfo()
        error = this->server_socket.bind(address);
        if (!error) {
          // This address is OK, stop searching and use its socket
          // this->selectedAddress = address;
          return error;
        }
      } else {
        throw std::runtime_error("could not set reusing socket");
      }

      // We could not bind a port for this address, continue searching
      this->server_socket.close();
    } else {
      // We could not open a socket for this address, continue searching
    }
  }

  return error;
}