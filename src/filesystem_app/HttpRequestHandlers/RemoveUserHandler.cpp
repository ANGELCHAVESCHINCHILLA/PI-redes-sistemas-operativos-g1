// Copyright © 2023 Camilo Suárez Sandí

#include "RemoveUserHandler.hpp"

#include <jsoncpp/json/json.h>

RemoveUserHandler::RemoveUserHandler(FileSystemAPI* api)
    : FileSystemRequestHandler(api) {
}

RemoveUserHandler::~RemoveUserHandler() {
}

bool RemoveUserHandler::canHandle(
    HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "DELETE" &&
      request.getTarget().getPath() == "/auth/user") {
    return true;
  }

  return false;
}
