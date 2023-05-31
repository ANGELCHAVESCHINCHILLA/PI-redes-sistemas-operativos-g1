// Copyright © 2023 Ángel Chaves Chinchilla

#include "StaticHandler.hpp"

bool StaticHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (this->serveHtml(request, response)) {
    return true;
  }

  if (this->serveStyles(request, response)) {
    return true;
  }

  if (this->serveScripts(request, response)) {
    return true;
  }

  if (this->serveAssets(request, response)) {
    return true;
  }

  return false;
}

bool StaticHandler::serveHtml(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET" && request.getTarget().getPath() == "/") {
    return this->serveStatic(request, response, "/web/pages/login.html",
                             "text/html");
  }

  // GET /index.html HTTP/1.1
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/index.html") {
    return HttpRequestHandler::serveStatic(request, response, "/web/pages/index.html",
                             "text/html");
  }

  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/solicitudes.html") {
    return HttpRequestHandler::serveStatic(request, response, "/web/pages/solicitudes.html",
                             "text/html");
  }

  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/form_solicitar_vacaciones.html") {
    return HttpRequestHandler::serveStatic(request, response
      , "/web/pages/form_solicitar_vacaciones.html", "text/html");
  }

  return false;
}

bool StaticHandler::serveAssets(HttpRequest& request, HttpResponse& response) {
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

  // GET /assets/images/back.png HTTP/1.1
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/assets/images/back.png") {
    return this->serveStatic(request, response, "/web/assets/images/back.png",
                             "image/png");
  }
  return false;
}

bool StaticHandler::serveScripts(HttpRequest& request, HttpResponse& response) {
  // Serve Javascript for Login from a request like : GET /scripts/login.js
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/login.js") {
    return this->serveStatic(request, response, "/web/scripts/login.js",
                             "application/javascript");
  }

  // GET /scripts/buttonlistener.js HTTP/1.1
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/buttonlistener.js") {
    return this->serveStatic(request, response, "/web/scripts/buttonlistener.js",
                             "application/javascript");
  }

  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/formbuilder.js") {
    return this->serveStatic(request, response, "/web/scripts/formbuilder.js",
                             "application/javascript");
  }

  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/app.js") {
    return this->serveStatic(request, response, "/web/scripts/app.js",
                             "application/javascript");
  }

  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/scripts.js") {
    return this->serveStatic(request, response, "/web/scripts/script.js",
                             "application/javascript");
  }

  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/modal.js") {
    return this->serveStatic(request, response, "/web/scripts/modal.js",
                             "application/javascript");
  }

  // GET /scripts/libs/NumeroALetras.js HTTP/1.1
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/scripts/libs/NumeroALetras.js") {
    return this->serveStatic(request, response
                            , "/web/scripts/libs/NumeroALetras.js",
                             "application/javascript");
  }

  return false;
}

bool StaticHandler::serveStyles(HttpRequest& request, HttpResponse& response) {
  // Serve styles
  if (request.getMethod() == "GET" && request.getTarget().getPath()
      == "/styles/styles.css") {
    return HttpRequestHandler::serveStatic(request, response, "/web/styles/styles.css",
                             "text/css");
  }

  return false;
}
