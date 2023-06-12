//
// Created by daviddev on 01/06/23.
//

#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_AUTHHANDLER_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_AUTHHANDLER_H

#include <jsoncpp/json/json.h>

#include "../../common/Log.hpp"
#include "FileSystemRequestHandler.hpp"

class AuthHandler : public FileSystemRequestHandler {
 public:
  explicit AuthHandler(FileSystemAPI* fileSystemApi)
      : FileSystemRequestHandler(fileSystemApi){};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "POST" &&
        (request.getTarget().getPath() == "/login" ||
            request.getTarget().getPath() == "/auth")) {
      Log::getInstance().write(
          Log::INFO, "AuthUserRequestHandled", request.getTarget().getPath());
      const std::string& body = request.getBody();
      Json::Value requestBody;
      Json::Reader reader;
      // Parse to JSON to easy manipulation
      bool parsed = reader.parse(body, requestBody);

      int statusCode;
      std::string responseBody;

      if (parsed) {
        std::string username = requestBody["username"].asString();
        std::string password = requestBody["password"].asString();
        // Auth via API
        bool isAuthenticated =
            this->fileSystemApi->authenticateUser(username, password);

        statusCode = isAuthenticated ? 200 : 400;
        responseBody = isAuthenticated ? "Successfully" : "Failed";
      } else {
        statusCode = 400;
        responseBody = "JSON ERROR";
        Log::getInstance().write(
            Log::ERROR, "AuthUserRequest", "JSON Parsing Error");
      }

      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(statusCode);
      response.getBody() << responseBody;

      response.buildResponse();
      // Send response
      Log::getInstance().write(
          Log::INFO, "ResponseSend", "Response Sent with body:" + responseBody);
      return true;
    }
    return false;
  }
};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_AUTHHANDLER_H
