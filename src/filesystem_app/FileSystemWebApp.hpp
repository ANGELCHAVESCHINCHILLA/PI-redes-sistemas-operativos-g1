// Copyright © 2023 David Cerdas Alvarado

#pragma once

#include <vector>

#include "../http/HttpApp.hpp"
#include "../http/HttpRequest.hpp"
#include "../http/HttpResponse.hpp"
#include "../url/URL.hpp"
#include "FileSystemAPI.hpp"

// #define HANDLERS_COUNT 4

class FileSystemWebApp : public HttpApp {
  DISABLE_COPY(FileSystemWebApp);


 protected:
  // std::vector<HttpRequestHandler*> requestHandlers;
  FileSystemAPI* fileSystemApi;

 public:
  FileSystemWebApp();

  ~FileSystemWebApp();

  bool start() override;

  bool run(HttpRequest& request, HttpResponse& response) override;
};
