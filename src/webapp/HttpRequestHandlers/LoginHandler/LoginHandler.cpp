// Copyright © 2023 Ángel Chaves Chinchilla

#include "LoginHandler.hpp"
#include <iostream>

#include "../../../net/TcpClient.hpp"


struct UserInfo {
 public:
  std::string username;
  std::string password;

 public:
  DECLARE_RULE4(UserInfo, default);

  UserInfo() = default;

  UserInfo(const std::string& username, const std::string& password)
    : username(username)
    , password(password) {
  }
};
class UserSession {
  /// Objects of this class can be copied, but avoid innecesary copies
  DECLARE_RULE4(UserSession, default);
 protected:
  std::shared_ptr<TcpClient> client;

  UserInfo userInfo;

 public:
  UserSession(HttpRequest& request)
      : client(new TcpClient()) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(request.getBody(), root)) {
      std::runtime_error("Could not parse the JSON file from POST request");
    }

    std::string username = root["username"].asString();
    std::string hash = root["password"].asString();

    this->userInfo.password = root["password"].asString();
    this->userInfo.username = root["username"].asString();

  }

  Socket& connect(const char* server, const char* port) {
    return (*this->client).connect(server, port);
  }
};

LoginHandler::LoginHandler(const std::string& server, const std::string& port)
    : server(server)
    , port(port) { 
  std::cout << "Client will connect to at http://" << server << ":" << port
    << "\n";
}

bool LoginHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "POST") {
    if (request.getTarget().getPath() == "/login") {
      bool served = false;
      // Create the info for current user
      UserSession user(request);

      // If the username and password are correct then
      if (this->isValidUser(request, user)) {
        // std::cout << "soy usuaro valido" << std::endl;
        // serve a valid response
        return this->serveAny(response, 200);
      } else {
        // serve an authentication failed
        served = this->serveAuthFailed(request, response);
      }
      return served;
    }
  }
  return false;
}

bool LoginHandler::isValidUser(HttpRequest& request, UserSession& user) {
  // TODO: remove this return true. Now works as bypass just to testing
  return true;
  // Connect with fylesystem server
  Socket& loginSocket = user.connect(this->server.data(), this->port.data());

  // send a request to know if is a valid user sendind username and password
  int error = loginSocket.send(request.buildString());

  std::string result;

  if (!error) {
    // receive the response from the FS server
    error = loginSocket.receive(result);
  } else {
    throw std::runtime_error("Could not send to File System Server");
  }

  if (!error) {
    // Construct the response received
    HttpResponse validationResponse(result);

    // parse the response received
    validationResponse.parseHttpResponse(result);

    // If is the received response has a succesfull status code then return true
    return 200 <= validationResponse.getStatusCode()
          && validationResponse.getStatusCode() < 300;
  }
  throw std::runtime_error("Could not receive from File System Server");
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


