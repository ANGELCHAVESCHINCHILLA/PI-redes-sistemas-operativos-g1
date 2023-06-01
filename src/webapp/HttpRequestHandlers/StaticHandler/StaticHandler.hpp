// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suárez Sandí

#ifndef STATIC_HANDLER
#define STATIC_HANDLER

#include "../HttpRequestHandler.hpp"

class StaticHandler : public HttpRequestHandler {
 protected:

 public:
  DISABLE_COPY(StaticHandler);

  StaticHandler() = default;
  /**
   * @brief 
   * 
   * @param request 
   * @param response 
   * @return true 
   * @return false 
   */
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

  void redirect(HttpResponse& response, const std::string& target) const;
};


#endif  // APP_HPP_