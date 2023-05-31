// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef QUERY_HANDLER
#define QUERY_HANDLER

#include "../HttpRequestHandler.hpp"
#include "authenticator.hpp"

class QueryHandler : public HttpRequestHandler {
 protected:
  /**
  * @brief 
  * 
  */
  Authenticator* authenticator;

 public:
  // TODO (any): look if needed
  DECLARE_RULE4(QueryHandler, default);

  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;
};

#endif  // QUERY_HANDLER
