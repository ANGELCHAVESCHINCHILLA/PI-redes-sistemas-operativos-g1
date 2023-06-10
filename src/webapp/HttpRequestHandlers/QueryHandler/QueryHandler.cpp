// Copyright © 2023 Ángel Chaves Chinchilla

#include "QueryHandler.hpp"
#include <iostream>

#include "../../../configuration.hpp"
#include "../../../http/HttpServer.hpp"

bool testSalary(HttpResponse& response);

bool testVacations(HttpResponse& response);

bool testAnnotations(HttpResponse& response);

bool testStateRequests(HttpResponse& response);

bool testRequestID(HttpResponse& response);

/*
Un ejemplo de una solicitud que manejaría este Handler es:

GET /consultVacationBalanceByUser?user=Juan HTTP/1.1
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
      // Esto es para testear sin conectarse a la base de datos utilizando datos
      // genéricos
      if (request.getTarget().getPath().find("consultRequestsByUser") != std::string::npos) {
        return testStateRequests(response);
      } else if (request.getTarget().getPath().find("consultRequestsByID") != std::string::npos) {
        return testRequestID(response);
      } else if (request.getTarget().getPath().find("consultSalaryByUser") != std::string::npos) {
        return testSalary(response);
      } else if (request.getTarget().getPath().find("consultVacationBalanceByUser") != std::string::npos) {
        return testVacations(response);
      } else if (request.getTarget().getPath().find("consultAnnotationsByUser") != std::string::npos) {
        return testAnnotations(response);
      }
      */
      try {
        this->callBDToGetQuery(request, response);
      } catch (const std::runtime_error& error) {
        std::cerr << error.what() << ".\n";
        response.setStatusCode(401);
      }

      // // create and connect Tcp Client with the Data Base Server
      // std::shared_ptr<TcpClient> client(new TcpClient);
      // Socket& DBSocket = (*client).connect(this->server.data()
      //   , this->port.data());

      // // Send the HTTP Request
      // int error = DBSocket.send(request.buildString());

      // // Receive the HTTP Response from Data Base server.
      // std::string result;
      // if (!error) {
      //   // receive the response of the server
      //   error = DBSocket.receive(result);
      // } else {
      //   throw std::runtime_error(request.getTarget().getPath()
      //     + ": Could not be sent to Data Base Server");
      // }

      // if (!error) {
      //   // Construct the response received as a HttpResponse Object
      //   HttpResponse DBResponse(result);

      //   // parse the response received
      //   // TODO: this parse method is not complete yet
      //   DBResponse.parseHttpResponse(result);

      //   // If the received response has a succesfull status code
      //   if (200 <= DBResponse.getStatusCode() && DBResponse.getStatusCode()
      //     < 300) {
      //     // TODO: Construir la respuesta que se enviará al cliente.
      //   } else {
      //     // TODO: ver si se envía algun otro tipo de error o con este es enough
      //     this->serveAny(response, 400);
      //   }
      // }
      // throw std::runtime_error("Could not receive from Data Base Server");
    }
  }
  return false;
}

void QueryHandler::callBDToGetQuery(HttpRequest& request, HttpResponse& response) {
  Configuration& configuration = Configuration::getInstance();

  std::string db_address = configuration.getServer("db").address;
  std::string db_port = std::to_string(configuration.getServer("db").port);

  HttpRequest DBRequest;

  DBRequest.setMethod("GET");
  DBRequest.setTarget("http://" + db_address + ":" + db_port + request.getTarget().getPath());
  DBRequest.setBody(request.getBody());

  // DBRequest.setHeader("host", db_address + ":" + db_port);

  std::cout << "Request que se enviará a Data Base" << std::endl;
  std::cout << DBRequest.toString() << std::endl;

  auto future = HttpServer::fetch(DBRequest);

  HttpResponse http_response = future.get();

  response.setStatusCode(http_response.getStatusCode());
  response.getBody() << http_response.getBody().str();
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

// Eliminar cuando ya database y webapp estén correctamente conectados
bool testStateRequests(HttpResponse& response) {
  Json::Value responseJson;
  
  // Crear el objeto request1
  Json::Value request1;
  request1["user"] = "Juan";
  request1["ID"] = 3;
  request1["state"] = 0;
  request1["padding"] = "          ";
  request1["information"] = "Hola, por favor puedo tener mi constancia salarial?";
  request1["feedback"] = "   ";
  request1["request_type"] = "ConstanciaSalarial";
  request1["vacation_days"] = 0;
  request1["vacation_start_date"] = 0;
  request1["vacation_end_date"] = 0;
  request1["area"] = "Cartago";
  
  // Crear el objeto request2
  Json::Value request2;
  request2["user"] = "Juan";
  request2["ID"] = 7;
  request2["state"] = 1;
  request2["padding"] = "          ";
  request2["information"] = "Hola, por favor puedo tener mis 13 días de vacaciones?";
  request2["feedback"] = "   ";
  request2["request_type"] = "Vacaciones";
  request2["vacation_days"] = 13;
  request2["vacation_start_date"] = 11223;
  request2["vacation_end_date"] = 151223;
  request2["area"] = "Cartago";
  
  // Agregar los objetos request1 y request2 al objeto responseJson
  responseJson["request1"] = request1;
  responseJson["request2"] = request2;

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
bool testRequestID(HttpResponse& response) {
  // Crear el objeto responseJson
  Json::Value responseJson;
  responseJson["user"] = "Juan";
  responseJson["ID"] = 3;
  responseJson["state"] = 0;
  responseJson["padding"] = "          ";
  responseJson["information"] = "Hola, por favor puedo tener mi constancia salarial?";
  responseJson["feedback"] = "   ";
  responseJson["request_type"] = "ConstanciaSalarial";
  responseJson["vacation_days"] = 0;
  responseJson["vacation_start_date"] = 0;
  responseJson["vacation_end_date"] = 0;
  responseJson["area"] = "Cartago";

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


