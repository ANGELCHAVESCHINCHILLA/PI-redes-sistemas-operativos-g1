// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef LOGIN_HANDLER
#define LOGIN_HANDLER

#include <jsoncpp/json/json.h>
#include "../HttpRequestHandler.hpp"
#include "authenticator.hpp"
#include "jwt.hpp"

class LoginHandler : public HttpRequestHandler {
 protected:
  /**
  * @brief 
  * 
  */

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

  bool serveJWT(const HttpRequest& request, HttpResponse& response
    , Json::Value& jsonResponse);
};

#endif  // LOGIN_HANDLER
