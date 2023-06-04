// Copyright © Ignacio Robles Mayorga

#include "./DatabaseWebApp.hpp"
// TODO: include all requestHandlers

DatabaseWebApp::DatabaseWebApp() {
  // this->initHandlers();
  // this->database = Database::getInstance(path);
}

DatabaseWebApp::~DatabaseWebApp() {

}

bool DatabaseWebApp::start() {
  return true;
}

bool DatabaseWebApp::run(HttpRequest& request, HttpResponse& response) {
  /*
  for (auto& handler : this->requestHandlers) {
    if (handler->canHandle(request, response)) {
      return true;
    }
  }
  */
  return false;
}