// Copyright 2022 Esteban Iglesias Vargas. Universidad de Costa Rica.
// Copyright 2022 Angel Chaves Chinchilla. Universidad de Costa Rica.
// Copyright 2022 Camilo Suarez Sandi. Universidad de Costa Rica.
// Copyright 2022 Ignacio Robles Mayorga. Universidad de Costa Rica.

#ifndef HTTP_CONN_HANDLER_HPP_
#define HTTP_CONN_HANDLER_HPP_

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

#include "Consumer.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"

/// @brief class responsible for consuming sockets and serving requests from
/// said sockets
class HttpConnHandler : public Consumer<Socket> {
 private:
  /// reference to the aplications vector
  std::vector<HttpApp*> applications;

 public:
  DISABLE_COPY(HttpConnHandler);
  /// @brief Default constructor
  /// @param applications a reference of all the web application
  explicit HttpConnHandler(std::vector<HttpApp*>& applications);

  /// Default Destructor
  ~HttpConnHandler() = default;

  // Override from Thread
  int run() override;

  /// @brief override from Consume class, while the socket client has requests
  /// then serve that requests
  /// @param client The socket to serve
  void consume(Socket client) override;

  /// Called each time an HTTP request is received. Web server should analyze
  /// the request object and assemble a response with the response object.
  /// Finally send the response calling the httpResponse.send() method.
  /// @return true on success and the server will continue handling further
  /// HTTP requests, or false if server should stop accepting requests from
  /// this client (e.g: HTTP/1.0)
  bool handleHttpRequest(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// Sends a page for a non found resouce in this server. This method is called
  /// if none of the registered web applications handled the request.
  /// If you want to override this method, create a web app, e.g NotFoundWebApp
  /// that reacts to all URIs, and chain it as the last web app
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /// @brief Pushes stop condition to consuming queue
  void pushStopCondition();
};

#endif  // HTTP_CONN_HANDLER_HPP_
