// Copyright © 2023 David Cerdas Alvarado

#pragma once

#include <vector>

#include "../http/HttpApp.hpp"
#include "../http/HttpRequest.hpp"
#include "../http/HttpResponse.hpp"
#include "../url/URL.hpp"
#include "FileSystemAPI.hpp"
#include "./HttpRequestHandlers/FileSystemRequestHandler.hpp"

class FileSystemWebApp : public HttpApp {
  DISABLE_COPY(FileSystemWebApp);


 protected:
  std::vector<FileSystemRequestHandler*> requestHandlers;
  FileSystemAPI* fileSystemApi;

 public:
  FileSystemWebApp();

  ~FileSystemWebApp();

  bool start() override;

  bool run(HttpRequest& request, HttpResponse& response) override;
 private:
  void initHandlers();
};
