//
// Created by David Cerdas Alvarado on 01/06/23.
//

#include "AddUserHandler.hpp"

#include <jsoncpp/json/json.h>

#include "../../common/Log.hpp"

AddUserHandler::AddUserHandler(FileSystemAPI* fileSystemApi)
    : FileSystemRequestHandler(fileSystemApi) {
}

bool AddUserHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "POST" &&
      (request.getTarget().getPath() == "/adduser" ||
          request.getTarget().getPath() == "/auth/user")) {
    Log::getInstance().write(
        Log::INFO, "AddUserHandler", request.getTarget().getPath());
    const std::string& body = request.getBody();
    Json::Value requestBody;
    Json::Reader reader;
    // Parse to JSON to easy manipulation
    bool parsed = reader.parse(body, requestBody);

    int statusCode;
    std::string responseBody;

    if (parsed) {
      // Get values
      std::string username = requestBody["username"].asString();
      std::string password = requestBody["password"].asString();
      std::string salt = requestBody["salt"].asString();
      int type = requestBody["type"].asInt();

      if (!this->fileSystemApi->userExists(username) &&
          this->fileSystemApi->addUser(username, password, salt, type)) {
        statusCode = 200;
        responseBody = "Successfully";
      } else {
        statusCode = 400;
        responseBody = "Failed";
      }
    } else {
      statusCode = 400;
      responseBody = "JSON ERROR";
      Log::getInstance().write(
          Log::ERROR, "AddUserHandler", "JSON Parsing Error");
    }
    response.setHeader("Content-Type", "text/plain");
    response.setStatusCode(statusCode);
    response.getBody() << responseBody;

    response.buildResponse();
    // Send
    Log::getInstance().write(
        Log::INFO, "AddUserHandler", "Response Sent with body:" + responseBody);
    return true;
  }
  return false;
}
