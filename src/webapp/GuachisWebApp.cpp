// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suarez Sandí

#include "GuachisWebApp.hpp"
#include <iostream>

#include "HttpRequestHandlers/ValidateHandler/ValidateHandler.hpp"
#include "HttpRequestHandlers/UserAdminHandler/UserAdminHandler.hpp"
#include "HttpRequestHandlers/WebLogHandler.hpp"

GuachisWebApp::GuachisWebApp() {
  this->requestHandlers.push_back(new UserAdminHandler());
  this->requestHandlers.push_back(new StaticHandler());
  this->requestHandlers.push_back(new UserAdminHandler());
  this->requestHandlers.push_back(new LoginHandler());
  this->requestHandlers.push_back(new QueryHandler());
  this->requestHandlers.push_back(new ValidateHandler());
  this->requestHandlers.push_back(new WebLogHandler());
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

// Aks each handler if can handle the request
bool GuachisWebApp::run(HttpRequest& request, HttpResponse& response) {
  for (auto & requestHandler : this->requestHandlers) {
    if (requestHandler->canHandle(request, response)) {
      return true;
    }
  }
  return false;
}
