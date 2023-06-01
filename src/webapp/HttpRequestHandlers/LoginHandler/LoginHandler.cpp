// Copyright © 2023 Ángel Chaves Chinchilla

#include "LoginHandler.hpp"
#include <iostream>


bool LoginHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "POST") {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(request.getBody(), root)) {
      std::runtime_error("Could not parse the JSON file from POST request");
    }

    std::string username = root["username"].asString();
    std::string hash = root["password"].asString();

    std::string payload = "{\"sub\":\"\' + subject + \'\"}" + username + "\"}";
    std::string secretKey = JWT::generateRandomKey(32);

    JWT token(secretKey, payload);

    Json::Value jsonResponse;
    jsonResponse["token"] = token.toString();

    return this->serveJWT(request, response, jsonResponse);
  }
  return false;
}

bool LoginHandler::validateUser(HttpRequest& request) {
  return true;
}


bool LoginHandler::serveAuthFailed(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse) {
  (void) httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(401);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-Type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Usuario o contraseña incorrecta";
  httpResponse.getBody()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <p>The requested resouce was not found on this server.</p>\n"
      << "  <hr><p><a href=\"/\">Login</a></p>\n"
      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.buildResponse();
}

bool LoginHandler::serveJWT(const HttpRequest& request, HttpResponse& response
    , Json::Value& jsonResponse) {

  response.setStatusCode(200);
  response.setHeader("Content-Type", "application/json");
  response.setHeader("Server", "AttoServer v1.0");

  Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, jsonResponse);

  response.getBody().str(jsonString);

  return response.buildResponse();
}