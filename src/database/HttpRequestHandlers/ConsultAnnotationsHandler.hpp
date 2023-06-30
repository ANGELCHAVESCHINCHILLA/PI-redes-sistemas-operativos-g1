// Copyright © 2023 Ignacio Robles Mayorga

#ifndef CONSULT_ANNOTATIONS_HANDLER_HPP_
#define CONSULT_ANNOTATIONS_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class ConsultAnnotationsHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  ConsultAnnotationsHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "GET" && request.getTarget().getPath() 
      == "/consultAnnotationsByUser") {
      response.setHeader("Content-Type", "text/plain");
      try {
        // fetch user from request url
        std::string user = request.getTarget().getQuery().find("user")->second;
        // print user
        Log::getInstance().write(Log::DEBUG,
          "ConsultAnnotationsHandler", "User: " + user);

        // insert user into api to get the annotations data
        std::vector<std::string> annotationsData = this->databaseApi->consultRecordAnnotationsByUser(user);
        // insert user into api to get the name and area name
        std::vector<std::string> nameAndArea = this->databaseApi->consultNameAndAreaByUser(user);
        
        int statusCode;
        std::stringstream responseBody;
        if (!annotationsData.empty() && !nameAndArea.empty()) {
          Json::Value json;

          json["name"] = nameAndArea[0];
          json["area"] = nameAndArea[1];

          Json::Value annotations;

          for (size_t index = 0; index < annotationsData.size(); index++) {
            annotations["annotation" + std::to_string(index + 1)] = annotationsData[index];
          }

          json["annotations"] = annotations;

          Json::StreamWriterBuilder writer;
          std::string jsonString = Json::writeString(writer, json);

          statusCode = 200;
          // TODO: Borrar el print
          std::cout << jsonString << "\n";
          responseBody << jsonString;
          Log::getInstance().write(Log::INFO, "ConsultAnnotationsHandler", "Request checked correctly");
        } else {
          statusCode = 400;
          responseBody << INVALID_USER;
          Log::getInstance().write(Log::ERROR, "ConsultAnnotationsHandler", INVALID_USER);
        }
        // build the response
        response.setStatusCode(statusCode);
        response.getBody() << responseBody.str();
      } catch(std::bad_alloc& err) {
        // build the response
        response.setStatusCode(400);
        response.getBody() << URL_ERROR;
        Log::getInstance().write(Log::ERROR, "ConsultAnnotationsHandler", URL_ERROR);
      }
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // CONSULT_ANNOTATIONS_HANDLER_HPP_
