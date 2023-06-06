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
      // fetch user from request url
      std::string user = request.getTarget().getQuery().find("user")->second;
      // print user
      std::cout << user << std::endl;
      
      // insert user into api to get the annotations data
      std::vector<std::string> annotationsData = this->databaseApi->consultRecordAnnotationsByUser(user);
      // insert user into api to get the name and company name
      std::vector<std::string> nameAndCompany = this->databaseApi->consultNameAndEnterpriseByUser(user);
      // pack all data into a json format string
      std::stringstream annotationsAsJSON;
      annotationsAsJSON << "{ \"name\": \"" << nameAndCompany[0] << "\", \"company_name\": \""
      << nameAndCompany[1] << "\", \"annotations\": {";
      for (int i = 0; i < annotationsData.size(); ++i) {
        annotationsAsJSON << "\"annotation" << (i + 1) << "\": \"";
        annotationsAsJSON << annotationsData[i] << "\",";
      }
      annotationsAsJSON << "} }";
      // build the response
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(200);
      std::cout << annotationsAsJSON.str() << std::endl;
      response.getBody() << annotationsAsJSON.str();
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // CONSULT_ANNOTATIONS_HANDLER_HPP_
