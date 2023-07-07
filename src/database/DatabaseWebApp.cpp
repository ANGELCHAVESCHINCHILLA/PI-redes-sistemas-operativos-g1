// Copyright © Ignacio Robles Mayorga

#include "./DatabaseWebApp.hpp"
#include "HttpRequestHandlers/ConsultVacationHandler.hpp"
#include "HttpRequestHandlers/ConsultSalaryHandler.hpp"
#include "HttpRequestHandlers/ConsultAnnotationsHandler.hpp"
#include "HttpRequestHandlers/ConsultRequestsByUserHandler.hpp"
#include "HttpRequestHandlers/ConsultRequestsByAreaHandler.hpp"
#include "HttpRequestHandlers/ConsultRequestsByIDHandler.hpp"
#include "HttpRequestHandlers/MakeRequestHandler.hpp"
#include "HttpRequestHandlers/CheckRequestHandler.hpp"
#include "HttpRequestHandlers/JobDataHandler.hpp"
#include "HttpRequestHandlers/PersonalDataHandler.hpp"
#include "HttpRequestHandlers/DatabaseLogHandler.hpp"
#include "HttpRequestHandlers/MakeAnnotationHandler.hpp"

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
  this->requestHandlers.push_back(new CheckRequestHandler(this->databaseApi));
  this->requestHandlers.push_back(new JobDataHandler(this->databaseApi));
  this->requestHandlers.push_back(new PersonalDataHandler(this->databaseApi));
  this->requestHandlers.push_back(new DatabaseLogHandler(this->databaseApi));
  this->requestHandlers.push_back(new MakeAnnotationHandler(this->databaseApi));
}

bool DatabaseWebApp::start() {
  return true;
}

bool DatabaseWebApp::run(HttpRequest& request, HttpResponse& response) {
  Log::getInstance().write(Log::INFO, "DatabaseWebApp", request.getTarget().getPath());
  for (auto& handler : this->requestHandlers) {
    if (handler->canHandle(request, response)) {
      return true;
    }
  }
  return false;
}
