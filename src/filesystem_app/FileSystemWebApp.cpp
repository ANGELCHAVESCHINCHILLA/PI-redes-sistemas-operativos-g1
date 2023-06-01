// Copyright © 2023 David Cerdas Alvarado

#include "FileSystemWebApp.hpp"

#include <fstream>
#include <iostream>

#include <jsoncpp/json/json.h>

FileSystemWebApp::FileSystemWebApp() {
  // this->requestHandlers.push_back(new LoginHandler());
    this->fileSystemApi = new FileSystemAPI();
}

FileSystemWebApp::~FileSystemWebApp() {
    delete this->fileSystemApi;
}



bool FileSystemWebApp::start() {
  //

  return true;
}

// TODO(david): module method

bool FileSystemWebApp::run(HttpRequest& request, HttpResponse& response) {
  // Login
  if (request.getMethod() == "POST" && request.getTarget().getPath() == "/login") {

    std::string body = request.getBody();

    // Parse body to JSON
    Json::Value requestBody;
    Json::Reader reader;
    // May I handle errors checking this? Is it necessary? Is it even possible?
    reader.parse(body, requestBody);

    // Get values
    std::string username = requestBody["username"].asString();
    std::string password = requestBody["password"].asString();

    // Auth by API
    bool isAuthenticated =  this->fileSystemApi->authenticateUser(username, password);

    int statusCode;
    std::string responseBody;
    if (isAuthenticated) {
      statusCode = 200;
      responseBody = "Successfully";
    } else {
      statusCode = 400;
      responseBody = "Failed";
    }
    response.setHeader("Content-Type", "text/plain");
    response.setStatusCode(statusCode);
    response.getBody() << responseBody;

    response.buildResponse();
    // Send
    return true;
  }
  // Add User
  if (request.getMethod() == "POST" && request.getTarget().getPath() == "/adduser") {

    std::string body = request.getBody();

    // Parse body to JSON
    Json::Value requestBody;
    Json::Reader reader;
    reader.parse(body, requestBody);

    // Get values
    std::string username = requestBody["username"].asString();
    std::string password = requestBody["password"].asString();
    int type = requestBody["type"].asInt();

    // Auth by API
    bool isAdded =  this->fileSystemApi->addUser(username, password, type);

    int statusCode;
    std::string responseBody;
    if (isAdded) {
      statusCode = 200;
      responseBody = "Successfully";
    } else {
      statusCode = 400;
      responseBody = "Failed";
    }
    response.setHeader("Content-Type", "text/plain");
    response.setStatusCode(statusCode);
    response.getBody() << responseBody;

    response.buildResponse();
    // Send
    return true;
  }
  // TODO: remove this get after debugging stage
  if (request.getMethod() == "GET" && request.getTarget().getPath() == "/viewfs") {


    response.setHeader("Content-Type", "text/plain");
    response.setStatusCode(200);
    response.getBody() << this->fileSystemApi->viewFS();

    response.buildResponse();
    // Send
    return true;
  }

  return false;
}

