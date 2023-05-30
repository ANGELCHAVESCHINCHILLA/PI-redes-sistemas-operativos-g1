// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suarez Sandí

#include "GuachisWebApp.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

GuachisWebApp::GuachisWebApp() {}

GuachisWebApp::~GuachisWebApp() {}


bool GuachisWebApp::start() {
  //

  return true;
}

/*
TODO(Any): Modularizar el código: Sugerencia:
Utilizar el patrón Cadena de responsabilidad

* Un LogginHandler: Solicitudes de logueo, servir los iconos del Login y el JS.
Además leer lo que el usuario escriba en el Form
* StaticHandler: Podría servir el index.html, modal y otros estáticos.
* Un QueryHandler: Sirve las consultas que se realicen, entonces este se encarg
aría de ir a la base de datos, construir la consulta y enviarla al cliente.
* RequestHandler: Se encargaría de manejar las solicitudes:
  - Servir los forms y manejar lo que el usuario escriba en ellos
    (escribirlo en base de datos o donde sea necesario)

Entonces un HttpRequest irá por cada uno de estos hasta que alguno se haga cargo.
*/
// TODO(Any): Servir el resto de páginas
bool GuachisWebApp::run(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET" && request.getTarget().getPath() == "/") {
    return this->serveStatic(request, response, "/web/pages/login.html",
                             "text/html");
  }

  // Serve styles
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/styles/styles.css") {
    return this->serveStatic(request, response, "/web/styles/styles.css",
                             "text/css");
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

bool GuachisWebApp::serveStatic(HttpRequest& httpRequest,
                                HttpResponse& httpResponse,
                                const std::string& path,
                                const std::string& contentType,
                                const std::string& charset) {
  (void)httpRequest;

  // Set the content type and the character encoding
  httpResponse.setStatusCode(200);
  httpResponse.setHeader("Content-Type", contentType + "; charset=" + charset);
  httpResponse.setHeader("Server", "AttoServer v1.0");

  // Read the file and write the text in the HTTP response
  GuachisWebApp::readFile(httpResponse.getBody(), path);

  return httpResponse.buildResponse();
}

void GuachisWebApp::readFile(std::ostream& output,
                                 const std::string& path) {
  // Get the path of the project directory
  std::filesystem::path current_path = std::filesystem::current_path();

  // Add the file path to the path of the project directory
  current_path += path;

  // Read the file in the path
  std::ifstream file;

  file.open(current_path);

  if (file.is_open()) {
    // Read every character and write it to the output stream.
    char c = '\0';

    while (file.get(c)) {
      output << c;
    }
  }

  file.close();
}