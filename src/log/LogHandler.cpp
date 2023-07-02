// Copyright © 2023 Camilo Suárez Sandí

#include "LogHandler.hpp"

#include <fstream>

#include "../common/Log.hpp"

LogHandler::LogHandler(std::string path) : path(path) {
}

int LogHandler::read() {
  this->lines.clear();

  std::ifstream file(this->path);

  if (!file) {
    Log::getInstance().write(
        Log::ERROR, "LogHandler", "Can't read the log file");
    return -1;
  }

  size_t count = 0;

  std::string line;

  while (std::getline(file, line)) {
    count++;

    this->lines.push_back(line);
  }

  file.close();

  return 0;
}

size_t LogHandler::getLinesCount() {
  return this->lines.size();
}

std::string LogHandler::getLine(size_t offset) {
  return this->lines.at(offset);
}

bool LogHandler::handleCount(
    HttpRequest& request, HttpResponse& response, const std::string& url) {
  if (request.getTarget().getPath() == url) {
    int error = this->read();

    if (error == -1) {
      response.setStatusCode(500);
      return true;
    }

    size_t count = this->getLinesCount();

    response.getBody() << count;
    response.setStatusCode(200);

    return true;
  }

  return false;
}

bool LogHandler::handleFile(
    HttpRequest& request, HttpResponse& response, const std::string& url) {
  if (request.getTarget().getPath() == url) {
    int error = this->read();

    if (error == -1) {
      response.setStatusCode(500);
      return true;
    }

    try {
      size_t offset = std::stoi(request.getTarget().getQuery().at("offset"));
      size_t lines = std::stoi(request.getTarget().getQuery().at("lines"));

      for (size_t index = 0; index < lines; index++) {
        response.getBody() << this->getLine(offset + index) << "\n";
      }
    } catch (const std::out_of_range& exception) {
      Log::getInstance().write(Log::WARNING, "LogHandler",
          "Request is missing a parameter or there's an overflow");
      response.setStatusCode(400);
    }

    return true;
  }

  return false;
}
