// Copyright © 2023 Camilo Suárez Sandí

#ifndef DATABASE_LOG_HANDLER_HPP_
#define DATABASE_LOG_HANDLER_HPP_

#include "../../common/common.hpp"
#include "../../log/LogHandler.hpp"
#include "DatabaseRequestHandler.hpp"

class DatabaseLogHandler : public DatabaseRequestHandler {
  DISABLE_COPY(DatabaseLogHandler);

 private:
  LogHandler log_handler;

 public:
  /// Constructor
  explicit DatabaseLogHandler(DatabaseAPI* api);

  /// Destructor
  ~DatabaseLogHandler() = default;

  bool canHandle(HttpRequest& request, HttpResponse& response) override;
};

#endif  // DATABASE_LOG_HANDLER_HPP_
