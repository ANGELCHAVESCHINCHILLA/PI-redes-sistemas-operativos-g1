// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cassert>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>

#include "TcpClient.hpp"
#include "Socket.hpp"

TcpClient::TcpClient() {
  // Set initial values for searching for a suitable network address
  ::memset(&this->clientSocketSettings, 0, sizeof(this->clientSocketSettings));
  // IPv4 or IPv6
  this->clientSocketSettings.ai_family = AF_UNSPEC;
  // TCP socket
  this->clientSocketSettings.ai_socktype = SOCK_STREAM;
}

TcpClient::~TcpClient() {
  this->close();
}

void TcpClient::close() {
  // Close the connection with the server
  this->clientSocket.close();
  // Release the resources required by the address
  if (this->possibleAddresses) {
    ::freeaddrinfo(this->possibleAddresses);
    this->possibleAddresses = nullptr;
  }
}

Socket& TcpClient::connect(const char* server, const char* port) {
  int error = SocketError::OK_SOCKET;
  // If there is an active connection, close it
  this->close();
  // Fetch all available network addresses where we can listen with this port
  error = this->fetchPossibleAddresses(server, port);

  if (!error) {
    // Get a socket for the first available address that works
    error = this->openSocketWithServer(server, port);
  }

  if (error) {
    this->close();
    throw std::runtime_error(std::string("could not connect to ")
      + server + ':' + port);
  }
  return this->clientSocket;
}

int TcpClient::fetchPossibleAddresses(const char* server, const char* port) {
  // This function is designed to be called when there is no active connection
  assert(this->possibleAddresses == nullptr);
  // Fetch all available addresses and store results in object attributes
  int error = ::getaddrinfo(server, port, &this->clientSocketSettings
    , &this->possibleAddresses);
  // If getaddrinfo failed, raise an exception
  if (error) {
    error = SocketError::CANT_FETCH_ADDRESSES;
  } else {
    error = SocketError::OK_SOCKET;
  }
  return error;
}

int TcpClient::openSocketWithServer(const char* server, const char* port) {
  assert(this->clientSocket.getFileDescriptor() == -1);
  int error = SocketError::NOT_OK_SOCKET;
  // Traverse the available addresses and select the first one that works
  for (const struct addrinfo* address = this->possibleAddresses; address;
      address = address->ai_next) {
    // Try to open a socket using this address result
    int error = this->clientSocket.create(address);

    // If we could open the socket
    if (!error) {
      // This address is OK, stop searching and use this socket
      // Ask the operating system to establish a connection on this socket
      error = this->clientSocket.connect(address);
      if (!error) {
        return error;
      }
    }
  }

  return error;
}
