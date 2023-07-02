// Copyright © 2023 Camilo Suárez Sandí

#include "WebLogHandler.hpp"

#include <jsoncpp/json/json.h>

#include <iostream>

#include "../../common/Log.hpp"
#include "../../configuration.hpp"
#include "../../http/HttpServer.hpp"

WebLogHandler::WebLogHandler() : log_handler("log.log") {
  //
}

bool WebLogHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getTarget().getPath() == "/log/web/count") {
    int error = this->log_handler.read();

    if (error != -1) {
      size_t count = this->log_handler.getLinesCount();

      response.getBody() << count;
      response.setStatusCode(200);
    } else {
      response.setStatusCode(500);
    }

    return true;
  }

  return false;
}

void WebLogHandler::callDatabase(HttpRequest& request, HttpResponse& response,
    const std::string& method, const std::string& path) {
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

void WebLogHandler::callFileSystem(HttpRequest& request, HttpResponse& response,
    const std::string& method, const std::string& path) {
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
