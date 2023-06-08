// Copyright © 2023 Camilo Suárez Sandí

#include "SaltHandler.hpp"

SaltHandler::SaltHandler(FileSystemAPI* api) : FileSystemRequestHandler(api) {
}

SaltHandler::~SaltHandler() {
}

bool SaltHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  //
}
