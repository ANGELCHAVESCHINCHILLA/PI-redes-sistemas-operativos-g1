// Copyright © Ignacio Robles Mayorga

#include "./DatabaseWebApp.hpp"
#include "HttpRequestHandlers/ConsultVacationHandler.hpp"
#include "HttpRequestHandlers/ConsultSalaryHandler.hpp"
#include "HttpRequestHandlers/ConsultAnnotationsHandler.hpp"
#include "HttpRequestHandlers/ConsultRequestsByUserHandler.hpp"
#include "HttpRequestHandlers/ConsultRequestsByAreaHandler.hpp"
#include "HttpRequestHandlers/ConsultRequestsByIDHandler.hpp"
#include "HttpRequestHandlers/MakeRequestHandler.hpp"

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
  this->requestHandlers.push_back(new ConsultRequestsByUserHandler(this->databaseApi));
  this->requestHandlers.push_back(new ConsultRequestsByAreaHandler(this->databaseApi));
  this->requestHandlers.push_back(new ConsultRequestsByIDHandler(this->databaseApi));
  this->requestHandlers.push_back(new MakeRequestHandler(this->databaseApi));
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