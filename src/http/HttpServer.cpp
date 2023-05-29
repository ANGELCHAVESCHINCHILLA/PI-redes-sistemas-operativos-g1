// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include "HttpServer.hpp"

#include <iostream>

HttpServer& HttpServer::getInstance() {
  static HttpServer server;
  return server;
}


HttpServer::HttpServer() {
  //
}

HttpServer::~HttpServer() {
  //
}

void HttpServer::stopServer(int signal) {
  std::cerr << "Signal " << signal << " received" << std::endl;
  HttpServer::getInstance().stop();
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests
  this->stopListening();
}

int HttpServer::start(const std::string& address, int port) {
  int error = SocketError::OK_SOCKET;

  const std::string sport = std::to_string(port);

  error = this->fetchPossibleAddresses(sport.data());

  if (!error) {
    error = this->openServerSocket();
  }

  // if (!error) {
  //   error = this->server_socket.bind(address, port);
  // }

  if (!error) {
    error = this->server_socket.listen();
    std::cout << "Server running at http://" << address << ":" << port << "\n";
  }

  error = this->acceptConnections();
  std::cout << "Terminé de aceptar conexiones\n";


  return error;
}

// En este momento es serial, por lo tanto el server procesará una solicitud a
// la vez, se deben agregar HttpConnectionHandler si se quiere hacer concurrente
// TODO(everyone): Pensar en si es necesario agregar estos handlers.
void HttpServer::handleClientConnection(const std::string& request, std::string& response
    , Socket& client) {
  std::cout << "Solicitud realizada:\n" << request << std::endl;
// While the same client asks for HTTP requests in the same connection
  // while (true) {
    // Revisar si el parse falla, en teoría no debería cerrarse la conexión aún
    HttpRequest http_request(request);
    HttpResponse http_response(response);

    // Dar la oportunidad a las apps que se encarguen del request
    const bool handled = this->route(http_request, http_response);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || http_request.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client.close();
      // break;
    }
  //   break;
  // }
}

bool HttpServer::route(HttpRequest& request, HttpResponse& response) {
  for (HttpApp* app : this->apps) {
    if (app->run(request, response)) {
      return true;
    }
  }
  return false;
}
