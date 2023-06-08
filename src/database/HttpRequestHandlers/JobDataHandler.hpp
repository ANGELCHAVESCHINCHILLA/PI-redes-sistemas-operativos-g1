// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#ifndef JOB_DATA_HANDLER_HPP_
#define JOB_DATA_HANDLER_HPP_

#include <jsoncpp/json/json.h>

#include "DatabaseRequestHandler.hpp"

class JobDataHandler : public DatabaseRequestHandler {
 public:
  /// Constructor
  JobDataHandler(DatabaseAPI* databaseApi)
      : DatabaseRequestHandler(databaseApi){};

  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  bool getJobData(HttpRequest& request, HttpResponse& response);

  bool addJobData(HttpRequest& request, HttpResponse& response);

  bool removeJobData(HttpRequest& request, HttpResponse& response);

  bool editJobData(HttpRequest& request, HttpResponse& response);
};

#endif  // JOB_DATA_HANDLER_HPP_
