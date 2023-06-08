// Copyright © 2023 Ignacio Robles Mayorga

#ifndef DATABASE_REQUEST_HANDLER_HPP_
#define DATABASE_REQUEST_HANDLER_HPP_

#include <iostream>
#include <string>

#include "../../http/HttpRequest.hpp"
#include "../../http/HttpResponse.hpp"
#include "../../common/common.hpp"
#include "../DatabaseAPI.hpp"

#define URL_ERROR "Error in the url given"
#define INVALID_USER "User not found"
#define INVALID_ID "Id not found"
#define PARAM_NOT_INTEGER "Param given was not an integer"
#define JSON_VALUES_ERROR "Error in the json values"
#define JSON_FORMAT_ERROR "Error in the json format"
#define INVALID_AREA "Area not found"
#define POST_SUCCESS "Post success"
#define POST_FAIL "Post fail"

class DatabaseRequestHandler {
  DISABLE_COPY(DatabaseRequestHandler);

 public:
  /// default constructor
  DatabaseRequestHandler(DatabaseAPI* databaseApi) : databaseApi(databaseApi){};

  /// default destructor
  virtual ~DatabaseRequestHandler() = default;

  DatabaseAPI* databaseApi;

  /**
   * @brief determines wether a handler can handle a request or not
   * 
   * @param request the request recieved
   * @param response the response to be given
   * @return true if it can handle the response
   * @return false if it can't handle the response
   */
  virtual bool canHandle(HttpRequest& request, HttpResponse& response) = 0;
};

#endif // DATABASE_REQUEST_HANDLER_HPP_
