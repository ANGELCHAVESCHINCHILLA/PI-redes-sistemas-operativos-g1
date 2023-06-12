// Copyright © 2023 Camilo Suárez Sandí

#include "UserAdminHandler.hpp"

#include <jsoncpp/json/json.h>

#include <iostream>

#include "../../../common/Log.hpp"
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
    // Add user in the database
    if (request.getTarget().getPath() == "/admin/add_user/data") {
      try {
        Log::getInstance().write(Log::DEBUG, "UserAdminHandler", "Call database to add a user");
        this->callDatabase(request, response, "POST", "/data/personal_data");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::WARNING, "UserAdminHandler", error.what());
        response.setStatusCode(401);
      }

      return true;
    }

    // Add a user in the file system
    if (request.getTarget().getPath() == "/admin/add_user/auth") {
      try {
        Log::getInstance().write(Log::DEBUG, "UserAdminHandler", "Call file system to add a user");
        this->callFileSystem(request, response, "POST", "/auth/user");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::WARNING, "UserAdminHandler", error.what());
        response.setStatusCode(401);
      }

      return true;
    }

    // Edit a user in the database
    if (request.getTarget().getPath() == "/admin/edit_user/data") {
      try {
        Log::getInstance().write(Log::DEBUG, "UserAdminHandler", "Call database to edit a user");
        this->callDatabase(request, response, "PUT", "/data/personal_data");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::WARNING, "UserAdminHandler", error.what());
        response.setStatusCode(401);
      }

      return true;
    }

    // Edit a user in the file system
    if (request.getTarget().getPath() == "/admin/edit_user/auth") {
      try {
        Log::getInstance().write(Log::DEBUG, "UserAdminHandler", "Call file system to edit a user");
        this->callFileSystem(request, response, "PUT", "/auth/user");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::WARNING, "UserAdminHandler", error.what());
        response.setStatusCode(401);
      }

      return true;
    }

    // Remove a user in the database
    if (request.getTarget().getPath() == "/admin/remove_user/data") {
      try {
        Log::getInstance().write(Log::DEBUG, "UserAdminHandler", "Call database to remove a user");
        this->callDatabase(request, response, "DELETE", "/data/personal_data");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::WARNING, "UserAdminHandler", error.what());
        response.setStatusCode(401);
      }

      return true;
    }

    // Remove a user in the file system
    if (request.getTarget().getPath() == "/admin/remove_user/auth") {
      try {
        Log::getInstance().write(Log::DEBUG, "UserAdminHandler", "Call file system to remove a user");
        this->callFileSystem(request, response, "DELETE", "/auth/user");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::WARNING, "UserAdminHandler", error.what());
        response.setStatusCode(401);
      }

      return true;
    }
  }

  return false;
}

void UserAdminHandler::callDatabase(HttpRequest& request,
    HttpResponse& response, const std::string& method,
    const std::string& path) {
  Configuration& configuration = Configuration::getInstance();

  std::string db_address = configuration.getServer("db").address;
  std::string db_port = std::to_string(configuration.getServer("db").port);

  HttpRequest db_request;

  db_request.setMethod(method);
  db_request.setTarget("http://" + db_address + ":" + db_port + path);
  db_request.setBody(request.getBody());

  auto future = HttpServer::fetch(db_request);

  HttpResponse db_response = future.get();

  response.setStatusCode(db_response.getStatusCode());
}

void UserAdminHandler::callFileSystem(HttpRequest& request,
    HttpResponse& response, const std::string& method,
    const std::string& path) {
  Configuration& configuration = Configuration::getInstance();

  std::string fs_address = configuration.getServer("fs").address;
  std::string fs_port = std::to_string(configuration.getServer("fs").port);

  HttpRequest fs_request;

  fs_request.setMethod(method);
  fs_request.setTarget("http://" + fs_address + ":" + fs_port + path);
  fs_request.setBody(request.getBody());

  auto future = HttpServer::fetch(fs_request);

  HttpResponse fs_response = future.get();

  response.setStatusCode(fs_response.getStatusCode());
}
