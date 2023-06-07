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
 protected:
  /**
  * @brief The filesystem server
  * 
  */
  std::string server;

  /**
   * @brief Port in which filesystem server is listenning
   * 
   */
  std::string port;

 public:
  DISABLE_COPY(LoginHandler);

  LoginHandler() = default;

  /**
   * @brief Construct a new Login Handler object
   * 
   * @param server The filesystem server
   * @param port Port in which filesystem server is listenning
   */
  LoginHandler(const std::string& server, const std::string& port);
  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

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
