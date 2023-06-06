// Copyright © 2023 Ignacio Robles Mayorga

#ifndef CONSULT_REQUESTS_BY_ID_HANDLER_HPP_
#define CONSULT_REQUESTS_BY_ID_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class ConsultRequestsByIDHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  ConsultRequestsByIDHandler(DatabaseAPI* databaseApi) : DatabaseRequestHandler(databaseApi) {};

  bool canHandle(HttpRequest& request, HttpResponse& response) override {
    if (request.getMethod() == "GET" && request.getTarget().getPath() 
      == "/consultRequestsByID") {
      // fetch id from request url
      std::string id = request.getTarget().getQuery().find("id")->second;
      // print id
      std::cout << id << std::endl;
      
      // insert id into api to get the annotations data
      std::vector<std::string> requestsData = this->databaseApi->getRequestByID(std::stoi(id));
      // pack all data into a json format string
      std::stringstream requestsAsJSON;
      requestsAsJSON << "{";
      for (int i = 0; i < requestsData.size(); ++i) {
        std::string jsonEntry;
        switch(i) {
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
        if (i == 1 || i == 2 || i == 7 || i == 8 || i == 9) {
          requestsAsJSON << std::stoi(requestsData[i]);
        } else {
          requestsAsJSON << "\"" << requestsData[i] << "\"";
        }
        requestsAsJSON << (i < 10 ? ", " : "}");
      }
      // build the response
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(200);
      std::cout << requestsAsJSON.str() << std::endl;
      response.getBody() << requestsAsJSON.str();
      response.buildResponse();
      return true;
    }
    return false;
  }
};

#endif // CONSULT_REQUESTS_BY_ID_HANDLER_HPP_
