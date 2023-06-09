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
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath().find("consult") != std::string::npos) {
      /*
      Esto es para testear sin conectarse a la base de datos utilizando datos
      genéricos
      return testSalary(response);

      return testVacations(response);

      return testAnnotations(response);
      */

     return testAnnotations(response);

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
  responseJson["name"] = "Carlos Montoya";
  responseJson["company_name"] = "Apple";

  // Crea el objeto "salaries" y agrega los salarios
  Json::Value salaries;
  Json::Value salary1;
  salary1["gross_salary"] = 2000;
  salary1["net_salary"] = 3000;
  salary1["salary_start_date"] = 230323;
  salaries["salary1"] = salary1;

  Json::Value salary2;
  salary2["gross_salary"] = 3000;
  salary2["net_salary"] = 4000;
  salary2["salary_start_date"] = 230523;
  salaries["salary2"] = salary2;

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
  responseJson["name"] = "Miranda Jop";
  responseJson["company_name"] = "Amazon";

  Json::Value annotations;
  annotations["annotation1"] = "Miranda chocó el carro en el parqueo de la compañía el día 22/3/23";
  annotations["annotation2"] = "Miranda se robó una computadora el día 23/3/23";
  annotations["annotation3"] = "Miranda llegó 30 minutos tarde el día 1/5/23";

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
