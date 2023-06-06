// Copyright © Ignacio Robles Mayorga

#ifndef DATABASE_WEB_APP_HPP_
#define DATABASE_WEB_APP_HPP_

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "./Database.hpp"
#include "../http/HttpApp.hpp"
#include "../http/HttpRequest.hpp"
#include "../http/HttpResponse.hpp"
#include "../url/URL.hpp"
#include "HttpRequestHandlers/DatabaseRequestHandler.hpp"

class DatabaseWebApp : public HttpApp {
  DISABLE_COPY(DatabaseWebApp);

 protected: 
  std::vector<DatabaseRequestHandler*> requestHandlers;
  DatabaseAPI* databaseApi;

 public:
  // Default constructor
  DatabaseWebApp();

  // Default destructor
  ~DatabaseWebApp();

  bool start() override;

  bool run(HttpRequest& request, HttpResponse& response) override;

 private:

  void initHandlers();
  
};

#endif  // DATABASE_WEB_APP_HPP_
