// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#ifndef PERSONAL_DATA_HANDLER_HPP_
#define PERSONAL_DATA_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class PersonalDataHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  PersonalDataHandler(DatabaseAPI* databaseApi)
      : DatabaseRequestHandler(databaseApi){};

  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  bool getData(HttpRequest& request, HttpResponse& response);

  bool addData(HttpRequest& request, HttpResponse& response);

  bool removeData(HttpRequest& request, HttpResponse& response);

  bool editData(HttpRequest& request, HttpResponse& response);
};

#endif  // PERSONAL_DATA_HANDLER_HPP_
