// Copyright © 2023 Camilo Suárez Sandí

#ifndef USER_ADMIN_HANDLER_HPP_
#define USER_ADMIN_HANDLER_HPP_

#include "../../../common/common.hpp"
#include "../HttpRequestHandler.hpp"

class UserAdminHandler : public HttpRequestHandler {
  DISABLE_COPY(UserAdminHandler);

 public:
  /// Constructor
  UserAdminHandler() = default;
  /// Destructor
  ~UserAdminHandler() = default;

  bool canHandle(HttpRequest& request, HttpResponse& response) override;
};

#endif  // USER_ADMIN_HANDLER_HPP_
