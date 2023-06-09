// Copyright © 2023 David Cerdas Alvarado

#include "FileSystemWebApp.hpp"

#include <iostream>

#include "./HttpRequestHandlers/AddUserHandler.hpp"
#include "./HttpRequestHandlers/AuthHandler.hpp"
#include "./HttpRequestHandlers/PermissionsHandler.hpp"
#include "./HttpRequestHandlers/SaltHandler.hpp"
#include "../common/Log.hpp"

FileSystemWebApp::FileSystemWebApp() {
  this->fileSystemApi = new FileSystemAPI();
  this->initHandlers();
}

FileSystemWebApp::~FileSystemWebApp() {
  delete this->fileSystemApi;
}

void FileSystemWebApp::initHandlers() {
  this->requestHandlers.push_back(new AuthHandler(this->fileSystemApi));
  this->requestHandlers.push_back(new AddUserHandler(this->fileSystemApi));
  this->requestHandlers.push_back(new PermissionsHandler(this->fileSystemApi));
  this->requestHandlers.push_back(new SaltHandler(this->fileSystemApi));
}

bool FileSystemWebApp::start() {
  return true;
}

bool FileSystemWebApp::run(HttpRequest& request, HttpResponse& response) {
  Log::getInstance().write(Log::INFO, "RequestReceived", request.getTarget().getPath());
  for (auto& handler : this->requestHandlers) {
    if (handler->canHandle(request, response)) {
      return true;
    }
  }

  // TODO: remove this get after debugging stage
  if (request.getMethod() == "GET" &&
      request.getTarget().getPath() == "/viewfs") {

    response.setHeader("Content-Type", "text/plain");
    response.setStatusCode(200);
    response.getBody() << this->fileSystemApi->viewFS();

    response.buildResponse();
    // Send
    return true;
  }

  return false;
}
