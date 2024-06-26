// Copyright © 2023 Camilo Suárez Sandí

#include "Database.hpp"

#include <iostream>
#include <sstream>

Database::Database(const char* absolute_path) : reference(nullptr) {
  int error = SQLITE_OK;

  error = sqlite3_open(absolute_path, &this->reference);

  if (error) {
    throw std::runtime_error("Can't open the database");
  }

  if (!error) {
    error = this->createTables();

    if (error) {
      throw std::runtime_error("Can't create the tables");
    }
  }
}

Database::~Database() {
  if (this->reference != nullptr) {
    sqlite3_close(this->reference);
  }
}

Database& Database::getInstance(const char* absolute_path) {
  static Database instance(absolute_path);

  return instance;
}

int Database::query(const char* query) {
  int error = SQLITE_OK;

  char* error_message;

  error =
      sqlite3_exec(this->reference, query, nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    Log::getInstance().write(Log::ERROR, "Database", error_message);

    sqlite3_free(error_message);
  }

  return error;
}

int Database::createTables() {
  int error = SQLITE_OK;

  error = this->query(PersonalData::CREATE_TABLE_QUERY.c_str());

  if (!error) {
    error = this->query(Annotation::CREATE_TABLE_QUERY.c_str());
  }

  if (!error) {
    error = this->query(HRRequest::CREATE_TABLE_QUERY.c_str());
  }

  if (!error) {
    error = this->query(JobData::CREATE_TABLE_QUERY.c_str());
  }

  return error;
}

int Database::addPersonalData(const PersonalData& personal_data) {
  int error = SQLITE_OK;

  error = this->query(personal_data.getInsertIntoQuery().c_str());

  return error;
}

int Database::addAnnotation(const Annotation& annotation) {
  int error = SQLITE_OK;

  error = this->query(annotation.getInsertIntoQuery().c_str());

  return error;
}

int Database::addHRRequest(const HRRequest& hr_request) {
  int error = SQLITE_OK;

  error = this->query(hr_request.getInsertIntoQuery().c_str());

  return error;
}

int Database::addJobData(const JobData& job_data) {
  int error = SQLITE_OK;

  error = this->query(job_data.getInsertIntoQuery().c_str());

  return error;
}

std::vector<PersonalData> Database::searchPersonalDataByUser(
    const std::string& user) {
  int error = SQLITE_OK;

  std::vector<PersonalData> users;

  std::string query = PersonalData::getSelectFromWhereQuery(user);

  sqlite3_stmt* statement;

  error =
      sqlite3_prepare(this->reference, query.c_str(), -1, &statement, nullptr);

  if (error != SQLITE_OK) {
    throw std::runtime_error("Can't search Personal Data");
  }

  if (!error) {
    while (sqlite3_step(statement) == SQLITE_ROW) {
      PersonalData::Builder builder = PersonalData::Builder();

      builder.setUser(
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
      builder.setEmployeeName(
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
      builder.setJobName(
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
      builder.setArea(
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
      builder.setEmail(
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
      builder.setPhoneNumber(sqlite3_column_int(statement, 5));

      PersonalData personal_data = builder.build();

      users.push_back(std::move(personal_data));
    }
  }

  sqlite3_finalize(statement);

  return users;
}

std::vector<JobData> Database::searchJobDataByUser(const std::string& user) {
  int error = SQLITE_OK;

  std::vector<JobData> users;

  std::string query = JobData::getSelectFromWhereQuery(user);

  sqlite3_stmt* statement;

  error =
      sqlite3_prepare(this->reference, query.c_str(), -1, &statement, nullptr);

  if (error != SQLITE_OK) {
    throw std::runtime_error("Can't search JobData");
  }

  if (!error) {
    while (sqlite3_step(statement) == SQLITE_ROW) {
      JobData::Builder builder = JobData::Builder();

      builder.setUser(
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
      builder.setVacationDays(sqlite3_column_int(statement, 1));
      builder.setGrossSalary(sqlite3_column_int(statement, 2));
      builder.setNetSalary(sqlite3_column_int(statement, 3));
      builder.setSalaryStartDate(sqlite3_column_int(statement, 4));
      builder.setSalaryEndDate(sqlite3_column_int(statement, 5));

      JobData job_data = builder.build();

      users.push_back(std::move(job_data));
    }
  }

  sqlite3_finalize(statement);

  return users;
}

int Database::removePersonalDataByUser(const std::string& user) {
  int error = SQLITE_OK;

  std::string query = "DELETE FROM PersonalData WHERE user = '" + user + "'";

  error = this->query(query.c_str());

  return error;
}

int Database::removeJobDataByUser(const std::string& user) {
  int error = SQLITE_OK;

  std::string query = "DELETE FROM JobData WHERE user = '" + user + "'";

  error = this->query(query.c_str());

  return error;
}

int Database::editPersonalData(const PersonalData& personal_data) {
  int error = SQLITE_OK;

  std::string query = personal_data.getUpdateQuery();

  error = this->query(query.c_str());

  return error;
}

int Database::editJobData(const JobData& job_data) {
  int error = SQLITE_OK;

  std::string query = job_data.getUpdateQuery();

  error = this->query(query.c_str());

  return error;
}
