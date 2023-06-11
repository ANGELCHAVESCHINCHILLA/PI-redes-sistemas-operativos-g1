// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suárez Sandí

#include "StaticHandler.hpp"
#include <iostream>

bool StaticHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath() == "/") {
      if (this->servePage(request, response, "login.html")) {
        return true;
      }
    }

    if (request.getTarget().getPath().rfind("/index.html", 0) == 0) {
      if (this->servePage(request, response, "index.html")) {
        return true;
      }
    }

    if (request.getTarget().getPath().rfind("/solicitudes", 0) == 0) {
      if (this->servePage(request, response, "solicitudes.html")) {
        return true;
      }
    }

    if (request.getTarget().getPath().rfind("/solicitar_vacaciones", 0) == 0) {
      if (this->servePage(
              request, response, "form_solicitar_vacaciones.html")) {
        return true;
      }
    }
    if (request.getTarget().getPath().rfind("/verificar_constancia", 0) == 0) {
      if (this->servePage(
              request, response, "verificar_constancia.html")) {
        return true;
      }
    }
    if (request.getTarget().getPath().rfind("/add_annotation", 0) == 0) {
      if (this->servePage(
              request, response, "supervisory/add_annotation.html")) {
        return true;
      }
    }

    if (this->serveStatic(request, response)) {
      return true;
    }
  }

  return false;
}

void StaticHandler::redirect(HttpResponse& response
    , const std::string& target) const {
  response.setStatusCode(302);
  response.setHeader("Location", target);
}