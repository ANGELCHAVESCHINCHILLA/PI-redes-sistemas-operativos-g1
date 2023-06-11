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
        std::cout << user << std::endl;
        
        // insert user into api to get the annotations data
        std::vector<std::string> annotationsData = this->databaseApi->consultRecordAnnotationsByUser(user);
        // insert user into api to get the name and company name
        std::vector<std::string> nameAndCompany = this->databaseApi->consultNameAndEnterpriseByUser(user);
        
        int statusCode;
        std::stringstream responseBody;
        if (!annotationsData.empty() && !nameAndCompany.empty()) {
          // pack all data into a json format string
          std::stringstream annotationsAsJSON;
          annotationsAsJSON << "{ \"name\": \"" << nameAndCompany[0] << "\", \"company_name\": \""
          << nameAndCompany[1] << "\", \"annotations\": {";
          for (int i = 0; i < annotationsData.size(); ++i) {
            annotationsAsJSON << "\"annotation" << (i + 1) << "\": \"";
            annotationsAsJSON << annotationsData[i] << "\",";
          }
          annotationsAsJSON << "} }";
          statusCode = 200;
          responseBody << annotationsAsJSON.str();
          Log::getInstance().write(Log::INFO, "DatabaseReached", "Request checked correctly");
        } else {
          statusCode = 400;
          responseBody << INVALID_USER;
          Log::getInstance().write(Log::ERROR, "DatabaseFail", INVALID_USER);
        }
        // build the response
        response.setStatusCode(statusCode);
        response.getBody() << responseBody.str();
      } catch(std::bad_alloc& err) {
        std::cerr << err.what() << std::endl;
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

#endif // CONSULT_ANNOTATIONS_HANDLER_HPP_
