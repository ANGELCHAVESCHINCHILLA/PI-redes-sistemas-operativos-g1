// Copyright © 2023 Camilo Suárez Sandí

#include "HttpServer.hpp"

#include <iostream>

HttpServer::HttpServer() {
  //
}

HttpServer::~HttpServer() {
  //
}

void HttpServer::run(const std::string& request, std::string& response
    , Socket& client) {
  HttpRequest http_request(request);
  HttpResponse http_response(response);

  for (HttpApp* app : this->apps) {
    if (app->run(http_request, http_response)) {
      break;
    }
  }
};
