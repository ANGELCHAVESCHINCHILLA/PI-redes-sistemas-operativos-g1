// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suárez Sandí

#include "StaticHandler.hpp"
#include <iostream>

bool StaticHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET") {
    if (request.getTarget().getFullPath() == "/") {
      if (this->servePage(request, response, "login.html")) {
        return true;
      }
    }

    if (request.getTarget().getFullPath().rfind("/index.html", 0) == 0) {
      if (this->servePage(request, response, "index.html")) {
        return true;
      }
    }

    if (request.getTarget().getFullPath().rfind("/solicitudes", 0) == 0) {
      if (this->servePage(request, response, "solicitudes.html")) {
        return true;
      }
    }

    if (request.getTarget().getFullPath().rfind("/solicitar_vacaciones", 0) == 0) {
      if (this->servePage(
              request, response, "form_solicitar_vacaciones.html")) {
        return true;
      }
    }
    if (request.getTarget().getFullPath().rfind("/verificar_constancia", 0) == 0) {
      if (this->servePage(
              request, response, "verificar_constancia.html")) {
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