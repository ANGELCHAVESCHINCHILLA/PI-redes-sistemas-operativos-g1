// Copyright © 2023 Ignacio Robles Mayorga

#ifndef CONSULT_SALARY_HANDLER_HPP_
#define CONSULT_SALARY_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class ConsultSalaryHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  ConsultSalaryHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "GET" && request.getTarget().getPath() 
      == "/consultSalaryByUser") {
      response.setHeader("Content-Type", "text/plain");
      try {
        // fetch user from request url
        std::string user = request.getTarget().getQuery().find("user")->second;
        // print user
        Log::getInstance().write(Log::DEBUG,
          "ConsultSalaryHandler", "User: " + user);
        
        // insert user into api to get the salary data
        std::vector<std::vector<std::string>> salaryData = this->databaseApi->consultSalaryByUser(user);
        // insert user into api to get the name and area
        std::vector<std::string> nameAndArea = this->databaseApi->consultNameAndAreaByUser(user);
        // pack all data into a json format string

        int statusCode;
        std::stringstream responseBody;
        if (!salaryData.empty() && !nameAndArea.empty()) {
          std::stringstream salaryAsJSON;
          salaryAsJSON << "{ \"name\": \"" << nameAndArea[0] << "\", \"area\": \""
          << nameAndArea[1] << "\", \"salaries\": {";
          for (int i = 0; i < salaryData.size(); ++i) {
            salaryAsJSON << "\"salary" << (i + 1) << "\": { ";
            for (int j = 0; j < salaryData[i].size(); ++j) {
              std::string jsonEntry;
              if (j == 0) {
                jsonEntry = "gross_salary";
              } else {
                if (j == 1) {
                  jsonEntry = "net_salary";
                } else {
                  jsonEntry = "salary_start_date";
                }
              }
              salaryAsJSON << "\"" << jsonEntry << "\": " << std::stoi(salaryData[i][j]) << (j == 2 ? "}" : ", ");
            }
            if (i < salaryData.size() - 1) {
              salaryAsJSON << ",";
            }
          }
          salaryAsJSON << "} }";
          statusCode = 200;
          responseBody << salaryAsJSON.str();
          Log::getInstance().write(Log::INFO, "ConsultSalaryHandler", "Request checked correctly");
        } else {
          statusCode = 400;
          responseBody << INVALID_USER;
          Log::getInstance().write(Log::ERROR, "ConsultSalaryHandler", INVALID_USER);
        }
        // build the response
        response.setStatusCode(statusCode);
        response.getBody() << responseBody.str();
      } catch(const std::bad_alloc& err) {
        // build the response
        response.setStatusCode(400);
        response.getBody() << URL_ERROR;
        Log::getInstance().write(Log::ERROR, "ConsultSalaryHandler", URL_ERROR);
      }
      response.buildResponse();
      
      return true;
    }
    return false;
  }
};

#endif // CONSULT_SALARY_HANDLER_HPP_
