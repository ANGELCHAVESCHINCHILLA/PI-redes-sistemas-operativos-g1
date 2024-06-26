// Copyright © 2023 Ignacio Robles Mayorga

#ifndef MAKE_REQUEST_HANDLER_HPP_
#define MAKE_REQUEST_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class MakeRequestHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  MakeRequestHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "POST" && request.getTarget().getPath() 
      == "/makeRequest") {
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
          std::string requestType = requestBody["request_type"].asString();
          std::string information = requestBody["information"].asString();
          std::string area = requestBody["area"].asString();
          int vacationDays = requestBody["vacation_days"].asInt();
          int vacationStartDate = requestBody["vacation_start_date"].asInt();
          int vacationEndDate = requestBody["vacation_end_date"].asInt();

          // add data to request database
          bool couldMakeRequest = this->databaseApi->makeRequest(user, requestType,
          information, area, vacationDays, vacationStartDate, vacationEndDate);

          // check for errors while adding data
          statusCode = couldMakeRequest ? 200 : 400;
          responseBody = couldMakeRequest ? POST_SUCCESS : POST_FAIL;
          if (couldMakeRequest) {
            Log::getInstance().write(Log::INFO, "MakeRequestHandler", "Request checked correctly");
          } else {
            Log::getInstance().write(Log::ERROR, "MakeRequestHandler", POST_FAIL);
          }
        } catch (const Json::LogicError& err) {
          statusCode = 400;
          responseBody = JSON_VALUES_ERROR;
          Log::getInstance().write(Log::ERROR, "MakeRequestHandler", JSON_VALUES_ERROR);
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

#endif // MAKE_REQUEST_HANDLER_HPP_
