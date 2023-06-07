// Copyright © 2023 Ángel Chaves Chinchilla

#include "AddUserHandler.hpp"

#include "../../../net/TcpClient.hpp";

bool AddUserHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "POST" &&
      request.getTarget().getPath() == "/adduser") {

    Log::getInstance().write(Log::INFO, "AddUserRequestHandled"
      , request.getTarget().getPath());
    const std::string& body = request.getBody();

    if (this->couldAddUser(request)) {
      // this will be received by the JS, so the only matter is the status code
      return this->serveAny(response, 200);
    } else {
      // this will be received by the JS, so the only matter is the status code
      return this->serveAny(response, 400);
    }
    // Send
    // Log::getInstance().write(
    //     Log::INFO, "ResponseSend", "Response Sent with body:" + response.);
    return true;
  }
  return false;
}

bool AddUserHandler::couldAddUser(HttpRequest& request) {
  std::shared_ptr<TcpClient> client(new TcpClient());

  // Connect with fylesystem server
  Socket& addUserSocket = (*client).connect(this->server.data(), this->port.data());

  // send a request to add the user
  int error = addUserSocket.send(request.buildString());

  std::string response;

  if (!error) {
    // receive the response of the server
    error = addUserSocket.receive(response);
  } else {
    throw std::runtime_error(request.getTarget().getPath()
      + ": Could not send request to File System Server");
  }

  if (!error) {
      // Construct the response received
    HttpResponse addUserResponse(response);

    // parse the response received
    addUserResponse.parseHttpResponse(response);

    // If is the received response has a succesfull status code then return true
    return 200 <= addUserResponse.getStatusCode()
          && addUserResponse.getStatusCode() < 300;
  }
    throw std::runtime_error("Could not receive from File System Server");
}
