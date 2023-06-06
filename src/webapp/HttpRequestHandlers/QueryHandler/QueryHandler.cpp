// Copyright © 2023 Ángel Chaves Chinchilla

#include "QueryHandler.hpp"
#include <iostream>

#include "../../../net/TcpClient.hpp"

bool QueryHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  (void) response;

  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath().find("consult") != std::string::npos) {
      // create a Tcp Client
      std::shared_ptr<TcpClient> client(new TcpClient);
      // Connect the socket of the TCP Client with the Data Base Server
      Socket& DBSocket = (*client).connect(this->server.data(), this->port.data());
      // Send the HTTP Request
      int error = DBSocket.send(request.buildString());

      std::string result;

      if (!error) {
        // receive the response of the server
        error = DBSocket.receive(result);
      } else {
        throw std::runtime_error(request.getTarget().getPath()
          + ": Could not be sent to Data Base Server");
      }

      if (!error) {
        // Construct the response received
        HttpResponse DBResponse(result);

        // parse the response receivde
        DBResponse.parseHttpResponse(result);

        // If the received response has a succesfull status code
        if(200 <= DBResponse.getStatusCode() && DBResponse.getStatusCode()
          < 300) {
          // TODO: Construir la respuesta que se enviará al cliente.
        } else {
          //
        }
      }
      throw std::runtime_error("Could not receive from File System Server");
    }
  }
  return false;
}