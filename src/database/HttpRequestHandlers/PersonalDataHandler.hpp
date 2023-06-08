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

  bool getJobData(HttpRequest& request, HttpResponse& response);

  bool addJobData(HttpRequest& request, HttpResponse& response);

  bool removeJobData(HttpRequest& request, HttpResponse& response);

  bool editJobData(HttpRequest& request, HttpResponse& response);
};

#endif  // PERSONAL_DATA_HANDLER_HPP_
