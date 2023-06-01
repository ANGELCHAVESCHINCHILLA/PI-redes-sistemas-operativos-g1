// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suarez Sandí

#include "GuachisWebApp.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

GuachisWebApp::GuachisWebApp() {
  this->requestHandlers.push_back(new StaticHandler());
  this->requestHandlers.push_back(new LoginHandler());
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
  for (size_t index = 0; index < this->requestHandlers.size(); ++index) {
    if (this->requestHandlers[index]->canHandle(request, response)) {
      return true;
    }
  }

  return false;
}
