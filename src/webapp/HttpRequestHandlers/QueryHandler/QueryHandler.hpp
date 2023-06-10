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
  /**
  * @brief The database server.
  * 
  */
  std::string server;

  /**
   * @brief Port in which database server is listenning
   * 
   */
  std::string port;

 public:
  DISABLE_COPY(QueryHandler);

  QueryHandler() = default;

  /**
   * @brief Construct a new Query Handler object
   * 
   * @param server The Data Base server
   * @param port Port in which Data Base server is listenning
   */
  QueryHandler(const std::string& server, const std::string& port);
  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  void callBDToGetQuery(HttpRequest& request, HttpResponse& response);

  inline void setServer(const std::string& server);

  inline void setPort(const std::string& port);
};


#endif  // QUERY_HANDLER
