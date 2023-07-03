// Copyright © 2023 Camilo Suárez Sandí

#include "DatabaseLogHandler.hpp"

DatabaseLogHandler::DatabaseLogHandler(DatabaseAPI* api)
    : log_handler("log.log"), DatabaseRequestHandler(api) {
}

bool DatabaseLogHandler::canHandle(
    HttpRequest& request, HttpResponse& response) {
  if (this->log_handler.handleCount(request, response, "/log/db/count")) {
    return true;
  }

  if (this->log_handler.handleFile(request, response, "/log/db/file")) {
    return true;
  }

  return false;
}
