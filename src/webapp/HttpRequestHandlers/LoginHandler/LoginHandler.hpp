// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef LOGIN_HANDLER
#define LOGIN_HANDLER

#include "../HttpRequestHandler.hpp"
#include "authenticator.hpp"


class LoginHandler : public HttpRequestHandler {
 protected:
  /**
  * @brief 
  * 
  */
  Authenticator* authenticator;

 public:
  DISABLE_COPY(LoginHandler);

  LoginHandler() = default;
  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  bool validateUser(HttpRequest& request);

  bool serveAuthFailed(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse);
};

#endif  // LOGIN_HANDLER
