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

    if (request.getMethod() == "DELETE") {
      if (this->removeData(request, response)) {
        return true;
      }
    }

    if (request.getMethod() == "PUT") {
      if (this->editData(request, response)) {
        return true;
      }
    }
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
    if (!reader.parse(request.getBody(), input)) {
      throw std::runtime_error("Can't parse the personal data json.");
    }

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
      output["area"] = personal_data.getArea();
      output["email"] = personal_data.getEmail();
      output["phone_number"] = personal_data.getPhoneNumber();
      // TODO: We know about this break, it should be removed
      break;
    }

    std::string json = Json::writeString(writer, output);

    response.setStatusCode(200);
    response.getBody() << json;
    Log::getInstance().write(Log::DEBUG, "PersonalDataHandler", "Get Data: Successful");
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
  } catch (const Json::LogicError& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
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
    if (!reader.parse(request.getBody(), input)) {
      throw std::runtime_error("Can't parse the personal data json.");
    }

    std::string user = input["user"].asString();
    std::string employee_name = input["employee_name"].asString();
    std::string job_name = input["job_name"].asString();
    std::string area = input["area"].asString();
    std::string email = input["email"].asString();
    int phone_number = input["phone_number"].asInt();

    PersonalData personal_data = PersonalData::Builder()
      .setUser(user)
      .setEmployeeName(employee_name)
      .setJobName(job_name)
      .setArea(area)
      .setEmail(email)
      .setPhoneNumber(phone_number)
      .build();

    if (this->databaseApi->database.addPersonalData(personal_data) != 0) {
      throw std::runtime_error("Can't add a personal data.");
    }

    response.setStatusCode(200);
    Log::getInstance().write(Log::DEBUG, "PersonalDataHandler", "Add Data: Successful");
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
  } catch (const Json::LogicError& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
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
    if (!reader.parse(request.getBody(), input)) {
      throw std::runtime_error("Can't parse the personal data json.");
    }

    std::string user = input["user"].asString();

    if (this->databaseApi->database.removePersonalDataByUser(user) != 0) {
      throw std::runtime_error("Can't remove a personal data.");
    }

    response.setStatusCode(200);
    Log::getInstance().write(Log::DEBUG, "PersonalDataHandler", "Remove Data: Successful");
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
  } catch (const Json::LogicError& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
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
    if (!reader.parse(request.getBody(), input)) {
      throw std::runtime_error("Can't parse the personal data json.");
    }

    std::string user = input["user"].asString();
    std::string employee_name = input["employee_name"].asString();
    std::string job_name = input["job_name"].asString();
    std::string area = input["area"].asString();
    std::string email = input["email"].asString();
    int phone_number = input["phone_number"].asInt();

    PersonalData personal_data = PersonalData::Builder()
      .setUser(user)
      .setEmployeeName(employee_name)
      .setJobName(job_name)
      .setArea(area)
      .setEmail(email)
      .setPhoneNumber(phone_number)
      .build();

    if (this->databaseApi->database.editPersonalData(personal_data) != 0) {
      throw std::runtime_error("Can't edit a personal data.");
    }

    response.setStatusCode(200);
    Log::getInstance().write(Log::DEBUG, "PersonalDataHandler", "Edit Data: Successful");
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
  } catch (const Json::LogicError& error) {
    response.setStatusCode(401);
    Log::getInstance().write(Log::WARNING, "PersonalDataHandler", error.what());
  }

  return true;
}
