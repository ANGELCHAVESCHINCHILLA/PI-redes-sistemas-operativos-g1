// Copyright © 2023 Camilo Suárez Sandí

#include "EditUserHandler.hpp"

#include <jsoncpp/json/json.h>

#include "../../common/Log.hpp"

EditUserHandler::EditUserHandler(FileSystemAPI* api)
    : FileSystemRequestHandler(api) {
}

EditUserHandler::~EditUserHandler() {
}

bool EditUserHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "PUT" &&
      request.getTarget().getPath() == "/auth/user") {
    try {
      Json::Reader reader;
      Json::Value root;

      if (!reader.parse(request.getBody(), root)) {
        throw std::runtime_error("Can't parse the json.");
      }

      std::string username = root["username"].asString();
      std::string password = root["password"].asString();
      std::string salt = root["salt"].asString();
      int type = root["type"].asInt();

      if (!this->fileSystemApi->userExists(username) ||
          !this->fileSystemApi->editUser(username, password, salt, type)) {
        throw std::runtime_error("User doesn't exist.");
      }

      response.setStatusCode(200);
      Log::getInstance().write(Log::DEBUG, "EditUserHandler", "Edit User: Successful");
    } catch (const std::runtime_error& error) {
      Log::getInstance().write(
          Log::WARNING, "EditUserHandler", error.what());
      response.setStatusCode(401);
      response.getBody() << error.what();
    } catch (const Json::LogicError& error) {
      Log::getInstance().write(
          Log::WARNING, "EditUserHandler", error.what());
      response.setStatusCode(401);
      response.getBody() << error.what();
    }

    return true;
  }

  return false;
}
