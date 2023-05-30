// Copyright © 2023 Camilo Suárez Sandí

#ifndef SHARED_SOCKET_HPP_
#define SHARED_SOCKET_HPP_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <string>

/**
 * @brief A wrapper class for a socket.
 *
 */
struct SharedSocket {
 public:
  int fd;
  struct sockaddr_in addr;

  /**
   * @brief Default constructor.
   *
   */
  SharedSocket();

  /**
   * @brief Destructor. Closes the socket.
   *
   */
  ~SharedSocket();

  // Copy Constructor
  SharedSocket(const SharedSocket& other) = delete;

  // Copy Assignment Operator
  SharedSocket& operator=(const SharedSocket& other) = delete;

  // Move Constructor
  SharedSocket(SharedSocket&& other) = delete;

  // Move Assignment Operator
  SharedSocket& operator=(SharedSocket&& other) = delete;

  void close();
};

#endif  // SHARED_SOCKET_HPP_
