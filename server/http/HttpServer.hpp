// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Copyright 2022 Esteban Iglesias Vargas. Universidad de Costa Rica.
// Copyright 2022 Angel Chaves Chinchilla. Universidad de Costa Rica.
// Copyright 2022 Camilo Suarez Sandi. Universidad de Costa Rica.
// Copyright 2022 Ignacio Robles Mayorga. Universidad de Costa Rica.

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <iostream>
#include <vector>

#include "HttpConnHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "TcpServer.hpp"

#define DEFAULT_PORT "8080"

class HttpApp;

/// TODO: Documentation
class HttpServer : TcpServer {
  DISABLE_COPY(HttpServer);

 protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;

  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;

  /// Chain of registered web applications. Each time an incoming HTTP request
  /// is received, the request is provided to each application of this chain.
  /// If an application detects the request is for it, the application will
  /// call the httpResponse.send() and the chain stops. If no web app serves
  /// the request, the not found page will be served.
  /// @brief Applications chained to the server
  std::vector<HttpApp*> applications;

  /// @brief Amount of handlers to be created
  size_t handlersCount;

  /// @brief Handlers created
  std::vector<HttpConnHandler*> handlers;

  /// @brief A client/socket queue
  Queue<Socket> clients;

 public:
  /// Destructor
  ~HttpServer();

  /// Get instance
  static HttpServer& getInstance();

  /// Registers a web application to the chain
  void chainWebApp(HttpApp* application);

  /// Start the web server for listening client connections and HTTP requests
  int start(int argc, char* argv[]);

  /// Stop the web server. The server may stop not immediately. It will stop
  /// for listening further connection requests at once, but pending HTTP
  /// requests that are enqueued will be allowed to finish
  void stop();

  /// Infinetelly listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);

  /**
   * @brief stops the server from listening
   *
   * @param signal is the signal (either Ctrl + C or a kill) received
   */
  static void stopServer(int signal);

 protected:
  /// Constructor
  HttpServer();

  /// Create HttpConnHandlers and initialize
  void createHttpConnHandlers();

  /// Wit for HttpConnHandlers and then destroy them
  void destroyHttpConnHandlers();

  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);

  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
};


#endif  // HTTPSERVER_H
