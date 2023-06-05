// Copyright © 2023 Ignacio Robles Mayorga

#ifndef CONSULT_REQUESTS_BY_USER_HANDLER_HPP_
#define CONSULT_REQUESTS_BY_USER_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class ConsultRequestsByUserHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  ConsultRequestsByUserHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "GET" && request.getTarget().getPath() 
      == "/consultRequestsByUser") {
      // fetch user from request url
      std::string user = request.getTarget().getQuery().find("user")->second;
      // print user
      std::cout << user << std::endl;
      
      // insert user into api to get the salary data
      std::vector<std::vector<std::string>> requestsData = this->databaseApi->consultRequestsMadeByUser(user);
      // pack all data into a json format string
      std::stringstream requestsAsJSON;
      requestsAsJSON << "{";
      for (int i = 0; i < requestsData.size(); ++i) {
        requestsAsJSON << "\"request" << (i + 1) << "\": { ";
        for (int j = 0; j < requestsData[i].size(); ++j) {
          std::string jsonEntry;
          switch(j) {
            case 0:
              jsonEntry = "user";
              break;
            case 1:
              jsonEntry = "ID";
              break;
            case 2:
              jsonEntry = "state";
              break;
            case 3:
              jsonEntry = "padding";
              break;
            case 4:
              jsonEntry = "information";
              break;
            case 5:
              jsonEntry = "feedback";
              break;
            case 6:
              jsonEntry = "request_type";
              break;
            case 7:
              jsonEntry = "vacation_days";
              break;
            case 8:
              jsonEntry = "vacation_start_date";
              break;
            case 9:
              jsonEntry = "vacation_end_date";
              break;
            case 10:
              jsonEntry = "area";
              break;
          }
          requestsAsJSON << "\"" << jsonEntry << "\": ";
          if (j == 1 || j == 2 || j == 7 || j == 8 || j == 9) {
            requestsAsJSON << std::stoi(requestsData[i][j]);
          } else {
            requestsAsJSON << "\"" << requestsData[i][j] << "\"";
          }
          requestsAsJSON << (j == 10 ? "}," : ", ");
        }
      }
      requestsAsJSON << "}";
      // build the response
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(200);
      response.getBody() << requestsAsJSON.str();
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // CONSULT_SALARY_HANDLER_HPP_
