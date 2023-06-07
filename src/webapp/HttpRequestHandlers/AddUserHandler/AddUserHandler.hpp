// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef ADD_USER_HANDLER_HPP
#define ADD_USER_HANDLER_HPP

#include <jsoncpp/json/json.h>
#include "../HttpRequestHandler.hpp"
#include "../../../common/Log.hpp"

// HAD NOT BEEN PROVE YET WITH FS SERVER

/**
 * @brief Handle a request that need to add a user in FS.
 * 
 */
class AddUserHandler : public HttpRequestHandler {
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
  AddUserHandler() = default;

  AddUserHandler(const std::string& server, const std::string& port);

  inline void setServer(const std::string& server);

  inline void setPort(const std::string& port);

  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  /**
   * @brief true if filesystem could add user
   * 
   * @param request 
   * @return true 
   * @return false 
   */
  bool couldAddUser(HttpRequest& request);
};

#endif  // ADD_USER_HANDLER_HPP
