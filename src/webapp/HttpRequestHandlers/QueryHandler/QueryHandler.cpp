// Copyright © 2023 Ángel Chaves Chinchilla

#include "QueryHandler.hpp"
#include <iostream>

#include "../../../common/Log.hpp"
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
... mas encabezados que le pone el navegador.....
Referer: http://127.0.0.1:8080/index.html

Juan sería el username que consulta por el balance de vacaciones
Esta solicitud se envía tal y como viene a la base de datos, por lo que la base
de datos debe trabajarlo como GET y que el username venga como un Query.
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
        // send request to and receive response from data base server
        Log::getInstance().write(Log::DEBUG, "QueryHandler", "Query Handler call to the database");
        return this->callBDToGetQuery(request, response, "GET");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::DEBUG, "QueryHandler", error.what());
        response.setStatusCode(401);
      }
    }
  }
  if (request.getMethod() == "POST") {
    if (request.getTarget().getPath().find("Request") != std::string::npos) {
      try {
        return this->callBDToGetQuery(request, response, "POST");
      } catch (const std::runtime_error& error) {
        Log::getInstance().write(Log::DEBUG, "QueryHandler", error.what());
        response.setStatusCode(401);
      }
    }
  }
  return false;
}

bool QueryHandler::callBDToGetQuery(HttpRequest& request, HttpResponse& response, const std::string& method) {
  Configuration& configuration = Configuration::getInstance();
  // IP adress of data base server
  std::string db_address = configuration.getServer("db").address;
  // port in which data base server is listenning
  std::string db_port = std::to_string(configuration.getServer("db").port);
  // request to be send to data base server
  HttpRequest DBRequest;
  // Construct request with our needs
  DBRequest.setMethod(method);
  DBRequest.setTarget("http://" + db_address + ":" + db_port + request.getTarget().getInput());
  DBRequest.setBody(request.getBody());

  // std::cout << "Request que se enviará a Data Base" << std::endl;
  // std::cout << DBRequest.toString() << std::endl;

  // Send request to data base and store its result in future
  auto future = HttpServer::fetch(DBRequest);

  // Get data received and create a HttResponse
  HttpResponse DBResponse = future.get();

  // Build our DBReponse
  response.setStatusCode(DBResponse.getStatusCode());
  response.getBody() << DBResponse.getBody().str();
  response.setHeader("Content-Type", "application/json");
  return response.buildResponse();
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


