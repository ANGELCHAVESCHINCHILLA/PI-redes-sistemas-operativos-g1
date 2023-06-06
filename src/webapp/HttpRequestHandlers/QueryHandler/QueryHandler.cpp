// Copyright © 2023 Ángel Chaves Chinchilla

#include "QueryHandler.hpp"
#include <iostream>

#include "../../../net/TcpClient.hpp";

bool QueryHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "POST") {
    if (request.getTarget().getFullPath().find("consultSalaryByUser")
        != std::string::npos) {

      // Este código es para hacer pruebas, el real está más abajo
      Json::Value responseJson;
      responseJson["name"] = "Angel Chaves";
      responseJson["company_name"] = "Guachimanes SA";

      Json::Value salaries(Json::arrayValue);
      salaries.append(10000);  // Gross Salary
      salaries.append(8000);   // Net Salary
      salaries.append("2023-01-01");  // Salary Start Date

      responseJson["salaries"] = salaries;

      Json::StreamWriterBuilder builder;
      builder["indentation"] = "\t";
      std::ostringstream jsonStream;
      std::string jsonString;

      std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
      jsonWriter->write(responseJson, &jsonStream);
      jsonString = jsonStream.str();

      // std::cout << "EL JSON GENERADO FUE:\n"
      // << jsonString << std::endl
      // << std::endl;

      this->serveAny(response, 200, "application/json", jsonString);

      return true;
      // fin código de pruebas

      // INICIO CÓDIGO REAL
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
        throw std::runtime_error(request.getTarget().getFullPath()
          + ": Could not be sent to Data Base Server");
      }

      if (!error) {
        // Construct the response received
        HttpResponse DBResponse(result);

        // parse the response receivde
        // TODO: this parse is not complete
        DBResponse.parseHttpResponse(result);

        // If the received response has a succesfull status code
        if(200 <= DBResponse.getStatusCode() && DBResponse.getStatusCode()
          < 300) {
          // TODO: Construir la respuesta que se enviará al cliente.
          
        } else {
          this->serveAny(response, 400);
        }
      }
      throw std::runtime_error("Could not receive from File System Server");
    }
  }
  return false;
}