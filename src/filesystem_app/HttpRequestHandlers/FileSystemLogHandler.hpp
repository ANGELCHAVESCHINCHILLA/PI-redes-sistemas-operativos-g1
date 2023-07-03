// Copyright © 2023 Camilo Suárez Sandí

#ifndef WEB_LOG_HANDLER_HPP_
#define WEB_LOG_HANDLER_HPP_

#include "../../common/common.hpp"
#include "../../log/LogHandler.hpp"
#include "FileSystemRequestHandler.hpp"

class FileSystemLogHandler : public FileSystemRequestHandler {
  DISABLE_COPY(FileSystemLogHandler);

 private:
  LogHandler log_handler;

 public:
  /// Constructor
  FileSystemLogHandler(FileSystemAPI* api);

  /// Destructor
  ~FileSystemLogHandler() = default;

  bool canHandle(HttpRequest& request, HttpResponse& response) override;
};

#endif  // WEB_LOG_HANDLER_HPP_
