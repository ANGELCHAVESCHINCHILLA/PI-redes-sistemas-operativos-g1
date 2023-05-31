// Copyright © 2023 Ángel Chaves Chinchilla

#include "LoginHandler.hpp"


bool LoginHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET" && request.getTarget().getPath() == "/") {
    return this->serveStatic(request, response, "/web/pages/login.html",
                             "text/html");
  }

  // Serve Javascript for Login from a request like : GET /scripts/login.js
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/login.js") {
    return this->serveStatic(request, response, "/web/scripts/login.js",
                             "application/javascript");
  }

  // Serve person.png
  // GET /assets/images/person.png
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/assets/images/person.png") {
    return this->serveStatic(request, response, "/web/assets/images/person.png",
                             "image/png");
  }
  // Serve eye.png
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/assets/images/eye.png") {
    return this->serveStatic(request, response, "/web/assets/images/eye.png",
                             "image/png");
  }

  return false;
}

bool LoginHandler::validateUser(HttpRequest& request) {
  return true;
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