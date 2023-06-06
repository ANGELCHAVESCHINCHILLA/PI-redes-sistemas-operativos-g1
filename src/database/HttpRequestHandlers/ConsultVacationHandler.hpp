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
      // fetch user from request url
      std::string user = request.getTarget().getQuery().find("user")->second;
      // print user
      std::cout << user << std::endl;

      // insert user into api to get the vacation balance
      std::string vacationBalance = this->databaseApi->consultVacationBalanceByUser(user);
      // build the response
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(200);
      response.getBody() << "{ \"vacationBalance\": " << std::stoi(vacationBalance) << "}";
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // CONSULT_VACATION_HANDLER_HPP_
