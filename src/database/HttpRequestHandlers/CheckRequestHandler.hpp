// Copyright © 2023 Ignacio Robles Mayorga

#ifndef CHECK_REQUEST_HANDLER_HPP_
#define CHECK_REQUEST_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class CheckRequestHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  CheckRequestHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "POST" && request.getTarget().getPath() 
      == "/checkRequest") {
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
          int requestID = requestBody["request_id"].asInt();
          int state = requestBody["state"].asInt();
          std::string feedback = requestBody["feedback"].asString();

          // check if id is valid
          bool idIsValid = this->databaseApi->idWasFound(requestID);

          if (idIsValid) {
            // add data to request database
            bool couldCheckRequest = this->databaseApi->checkRequest(requestID,
            state, feedback);

            // check for errors while adding data
            statusCode = couldCheckRequest ? 200 : 400;
            responseBody = couldCheckRequest ? POST_SUCCESS : POST_FAIL;
            Log::getInstance().write(Log::INFO, "CheckRequestHandler", "Request checked correctly");
          } else {
            statusCode = 400;
            responseBody = INVALID_ID;
            Log::getInstance().write(Log::ERROR, "CheckRequestHandler", INVALID_ID);
          }
        } catch(const Json::LogicError& err) {
          statusCode = 400;
          responseBody = JSON_VALUES_ERROR;
          Log::getInstance().write(Log::ERROR, "CheckRequestHandler", JSON_VALUES_ERROR);
        }
      } else {
        statusCode = 400;
        responseBody = JSON_FORMAT_ERROR;
        Log::getInstance().write(Log::ERROR, "CheckRequestHandler", JSON_FORMAT_ERROR);
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

#endif // CHECK_REQUEST_HANDLER_HPP_
