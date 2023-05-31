// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef STATIC_HANDLER
#define STATIC_HANDLER

#include "../HttpRequestHandler.hpp"

class StaticHandler : public HttpRequestHandler {
 protected:

 public:
  DISABLE_COPY(StaticHandler);

  StaticHandler() = default;
  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  bool serveHtml(HttpRequest& request, HttpResponse& response);

  bool serveAssets(HttpRequest& request, HttpResponse& response);

  bool serveScripts(HttpRequest& request, HttpResponse& response);

  bool serveStyles(HttpRequest& request, HttpResponse& response);
};

#endif  // STATIC_HANDLER
