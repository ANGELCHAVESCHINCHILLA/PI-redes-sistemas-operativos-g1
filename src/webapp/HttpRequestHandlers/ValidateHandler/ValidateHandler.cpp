//
// Created by David on 03/06/23.
//

#include "ValidateHandler.hpp"
#include <jsoncpp/json/json.h>

bool ValidateHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "POST" &&
      request.getTarget().getPath() == "/validate") {
    const std::string& body = request.getBody();
    Json::Value requestBody;
    Json::Reader reader;
    // Parse to JSON to easy manipulation
    bool parsed = reader.parse(body, requestBody);
    if (parsed) {
      std::string data = requestBody["data"].asString();
      if (data == "false") {
        response.getBody() << "Unauthorized";
        response.setStatusCode(401);
        response.buildResponse();
        return true;
      }
    }
  }
}