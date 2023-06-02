// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include "HttpServer.hpp"

#include <iostream>
#include <cassert>
#include "../common/Log.hpp"

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

int HttpServer::appendApp(HttpApp* application) {
  assert(application);
  this->apps.push_back(application);
  return 0;
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
  Log::getInstance().start();
  Log::getInstance().write(Log::INFO, "start","Server started");
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
  Log::getInstance().write(Log::INFO, "finish","Server closed");
  Log::getInstance().stop();

  return error;
}

// En este momento es serial, por lo tanto el server procesará una solicitud a
// la vez, se deben agregar HttpConnectionHandler si se quiere hacer concurrente
// TODO(everyone): Pensar en si es necesario agregar estos handlers.
void HttpServer::handleClientConnection(const std::string& request
    , std::string& response, Socket& client) {
  // Impresión para debug
  std::cout << "Solicitud realizada:\n" << request << std::endl;
// While the same client asks for HTTP requests in the same connection
  // while (true) {
    // Revisar si el parse falla, en teoría no debería cerrarse la conexión aún
    HttpRequest http_request(request);
    HttpResponse http_response(response);

    // Give the oportunity to apps to handle the client connection
    const bool handled = this->route(http_request, http_response);


    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || http_request.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client.close();
      // break;
    } else {
      // If the request was succesfull handled then send Httt Response to the
      // client
      if (client.send(http_response.getOutput()) != SocketError::OK_SOCKET) {
        // If could not sent data then close the connection
        std::cout << "No se logró enviar la respuesta \n" << std::endl;
        client.close();
      } else {
        std::cout << "Respuesta enviada: \n" << std::endl;
        std::cout << http_response.getOutput() << std::endl;
      }
    }
  //   break;
  // }
}

bool HttpServer::route(HttpRequest& request, HttpResponse& response) {
  for (HttpApp* app : this->apps) {
    // Ask to te app if it could handle the connection
    if (app->run(request, response)) {
      // Impresión para debug
      std::cout << "Logré manejar mi solicitud" << std::endl;
      return true;
    }
  }
  // If no one handle the connection then build a Serve Not Found response
  std::cout << "Voy a servir un NOT FOUND" << std::endl;
  return serveNotFound(request, response);
}

bool HttpServer::serveNotFound(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse) {
  (void) httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-Type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.getBody()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <p>The requested resouce was not found on this server.</p>\n"
      << "  <hr><p><a href=\"/\">Login</a></p>\n"
      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.buildResponse();
}
