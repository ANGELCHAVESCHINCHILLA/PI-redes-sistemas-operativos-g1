// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef QUERY_HANDLER
#define QUERY_HANDLER

#include <jsoncpp/json/json.h>
#include "../HttpRequestHandler.hpp"

/**
 * @brief Is a query handler like consult salary or others. It has connection
 * with Data Base server.
 * 
 */
class QueryHandler : public HttpRequestHandler {
 protected:

 public:
  DISABLE_COPY(QueryHandler);

  QueryHandler() = default;

  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  bool callBDToGetQuery(HttpRequest& request, HttpResponse& response);
};


#endif  // QUERY_HANDLER
