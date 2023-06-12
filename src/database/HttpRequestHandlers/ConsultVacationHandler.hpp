// Copyright © 2023 Ignacio Robles Mayorga

#ifndef CONSULT_VACATION_HANDLER_HPP_
#define CONSULT_VACATION_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class ConsultVacationHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  ConsultVacationHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "GET" && request.getTarget().getPath() 
      == "/consultVacationBalanceByUser") {
      response.setHeader("Content-Type", "text/plain");
      try {
        // fetch user from request url
        std::string user = request.getTarget().getQuery().find("user")->second;
        // print user
        Log::getInstance().write(Log::MessageType::DEBUG,
          "ConsultVacationHandler", "User: " + user);

        // insert user into api to get the vacation balance
        std::string vacationBalance = this->databaseApi->consultVacationBalanceByUser(user);

        int statusCode;
        std::stringstream responseBody;
        if (vacationBalance == "user not found") {
          statusCode = 400;
          responseBody << INVALID_USER;
          Log::getInstance().write(Log::ERROR, "DatabaseFail", INVALID_USER);
        } else {
          statusCode = 200;
          responseBody << "{ \"vacationBalance\": " << std::stoi(vacationBalance) << "}";
          Log::getInstance().write(Log::INFO, "DatabaseReached", "Request checked correctly");
        }
        // build the response
        response.setStatusCode(statusCode);
        response.getBody() << responseBody.str();
      } catch(const std::bad_alloc err) {
        // build the response
        response.setStatusCode(400);
        response.getBody() << URL_ERROR;
        Log::getInstance().write(Log::ERROR, "DatabaseFail", URL_ERROR);
      }
      response.buildResponse();
      
      return true;
    }
    return false;
  }
};

#endif // CONSULT_VACATION_HANDLER_HPP_
