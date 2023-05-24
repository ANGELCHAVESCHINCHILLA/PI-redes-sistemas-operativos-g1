// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <netdb.h>

#include "common.hpp"

class NetworkAddress;
class Socket;

// struct addrinfo {
//     int ai_flags;           // Opciones adicionales
//     int ai_family;          // Familia de direcciones (IPv4, IPv6, etc.)
//     int ai_socktype;        // Tipo de socket (TCP, UDP, etc.)
//     int ai_protocol;        // Protocolo de transporte (IP, ICMP, etc.)
//     socklen_t ai_addrlen;   // Longitud de la dirección
//     struct sockaddr* ai_addr;   // Puntero a la dirección
//     char* ai_canonname;     // Nombre canónico del host
//     struct addrinfo* ai_next;   // Puntero al siguiente resultado en la lista
// };

class TcpServer {
  DISABLE_COPY(TcpServer);

 public:
  /// Default number of pending connection requests allowed in the queue
  static const int defaultConnectionQueueCapacity = 10;

 protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;
  /// Available network addresses for listening in current host
  struct addrinfo* availableAddresses = nullptr;
  /// Selected network address for this TCP server
  const struct addrinfo* selectedAddress = nullptr;
  /// Socket for listening for incoming connection requests
  // Indica el file descriptor del socket ya que en linux los sockets son vistos
  // como archivos. se utiliza para identificar un socket abierto y establecer
  // comunicación con él.
  int connectionRequestSocket = -1;
  /// Maximum number of pending connection requests allowed in the queue
  /// This queue is called backlog in the Unix sockets manual (man listen)
  int connectionQueueCapacity = defaultConnectionQueueCapacity;

 public:
  /// Constructor
  TcpServer();
  /// Destructor
  ~TcpServer();
  /// Infinetelly listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);
  /// Stop listening for client connections. This method should be called when
  /// the server stops, for example, when a user presses Ctrl+C, sends a kill
  /// signal, or when the operating system is shutting down
  void stopListening();
  /// Start listening for client connections at the given port
  /// This is a non blocking method. After calling this method, the OS will
  /// just start feeding the queue with connection requests from clients
  /// @throw std::runtime_error on any error condition
  void listenForConnections(const char* port);
  /// Repeatedly and sequentially accept all incoming connection requests.
  /// For each accepted connection request, the pure virtual method @a
  /// handleClientConnection() is called
  void acceptAllConnections();
  /// Accept the next pending incoming connection request on the queue.
  /// Calls the pure virtual method @a handleClientConnection() to handle it.
  /// If queue is empty, the caller thread will be blocked
  void acceptConnectionRequest();
  /// Get the network address (IP and port) where this server is listening
  NetworkAddress getNetworkAddress() const;

 protected:
  /// Fetch all available network addresses where we can listen with this port
  void fetchAvailableAddresses(const char* port);
  /// Get a socket for the first available address that works for the given port
  void openConnectionRequestSocket(const char* port);
  /// This method is called each time a client connection request is accepted.
  /// Inherited classes must override this method, process the connection
  /// request, and finally close the connection socket
  virtual void handleClientConnection(Socket& client) = 0;
};

#endif  // TCPSERVER_H
