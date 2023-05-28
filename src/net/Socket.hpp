// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <memory>
#include <string>

#include "../common/common.hpp"

enum SocketError {
  OK_SOCKET = EXIT_SUCCESS,
  NOT_OK_SOCKET = EXIT_FAILURE,
  //
  CANT_CREATE_SOCKET,
  CANT_BIND_SOCKET,
  CANT_LISTEN_SOCKET,
  CANT_ACCEPT_SOCKET,
  CANT_CONNECT_SOCKET,
  //
  CANT_SEND_DATA,
  CANT_RECEIVE_DATA,
  
  CANT_FETCH_ADDRESSES,
};

struct SharedSocket;
/**
 * @brief A wrapper class for a socket.
 *
 */
class Socket {
  /// Objects of this class can be copied, but avoid innecesary copies
  DECLARE_RULE4(Socket, default);

 protected:
  /// Copies of this object share the same socket file descriptor and buffers
  /// The sharedSocket contents all the info of this Socket
  std::shared_ptr<SharedSocket> sharedSocket;

 public:
  /**
   * @brief Default constructor.
   *
   */
  Socket();

  /**
   * @brief Destructor. Closes the socket file descriptor JUST if this is the
   * last object using a shared socket
   *
   */
  ~Socket() = default;

 public:  // Access
  int getFileDescriptor() const;

 public:  // Setters
  void setFileDescriptor(int fd);

  /**
   * @brief Creates a new socket.
   *
   * @return int A SocketError code.
   */
  int create();

  int create(const struct addrinfo* address);

  /**
   * @brief Binds a socket to an address specified by the host and the port.
   *
   * @param address The address of the socket.
   * @param port The port of the socket.
   * @return int A SocketError code.
   */
  int bind(const std::string& address, int port);

  int bind(const struct addrinfo* address);

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

  int allowReuse();

  /**
   * @brief Closes the socket.
   *
   */
  void close();
};

#endif  // SOCKET_HPP_
