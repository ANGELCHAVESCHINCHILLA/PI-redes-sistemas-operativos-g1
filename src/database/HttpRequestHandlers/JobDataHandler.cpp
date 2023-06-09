// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#include "JobDataHandler.hpp"

bool JobDataHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getTarget().getPath() == "/data/job_data") {
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

bool JobDataHandler::getData(HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);

    std::string user = input["user"].asString();

    output["user"] = user;

    std::vector<JobData> job_data_list =
        this->databaseApi->database.searchJobDataByUser(user);

    if (job_data_list.empty()) {
      throw std::runtime_error("There is no job data for this user.");
    }

    // TODO: Only adds one personal data for now, change to add a list inside
    // the json
    for (auto& job_data : job_data_list) {
      output["vacation_days"] = job_data.getVacationDays();
      output["gross_salary"] = job_data.getGrossSalary();
      output["net_salary"] = job_data.getNetSalary();
      output["salary_start_date"] = job_data.getSalaryStartDate();
      output["salary_end_date"] = job_data.getSalaryEndDate();
      // TODO: We know about this break, it should be removed
      break;
    }

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

    JobData job_data = JobData::Builder()
      .setUser(user)
      .setVacationDays(vacation_days)
      .setGrossSalary(gross_salary)
      .setNetSalary(net_salary)
      .setSalaryStartDate(salary_start_date)
      .setSalaryEndDate(salary_end_date)
      .build();

    if (this->databaseApi->database.addJobData(job_data) != 0) {
      throw std::runtime_error("Can't add a job data.");
    }

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

    if (this->databaseApi->database.removeJobDataByUser(user) != 0) {
      throw std::runtime_error("Can't remove a job data.");
    }

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

    JobData job_data = JobData::Builder()
      .setUser(user)
      .setVacationDays(vacation_days)
      .setGrossSalary(gross_salary)
      .setNetSalary(net_salary)
      .setSalaryStartDate(salary_start_date)
      .setSalaryEndDate(salary_end_date)
      .build();

    if (this->databaseApi->database.editJobData(job_data) != 0) {
      throw std::runtime_error("Can't edit a job data.");
    }

    response.setStatusCode(200);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}
