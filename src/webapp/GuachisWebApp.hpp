// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef GUACHIS_WEB_APP
#define GUACHIS_WEB_APP

#include <vector>

#include "../http/HttpApp.hpp"
#include "../url/URL.hpp"
#include "./HttpRequestHandlers/LoginHandler/LoginHandler.hpp"
#include "./HttpRequestHandlers/StaticHandler/StaticHandler.hpp"
#include "./HttpRequestHandlers/QueryHandler/QueryHandler.hpp"
#include "../http/HttpResponse.hpp"
#include "../http/HttpRequest.hpp"

#define HANDLERS_COUNT 4

class GuachisWebApp : public HttpApp {
  DISABLE_COPY(GuachisWebApp);

 protected:
  std::vector<HttpRequestHandler*> requestHandlers;
  

 public:
  GuachisWebApp();

  ~GuachisWebApp();

  bool start() override;

  bool run(HttpRequest& request, HttpResponse& response) override;

};

#endif  // GUACHIS_WEB_APP