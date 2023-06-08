// Copyright © 2023 Camilo Suárez Sandí

#include "UserAdminHandler.hpp"

bool UserAdminHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath() == "/admin") {
      if (this->servePage(request, response, "admin/admin.html")) {
        return true;
      }
    }

    if (request.getTarget().getPath() == "/admin/add_user") {
      if (this->servePage(request, response, "admin/add_user.html")) {
        return true;
      }
    }

    if (request.getTarget().getPath() == "/admin/remove_user") {
      if (this->servePage(request, response, "admin/remove_user.html")) {
        return true;
      }
    }

    if (request.getTarget().getPath() == "/admin/edit_user") {
      if (this->servePage(request, response, "admin/edit_user.html")) {
        return true;
      }
    }
  }

  return false;
}
