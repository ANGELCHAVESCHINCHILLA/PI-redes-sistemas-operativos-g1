// Copyright © 2023 Camilo Suárez Sandí

#include "UserAdminHandler.hpp"

#include <jsoncpp/json/json.h>

#include <iostream>

#include "../../../configuration.hpp"
#include "../../../http/HttpServer.hpp"

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

  if (request.getMethod() == "POST") {
    if (request.getTarget().getPath() == "/admin/add_user") {
      try {
        Configuration& configuration = Configuration::getInstance();

        std::string db_address = configuration.getServer("db").address;
        std::string db_port =
            std::to_string(configuration.getServer("db").port);

        HttpRequest http_request("POST http://" + db_address + ":" + db_port +
                                 "/data/personal_data HTTP/1.1\n\n\n" +
                                 request.getBody() + "\n");

        auto future = HttpServer::fetch(http_request);

        HttpResponse http_response = future.get();

        response.setStatusCode(http_response.getStatusCode());
      } catch (const std::runtime_error& error) {
        std::cerr << error.what() << ".\n";
        response.setStatusCode(401);
      }

      return true;
    }
  }

  return false;
}
