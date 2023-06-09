// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#include "JobDataHandler.hpp"

bool JobDataHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getTarget().getPath() == "/data/job_data") {
    // if (request.getMethod() == "GET") {
    //   if (this->getData(request, response)) {
    //     return true;
    //   }
    // }

    // if (request.getMethod() == "POST") {
    //   if (this->addData(request, response)) {
    //     return true;
    //   }
    // }

    // if (request.getMethod() == "DELETE") {
    //   if (this->removeData(request, response)) {
    //     return true;
    //   }
    // }

    // if (request.getMethod() == "PUT") {
    //   if (this->editData(request, response)) {
    //     return true;
    //   }
    // }
  }

  return false;
}

bool JobDataHandler::getData(HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();

    output["user"] = user;
    // output["vacation_days"] = vacation_days;
    // output["gross_salary"] = gross_salary;
    // output["net_salary"] = net_salary;
    // output["salary_start_date"] = salary_start_date;
    // output["salary_end_date"] = salary_end_date;

    std::string json = Json::writeString(writer, output);

    response.setStatusCode(200);
    response.getBody() << json;
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool JobDataHandler::addData(HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();
    int vacation_days = input["vacation_days"].asInt();
    double gross_salary = input["gross_salary"].asDouble();
    double net_salary = input["net_salary"].asDouble();
    int salary_start_date = input["salary_start_date"].asInt();
    int salary_end_date = input["salary_end_date"].asInt();

    response.setStatusCode(200);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool JobDataHandler::removeData(HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();

    response.setStatusCode(200);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool JobDataHandler::editData(HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();
    int vacation_days = input["vacation_days"].asInt();
    double gross_salary = input["gross_salary"].asDouble();
    double net_salary = input["net_salary"].asDouble();
    int salary_start_date = input["salary_start_date"].asInt();
    int salary_end_date = input["salary_end_date"].asInt();

    response.setStatusCode(200);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}
