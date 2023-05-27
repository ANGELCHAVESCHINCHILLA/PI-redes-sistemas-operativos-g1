// Copyright © 2023 Camilo Suárez Sandí

#include "HttpServer.hpp"

#include <iostream>

HttpServer::HttpServer() {
  //
}

HttpServer::~HttpServer() {
  //
}

int HttpServer::start(const std::string& address, int port) {
  int error = SocketError::OK;

  error = this->server_socket.create();

  if (!error) {
    error = this->server_socket.bind(address, port);
  }

  if (!error) {
    error = this->server_socket.listen();
  }

  error = this->acceptConnections();
}

void HttpServer::handleClientConnection(const std::string& request, std::string& response
    , Socket& client) {
// While the same client asks for HTTP requests in the same connection
  // while (true) {
    // Revisar si el parse falla, en teoría no debería cerrarse la conexión aún
    HttpRequest http_request(request);
    HttpResponse http_response(response);

    for (HttpApp* app : this->apps) {
      if (app->run(http_request, http_response)) {
        break;
      }
    }

    // Dar la oportunidad a las apps que se encarguen del request
    const bool handled = this->route(http_request, http_response);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || HTTP_VERSION == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client.close();
      // break;
    }
  //   break;
  // }
}

bool HttpServer::route(const HttpRequest& request, HttpResponse& response) {
  for (HttpApp* app : this->apps) {
    if (app->run(request, response)) {
      return true;
    }
  }
  return false;
}