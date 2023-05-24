// Copyright © 2023 Camilo Suárez Sandí

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <string>

enum SocketError {
  OK = EXIT_SUCCESS,
  NOT_OK = EXIT_FAILURE,
  //
  CANT_CREATE_SOCKET,
  CANT_BIND_SOCKET,
  CANT_LISTEN_SOCKET,
  CANT_ACCEPT_SOCKET,
  CANT_CONNECT_SOCKET,
  //
  CANT_SEND_DATA,
  CANT_RECEIVE_DATA,
};

/**
 * @brief A wrapper class for a socket.
 *
 */
class Socket {
 private:
  int fd;
  struct sockaddr_in addr;

 public:
  /**
   * @brief Default constructor.
   *
   */
  Socket();

  /**
   * @brief Destructor. Closes the socket.
   *
   */
  ~Socket();

  // Copy Constructor
  Socket(const Socket& other) = delete;

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
  int listen();

  /**
   * @brief The socket accepts an incoming connection on the listening stream
   * socket.
   *
   * @param socket A socket connected to the peer socket that performed a
   * connection.
   * @return int A SocketError code.
   */
  int accept(Socket& socket);

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
  int send(const std::string& data);

  /**
   * @brief Receive data from the socket.
   *
   * @param data The received data.
   * @return int A SocketError code.
   */
  int receive(std::string& data);

  /**
   * @brief Closes the socket.
   *
   */
  void close();
};

#endif  // SOCKET_HPP_