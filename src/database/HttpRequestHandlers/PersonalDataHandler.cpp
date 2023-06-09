// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#include "PersonalDataHandler.hpp"

bool PersonalDataHandler::canHandle(
    HttpRequest& request, HttpResponse& response) {
  if (request.getTarget().getPath() == "/data/personal_data") {
    if (request.getMethod() == "GET") {
      if (this->getData(request, response)) {
        return true;
      }
    }

    if (request.getMethod() == "POST") {
      if (this->addData(request, response)) {
        return true;
      }
    }

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

bool PersonalDataHandler::getData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();

    output["user"] = user;

    std::vector<PersonalData> personal_data_list =
        this->databaseApi->database.searchPersonalDataByUser(user);

    if (personal_data_list.empty()) {
      throw std::runtime_error("There is no personal data for this user.");
    }

    // TODO: Only adds one personal data for now, change to add a list inside
    // the json
    for (auto& personal_data : personal_data_list) {
      output["employee_name"] = personal_data.getEmployeeName();
      output["job_name"] = personal_data.getJobName();
      output["company_name"] = personal_data.getCompanyName();
      output["email"] = personal_data.getEmail();
      output["phone_number"] = personal_data.getPhoneNumber();
      // TODO: We know about this break, it should be removed
      break;
    }

    std::string json = Json::writeString(writer, output);

    response.setStatusCode(200);
    response.getBody() << json;
  } catch (const std::runtime_error& error) {
    std::cerr << error.what() << "\n";

    response.setStatusCode(401);
  }

  return true;
}

bool PersonalDataHandler::addData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();
    std::string employee_name = input["employee_name"].asString();
    std::string job_name = input["job_name"].asString();
    std::string company_name = input["company_name"].asString();
    std::string email = input["email"].asString();
    int phone_number = input["phone_number"].asInt();

    PersonalData personal_data = PersonalData::Builder()
      .setUser(user)
      .setEmployeeName(employee_name)
      .setJobName(job_name)
      .setCompanyName(company_name)
      .setEmail(email)
      .setPhoneNumber(phone_number)
      .build();

    this->databaseApi->database.addPersonalData(personal_data);

    response.setStatusCode(200);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool PersonalDataHandler::removeData(
    HttpRequest& request, HttpResponse& response) {
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

bool PersonalDataHandler::editData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();
    std::string employee_name = input["employee_name"].asString();
    std::string job_name = input["job_name"].asString();
    std::string company_name = input["company_name"].asString();
    std::string email = input["email"].asString();
    int phone_number = input["phone_number"].asInt();

    response.setStatusCode(200);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}
