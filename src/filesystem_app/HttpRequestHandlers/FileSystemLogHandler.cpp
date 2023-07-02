// Copyright © 2023 Camilo Suárez Sandí

#include "FileSystemLogHandler.hpp"

FileSystemLogHandler::FileSystemLogHandler(FileSystemAPI* api)
    : log_handler("log.log"), FileSystemRequestHandler(api) {
}

bool FileSystemLogHandler::canHandle(
    HttpRequest& request, HttpResponse& response) {
  if (this->log_handler.handleCount(request, response, "/log/fs/count")) {
    return true;
  }

  if (this->log_handler.handleFile(request, response, "/log/fs/file")) {
    return true;
  }

  return false;
}
