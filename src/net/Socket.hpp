// Copyright © 2023 Camilo Suárez Sandí

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <memory>
#include <string>

#include "SharedSocket.hpp"

/**
 * @brief A wrapper class for a socket.
 *
 */
class Socket {
 private:
  std::shared_ptr<SharedSocket> shared_socket;

 public:
  /**
   * @brief Default constructor.
   *
   */
  Socket();

  /**
   * @brief Destructor.
   *
   */
  ~Socket();

  // Copy Constructor
  Socket(const Socket& other);

  // Copy Assignment Operator
  Socket& operator=(const Socket& other) = delete;

  // Move Constructor
  Socket(Socket&& other) = delete;

  // Move Assignment Operator
  Socket& operator=(Socket&& other) = delete;

  /**
   * @brief Creates a new socket.
   *
   * @return int A SocketError code.
   */
  int create();

  /**
   * @brief Binds a socket to an address specified by the host and the port.
   *
   * @param address The address of the socket.
   * @param port The port of the socket.
   * @return int A SocketError code.
   */
  int bind(const std::string& address, int port);

  /**
   * @brief The socket will be used to accept connections for other sockets.
   *
   * @return int A SocketError code.
   */
  int listen() const;

  /**
   * @brief The socket accepts an incoming connection on the listening stream
   * socket.
   *
   * @param socket A socket connected to the peer socket that performed a
   * connection.
   * @return int A SocketError code.
   */
  int accept(Socket& socket) const;

  /**
   * @brief Connects the socket to a listening socket whose address is specified
   * by the host and the port.
   *
   * @param address The address of the listening socket.
   * @param port The port of the listening socket.
   * @return int A SocketError code.
   */
  int connect(const std::string& address, int port);

  /**
   * @brief Send data to the socket.
   *
   * @param data The sent data.
   * @return int A SocketError code.
   */
  int send(const std::string& data) const;

  /**
   * @brief Receive data from the socket.
   *
   * @param data The received data.
   * @return int A SocketError code.
   */
  int receive(std::string& data) const;

  /**
   * @brief Closes the socket.
   *
   */
  void close() const;
};

#endif  // SOCKET_HPP_
