// Copyright © 2023 Camilo Suárez Sandí

#include "HttpServer.hpp"

#include <iostream>

HttpServer* HttpServer::instance = nullptr;

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

HttpServer* HttpServer::getInstance() {
  if (HttpServer::instance == nullptr) {
    HttpServer::instance = new HttpServer();
  }

  return HttpServer::instance;
}

void HttpServer::onSignal(int signal) {
  std::cout << "\nServer stopping\n";

  HttpServer* instance = HttpServer::getInstance();

  instance->stop();
}

void HttpServer::stop() {
  this->server_socket.close();
}

void HttpServer::route(const std::string& request, std::string& response) {
  HttpRequest http_request(request);
  HttpResponse http_response(response);

  for (HttpApp* app : this->apps) {
    if (app->run(http_request, http_response)) {
      response = http_response.toString();

      break;
    }
  }
};

void HttpServer::addApp(HttpApp* app) {
  this->apps.push_back(app);
}
