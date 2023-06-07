// Copyright © 2023 Ángel Chaves Chinchilla

#include "QueryHandler.hpp"
#include <iostream>

#include "../../../net/TcpClient.hpp"

bool testSalary(HttpResponse& response);

bool testVacations(HttpResponse& response);

bool testAnnotations(HttpResponse& response);

/*
Un ejemplo de una solicitud que manejaría este Handler es:

POST /consultVacationBalanceByUser HTTP/1.1
Host: 127.0.0.1:8080
Content-Length: 27
... mas encabezados que le pone el navegador.....
Content-Type: application/json
Referer: http://127.0.0.1:8080/index.html


{"username":"Juan Alberto"}

Juan Alberto sería el username que consulta por el balance de vacaciones
Esta solicitud se envía tal y como viene a la base de datos, por lo que la base
de datos debe trabajarlo como POST y que el username venga en el body tipo JSON.
*/

bool QueryHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  (void) response;

  // {"username":"adf","password":"sdf"}
  if (request.getMethod() == "POST") {
    if (request.getTarget().getPath().find("consult") != std::string::npos) {
      /*
      Esto es para testear sin conectarse a la base de datos utilizando datos
      genéricos
      return testSalary(response);

      return testVacations(response);

      return testAnnotations(response);
      */

      // create and connect Tcp Client with the Data Base Server
      std::shared_ptr<TcpClient> client(new TcpClient);
      Socket& DBSocket = (*client).connect(this->server.data()
        , this->port.data());

      // Send the HTTP Request
      int error = DBSocket.send(request.buildString());

      // Receive the HTTP Response from Data Base server.
      std::string result;
      if (!error) {
        // receive the response of the server
        error = DBSocket.receive(result);
      } else {
        throw std::runtime_error(request.getTarget().getPath()
          + ": Could not be sent to Data Base Server");
      }

      if (!error) {
        // Construct the response received as a HttpResponse Object
        HttpResponse DBResponse(result);

        // parse the response received
        // TODO: this parse method is not complete yet
        DBResponse.parseHttpResponse(result);

        // If the received response has a succesfull status code
        if (200 <= DBResponse.getStatusCode() && DBResponse.getStatusCode()
          < 300) {
          // TODO: Construir la respuesta que se enviará al cliente.
        } else {
          // TODO: ver si se envía algun otro tipo de error o con este es enough
          this->serveAny(response, 400);
        }
      }
      throw std::runtime_error("Could not receive from Data Base Server");
    }
  }
  return false;
}


// Eliminar cuando ya database y webapp estén correctamente conectados
bool testSalary(HttpResponse& response) {
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

  HttpRequestHandler::serveAny(response, 200, "application/json", jsonString);

  return true;
}

// Eliminar cuando ya database y webapp estén correctamente conectados
bool testVacations(HttpResponse& response) {
  Json::Value responseJson;
  responseJson["vacationBalance"] = 30;

  Json::StreamWriterBuilder builder;
  builder["indentation"] = "\t";
  std::ostringstream jsonStream;
  std::string jsonString;

  std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
  jsonWriter->write(responseJson, &jsonStream);
  jsonString = jsonStream.str();

  std::cout << "EL JSON GENERADO FUE:\n"
  << jsonString << std::endl
  << std::endl;

  HttpRequestHandler::serveAny(response, 200, "application/json", jsonString);

  return true;
}

// Eliminar cuando ya database y webapp estén correctamente conectados
bool testAnnotations(HttpResponse& response) {
  Json::Value responseJson;
  responseJson["name"] = "Angel Chaves";
  responseJson["company_name"] = "Guachimanes SA";

  Json::Value annotations(Json::arrayValue);
  annotations.append("Incumplimiento de baño");
  annotations.append("Llegó tarde");
  annotations.append("Se le acusa de robo a mano armada");

  responseJson["annotations"] = annotations;

  Json::StreamWriterBuilder builder;
  builder["indentation"] = "\t";
  std::ostringstream jsonStream;
  std::string jsonString;

  std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
  jsonWriter->write(responseJson, &jsonStream);
  jsonString = jsonStream.str();

  std::cout << "EL JSON GENERADO FUE:\n"
  << jsonString << std::endl
  << std::endl;

  HttpRequestHandler::serveAny(response, 200, "application/json", jsonString);

  return true;
}
