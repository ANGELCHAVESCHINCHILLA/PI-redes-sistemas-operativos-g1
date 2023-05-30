// Copyright © 2023 Ángel Chaves Chinchilla

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