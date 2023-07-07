// Copyright © 2023 Ignacio Robles Mayorga

#ifndef MAKE_ANNOTATION_HANDLER_HPP_
#define MAKE_ANNOTATION_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class MakeAnnotationHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  MakeAnnotationHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "POST" && request.getTarget().getPath() 
      == "/makeAnnotation") {
      // fetch body from request
      std::string body = request.getBody();
      Json::Value requestBody;
      Json::Reader reader;

      // parse to json for easier manipulation
      bool parsed = reader.parse(body, requestBody);

      int statusCode;
      std::string responseBody;

      if (parsed) {
        try {
          // access json data
          std::string user = requestBody["user"].asString();
          std::string information = requestBody["information"].asString();

          // add data to annotation database
          bool couldMakeAnnotation = this->databaseApi->makeAnnotation(user, information);

          // check for errors while adding data
          statusCode = couldMakeAnnotation ? 200 : 400;
          responseBody = couldMakeAnnotation ? POST_SUCCESS : POST_FAIL;
          if (couldMakeAnnotation) {
            Log::getInstance().write(Log::INFO, "MakeAnnotationHandler", "Request checked correctly");
          } else {
            Log::getInstance().write(Log::ERROR, "MakeAnnotationHandler", POST_FAIL);
          }
        } catch (const Json::LogicError& err) {
          statusCode = 400;
          responseBody = JSON_VALUES_ERROR;
          Log::getInstance().write(Log::ERROR, "MakeAnnotationHandler", JSON_VALUES_ERROR);
        }
      } else {
        statusCode = 400;
        responseBody = JSON_FORMAT_ERROR;
        Log::getInstance().write(Log::ERROR, "DatabaseFail", JSON_FORMAT_ERROR);
      }

      // build the response
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(statusCode);
      response.getBody() << responseBody;
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // MAKE_ANNOTATION_HANDLER_HPP_
