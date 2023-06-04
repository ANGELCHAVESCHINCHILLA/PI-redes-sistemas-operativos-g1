//
// Created by David Cerdas on 03/06/23.
//

#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_VALIDATEHANDLER_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_VALIDATEHANDLER_H

#include "../HttpRequestHandler.hpp"

class ValidateHandler : public HttpRequestHandler {
 public:
  DISABLE_COPY(ValidateHandler);

  ValidateHandler() = default;
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

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_VALIDATEHANDLER_H
