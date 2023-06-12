// Copyright © 2023 Camilo Suárez Sandí

#include "RemoveUserHandler.hpp"

#include <jsoncpp/json/json.h>

#include "../../common/Log.hpp"

RemoveUserHandler::RemoveUserHandler(FileSystemAPI* api)
    : FileSystemRequestHandler(api) {
}

RemoveUserHandler::~RemoveUserHandler() {
}

bool RemoveUserHandler::canHandle(
    HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "DELETE" &&
      request.getTarget().getPath() == "/auth/user") {
    try {
      Json::Reader reader;
      Json::Value root;

      if (!reader.parse(request.getBody(), root)) {
        throw std::runtime_error("Can't parse the json.");
      }

      std::string username = root["username"].asString();

      if (!this->fileSystemApi->userExists(username) &&
          !this->fileSystemApi->removeUser(username)) {
        throw std::runtime_error("User doesn't exist.");
      }

      response.setStatusCode(200);
    } catch (const std::runtime_error& error) {
      Log::getInstance().write(
          Log::MessageType::WARNING, "RemoveUserHandler", error.what());
      response.setStatusCode(401);
      response.getBody() << error.what();
    } catch (const Json::LogicError& error) {
      Log::getInstance().write(
          Log::MessageType::WARNING, "RemoveUserHandler", error.what());
      response.setStatusCode(401);
      response.getBody() << error.what();
    }

    return true;
  }

  return false;
}
