// Copyright © Ignacio Robles Mayorga

#include "./DatabaseWebApp.hpp"
#include "HttpRequestHandlers/ConsultVacationHandler.hpp"
#include "HttpRequestHandlers/ConsultSalaryHandler.hpp"
#include "HttpRequestHandlers/ConsultAnnotationsHandler.hpp"

// TODO: include all requestHandlers

DatabaseWebApp::DatabaseWebApp() {
  this->databaseApi = new DatabaseAPI();
  this->initHandlers();
}

DatabaseWebApp::~DatabaseWebApp() {
  delete this->databaseApi;
}

void DatabaseWebApp::initHandlers() {
  this->requestHandlers.push_back(new ConsultVacationHandler(this->databaseApi));
  this->requestHandlers.push_back(new ConsultSalaryHandler(this->databaseApi));
  this->requestHandlers.push_back(new ConsultAnnotationsHandler(this->databaseApi));
}

bool DatabaseWebApp::start() {
  return true;
}

bool DatabaseWebApp::run(HttpRequest& request, HttpResponse& response) {
  for (auto& handler : this->requestHandlers) {
    if (handler->canHandle(request, response)) {
      return true;
    }
  }
  return false;
}