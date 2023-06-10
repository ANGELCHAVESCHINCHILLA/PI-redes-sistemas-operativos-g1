// Copyright © 2023 Ángel Chaves Chinchilla

#include "LoginHandler.hpp"
#include <iostream>

#include "../../../configuration.hpp"
#include "../../../net/TcpClient.hpp"
#include "../../../http/HttpServer.hpp"

bool LoginHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "POST") {
    if (request.getTarget().getPath() == "/login") {
      // TODO: QUitar este return cuando ya la constrasea venga encriptada.
      return true;
      try {
        // send request to and receive response from data base server
        return this->callFSToLogin(request, response);
      } catch (const std::runtime_error& error) {
        std::cerr << error.what() << ".\n";
        response.setStatusCode(401);
      }
    }
  }
  return false;
}

bool LoginHandler::callFSToLogin(HttpRequest& request, HttpResponse& response) {
  Configuration& configuration = Configuration::getInstance();
  // IP adress of file system server
  std::string db_address = configuration.getServer("fs").address;
  // port in which file system server is listenning
  std::string db_port = std::to_string(configuration.getServer("fs").port);
  // request to be send to file system server
  HttpRequest FSRequest;
  // Construct request with our needs
  FSRequest.setMethod("POST");
  FSRequest.setTarget("http://" + db_address + ":" + db_port + request.getTarget().getInput());
  FSRequest.setBody(request.getBody());

  // std::cout << "Request que se enviará a file system" << std::endl;
  // std::cout << DBRequest.toString() << std::endl;

  // Send request to file system and store its result in future
  auto future = HttpServer::fetch(FSRequest);

  // Get data received and create a HttResponse
  HttpResponse FSResponse = future.get();

  // Build our FSResponse
  response.setStatusCode(FSResponse.getStatusCode());
  response.getBody() << FSResponse.getBody().str();
  response.setHeader("Content-Type", "application/json");
  return response.buildResponse();
}

bool LoginHandler::serveAuthFailed(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse) {
  (void) httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(401);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-Type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Usuario o contraseña incorrecta";
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


