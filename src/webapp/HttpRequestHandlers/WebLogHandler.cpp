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
  if (this->log_handler.handleCount(request, response, "/log/web/count")) {
    return true;
  }

  if (this->log_handler.handleFile(request, response, "/log/web/file")) {
    return true;
  }

  if (request.getTarget().getPath() == "/log/db/count") {
    try {
      Log::getInstance().write(
          Log::DEBUG, "WebLogHandler", "Call database to get the logs count");
      this->callDatabase(request, response, "GET", "/log/db/count");
    } catch (const std::runtime_error& error) {
      Log::getInstance().write(Log::WARNING, "WebLogHandler", error.what());
      response.setStatusCode(401);
    }

    return true;
  }

  if (request.getTarget().getPath() == "/log/db/file") {
    try {
      Log::getInstance().write(
          Log::DEBUG, "WebLogHandler", "Call database to get the logs");
      this->callDatabase(request, response, "GET", "/log/db/file");
    } catch (const std::runtime_error& error) {
      Log::getInstance().write(Log::WARNING, "WebLogHandler", error.what());
      response.setStatusCode(401);
    }

    return true;
  }

  if (request.getTarget().getPath() == "/log/fs/count") {
    try {
      Log::getInstance().write(Log::DEBUG, "WebLogHandler",
          "Call file system to get the logs count");
      this->callFileSystem(request, response, "GET", "/log/fs/count");
    } catch (const std::runtime_error& error) {
      Log::getInstance().write(Log::WARNING, "WebLogHandler", error.what());
      response.setStatusCode(401);
    }

    return true;
  }

  if (request.getTarget().getPath() == "/log/fs/file") {
    try {
      Log::getInstance().write(
          Log::DEBUG, "WebLogHandler", "Call file system to get the logs");
      this->callFileSystem(request, response, "GET", "/log/fs/file");
    } catch (const std::runtime_error& error) {
      Log::getInstance().write(Log::WARNING, "WebLogHandler", error.what());
      response.setStatusCode(401);
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

  std::string query = request.getTarget().toString();

  query = query.substr(query.find_last_of('?') + 1);

  db_request.setMethod(method);
  db_request.setTarget(
      "http://" + db_address + ":" + db_port + path + "?" + query);
  db_request.setBody(request.getBody());

  auto future = HttpServer::fetch(db_request);

  HttpResponse db_response = future.get();

  response.setStatusCode(db_response.getStatusCode());
  response.getBody() << db_response.getBody().str();
}

void WebLogHandler::callFileSystem(HttpRequest& request, HttpResponse& response,
    const std::string& method, const std::string& path) {
  Configuration& configuration = Configuration::getInstance();

  std::string fs_address = configuration.getServer("fs").address;
  std::string fs_port = std::to_string(configuration.getServer("fs").port);

  HttpRequest fs_request;

  std::string query = request.getTarget().toString();

  query = query.substr(query.find_last_of('?') + 1);

  fs_request.setMethod(method);
  fs_request.setTarget(
      "http://" + fs_address + ":" + fs_port + path + '?' + query);
  fs_request.setBody(request.getBody());

  auto future = HttpServer::fetch(fs_request);

  HttpResponse fs_response = future.get();

  response.setStatusCode(fs_response.getStatusCode());
  response.getBody() << fs_response.getBody().str();
}
