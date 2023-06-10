// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef LOGIN_HANDLER
#define LOGIN_HANDLER

#include <jsoncpp/json/json.h>
#include "../HttpRequestHandler.hpp"
#include "../../../authenticator.hpp"

class UserSession;

/**
 * @brief In charge of handle the login, has communication with Filesystem
 * server
 * 
 */
class LoginHandler : public HttpRequestHandler {
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

  bool callFSToLogin(HttpRequest& request, HttpResponse& response);

  /**
   * @brief true if the user is valid
   * 
   * @param request 
   * @param user 
   * @return true 
   * @return false 
   */
  bool isValidUser(HttpRequest& request, UserSession& user);

  inline void setServer(const std::string& server);

  inline void setPort(const std::string& port);

  bool serveAuthFailed(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse);

};

#endif  // LOGIN_HANDLER
