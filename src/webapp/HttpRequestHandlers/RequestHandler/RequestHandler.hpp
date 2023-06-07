// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef REQUEST_HANDLER
#define REQUEST_HANDLER

#include "../HttpRequestHandler.hpp"
#include "authenticator.hpp"

/**
 * @brief Handler the request from the employee, employer or some else.
 * Example of a request: Solicitud de vacaciones
 * 
 */
class RequestHandler : public HttpRequestHandler {
 protected:
  /**
  * @brief 
  * 
  */
  Authenticator* authenticator;

 public:
  DECLARE_RULE4(RequestHandler, default);

  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  // TODO (any): look if needed
  bool canHandle(HttpRequest& request, HttpResponse& response) override;
};

#endif  // REQUEST_HANDLER