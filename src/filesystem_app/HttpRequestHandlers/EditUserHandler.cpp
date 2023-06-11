// Copyright © 2023 Camilo Suárez Sandí

#include "EditUserHandler.hpp"

#include <jsoncpp/json/json.h>

EditUserHandler::EditUserHandler(FileSystemAPI* api) : FileSystemRequestHandler(api) {
}

EditUserHandler::~EditUserHandler() {
}

bool EditUserHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  return false;
}
