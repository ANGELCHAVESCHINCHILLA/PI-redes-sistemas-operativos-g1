// Copyright © 2023 Camilo Suárez Sandí

#ifndef WEB_LOG_HANDLER_HPP_
#define WEB_LOG_HANDLER_HPP_

#include "../../common/common.hpp"
#include "../../log/LogHandler.hpp"
#include "HttpRequestHandler.hpp"

class WebLogHandler : public HttpRequestHandler {
  DISABLE_COPY(WebLogHandler);

 private:
  LogHandler log_handler;

 public:
  /// Constructor
  WebLogHandler();

  /// Destructor
  ~WebLogHandler() = default;

  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  void callDatabase(HttpRequest& request, HttpResponse& response,
      const std::string& method, const std::string& path);

  void callFileSystem(HttpRequest& request, HttpResponse& response,
      const std::string& method, const std::string& path);
};

#endif  // WEB_LOG_HANDLER_HPP_
