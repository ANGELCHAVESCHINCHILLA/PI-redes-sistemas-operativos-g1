//
// Created by David Cerdas Alvarado on 01/06/23.
//

#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_ADDUSERHANDLER_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_ADDUSERHANDLER_H

#include <jsoncpp/json/json.h>

#include "FileSystemequestHandler.hpp"

class AddUserHandler : public FileSystemRequestHandler {
 public:
  AddUserHandler(FileSystemAPI* fileSystemApi) :
        FileSystemRequestHandler(fileSystemApi){}

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "POST" &&
        request.getTarget().getPath() == "/adduser") {

      std::string body = request.getBody();
      Json::Value requestBody;
      Json::Reader reader;
      // Parse to JSON to easy manipulation
      bool parsed = reader.parse(body, requestBody);

      int statusCode;
      std::string responseBody;

      if (parsed) {
        // Get values
        std::string username = requestBody["username"].asString();
        std::string password = requestBody["password"].asString();
        int type = requestBody["type"].asInt();

        // Auth by API
        bool isAdded =
            this->fileSystemApi->addUser(username, password, type);

        statusCode = isAdded ? 200 : 400;
        responseBody = isAdded ? "Successfully" : "Failed";

      } else {
        statusCode = 400;
        responseBody = "JSON ERROR";
      }
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(statusCode);
      response.getBody() << responseBody;

      response.buildResponse();
      // Send
      return true;
    }
    return false;
  }
};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_ADDUSERHANDLER_H
