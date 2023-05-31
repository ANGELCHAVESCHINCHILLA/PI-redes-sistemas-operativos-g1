// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suarez Sandí

#include "GuachisWebApp.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

GuachisWebApp::GuachisWebApp() {
  this->requestHandlers.push_back(new LoginHandler);
}

GuachisWebApp::~GuachisWebApp() {
  const size_t count = this->requestHandlers.size();
  for (size_t index = 0; index < count; ++index) {
    delete this->requestHandlers[index];
  }
}


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
  for (size_t index = 0; index < this->requestHandlers.size(); ++index) {
    if (this->requestHandlers[index]->canHandle(request, response)) {
      return true;
    }
  }

  // Serve styles
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/styles/styles.css") {
    return HttpRequestHandler::serveStatic(request, response, "/web/styles/styles.css",
                             "text/css");
  }

  return false;
}

