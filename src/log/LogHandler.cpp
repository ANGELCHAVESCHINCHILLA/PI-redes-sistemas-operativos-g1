// Copyright © 2023 Camilo Suárez Sandí

#include "LogHandler.hpp"

#include <fstream>
#include <jsoncpp/json/json.h>

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
      
      std::stringstream responseBody;
      Json::Value json;
      for (size_t index = 0; index < lines; index++) {
        Json::Value line;
        char time[10];
        char type[30];
        char server[30];
        char message[99];

        std::sscanf(this->getLine(offset + index).c_str(), "[%[^]]] %s\t%s\t\t%99[^\n]", time,
         type, server, message);

        line["time"] = time;
        line["type"] = type;
        line["server"] = server;
        line["message"] = message;
        
        json["line" + std::to_string(index + 1)] = line;
      }

      Json::StreamWriterBuilder writer;

      response.getBody() << Json::writeString(writer, json);
    } catch (const std::out_of_range& exception) {
      Log::getInstance().write(Log::WARNING, "LogHandler", exception.what());
      response.setStatusCode(400);
    }

    return true;
  }

  return false;
}
