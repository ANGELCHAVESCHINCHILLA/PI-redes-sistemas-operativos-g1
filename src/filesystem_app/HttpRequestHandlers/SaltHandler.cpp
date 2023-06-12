// Copyright © 2023 Camilo Suárez Sandí

#include "SaltHandler.hpp"

#include <jsoncpp/json/json.h>
#include <iostream>

SaltHandler::SaltHandler(FileSystemAPI* api) : FileSystemRequestHandler(api) {
}

SaltHandler::~SaltHandler() {
}

bool SaltHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath() == "/auth/salt") {
      // Json::Reader reader;
      // Json::Value root;

      // reader.parse(request.getBody(), root);

      // std::string username = root["username"].asString();

      // std::string salt = this->fileSystemApi->getUserSalt(username);

      std::string username = request.getTarget().getQuery().find("username")->second;

      std::string salt = this->fileSystemApi->getUserSalt(username);

      if (salt.empty()) {
        response.setStatusCode(401);
      } else {
        Json::StreamWriterBuilder writer;

        Json::Value object(Json::objectValue);

        object["salt"] = salt;

        std::string json = Json::writeString(writer, object);

        response.setStatusCode(200);
        response.getBody() << json;
      }

      return true;
    }
  }

  return false;
}
