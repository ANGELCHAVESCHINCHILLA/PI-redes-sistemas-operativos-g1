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
      // fetch user from request url
      std::string user = request.getTarget().getQuery().find("user")->second;
      // print user
      std::cout << user << std::endl;
      
      // insert user into api to get the salary data
      std::vector<std::vector<std::string>> salaryData = this->databaseApi->consultSalaryByUser(user);
      // insert user into api to get the name and company name
      std::vector<std::string> nameAndCompany = this->databaseApi->consultNameAndEnterpriseByUser(user);
      // pack all data into a json format string
      std::stringstream salaryAsJSON;
      salaryAsJSON << "{ \"name\": \"" << nameAndCompany[0] << "\", \"company_name\": \""
      << nameAndCompany[1] << "\", \"salaries\": {";
      for (size_t i = 0; i < salaryData.size(); ++i) {
        salaryAsJSON << "\"salary" << (i + 1) << "\": { ";
        for (size_t j = 0; j < salaryData[i].size(); ++j) {
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
        salaryAsJSON << ",";
      }
      salaryAsJSON << "} }";
      // build the response
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(200);
      response.getBody() << salaryAsJSON.str();
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // CONSULT_SALARY_HANDLER_HPP_
