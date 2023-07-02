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
