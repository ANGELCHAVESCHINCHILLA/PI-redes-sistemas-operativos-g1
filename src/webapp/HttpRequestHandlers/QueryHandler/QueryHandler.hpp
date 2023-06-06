// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef QUERY_HANDLER
#define QUERY_HANDLER

#include <jsoncpp/json/json.h>
#include "../HttpRequestHandler.hpp"

class QueryHandler : public HttpRequestHandler {
 protected:
  /**
  * @brief The database server
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
   * @brief Construct a new Login Handler object
   * 
   * @param server The filesystem server
   * @param port Port in which filesystem server is listenning
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

  inline void setServer(const std::string& server);

  inline void setPort(const std::string& port);

  bool serveAuthFailed(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse);
};


#endif  // QUERY_HANDLER
