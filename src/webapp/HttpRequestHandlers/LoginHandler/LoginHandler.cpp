// Copyright © 2023 Ángel Chaves Chinchilla

#include "LoginHandler.hpp"
#include <iostream>

#include "../../../common/Log.hpp"
#include "../../../configuration.hpp"
#include "../../../net/TcpClient.hpp"
#include "../../../http/HttpServer.hpp"

bool LoginHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "POST") {
    if (request.getTarget().getPath() == "/login") {
      try {
        // send request to and receive response from data base server
        if (this->callToFs(request, response, "POST", "application/json")) {
          Log::getInstance().write(Log::DEBUG, "LoginHandler", "Login: Successful");
        }
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::DEBUG, "LoginHandler", error.what());
        response.setStatusCode(401);
      }
      return true;
    }
  }
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath().rfind("/permissions") == 0) {
      try {
        // send request to and receive response from data base server
        if (this->callToFs(request, response, "GET", "text/plain")) {
          Log::getInstance().write(Log::DEBUG, "LoginHandler", "Permissions: Successful");
        }
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::DEBUG, "LoginHandler", error.what());
        response.setStatusCode(401);
      }
      return true;
    }
  }

  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath().rfind("/auth/salt") == 0) {
      try {
        // send request to and receive response from data base server
        if (this->callToFs(request, response, "GET", "application/json")) {
          Log::getInstance().write(Log::DEBUG, "LoginHandler", "Get Salt: Successful");
        }
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::DEBUG, "LoginHandler", error.what());
        response.setStatusCode(401);
      }
      return true;
    }
  }
  return false;
}

bool LoginHandler::callToFs(HttpRequest& request, HttpResponse& response
  , const std::string& method, const std::string& contentType) {
    Configuration& configuration = Configuration::getInstance();
  // IP adress of file system server
  std::string FSAddress = configuration.getServer("fs").address;
  // port in which file system server is listenning
  std::string FSPort = std::to_string(configuration.getServer("fs").port);
  // request to be send to file system server
  HttpRequest FSRequest;
  // Construct request with our needs
  FSRequest.setMethod(method);
  FSRequest.setTarget("http://" + FSAddress + ":" + FSPort + request.getTarget().getInput());
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
  response.setHeader("Content-Type", contentType);
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


