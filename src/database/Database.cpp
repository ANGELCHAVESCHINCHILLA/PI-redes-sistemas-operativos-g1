// Copyright © 2023 Camilo Suárez Sandí

#include "Database.hpp"

#include <iostream>
#include <sstream>

Database::Database(const char* absolute_path) : reference(nullptr) {
  int error = SQLITE_OK;

  error = sqlite3_open(absolute_path, &this->reference);

  if (error) {
    // TODO: Replace with an exception
    std::cerr << "Can't open the database.\n";
  }

  if (!error) {
    error = this->createTables();

    if (error) {
      std::cerr << "Can't create the tables.\n";
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
    std::cerr << error_message << "\n";

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
    // TODO: Replace with an exception
    std::cerr << "Can't search PersonalData.\n";
  }

  if (!error) {
    while (sqlite3_step(statement) == SQLITE_ROW) {
      PersonalData::Builder builder = PersonalData::Builder();

      builder.setUser(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
      builder.setEmployeeName(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
      builder.setJobName(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
      builder.setCompanyName(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
      builder.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
      builder.setPhoneNumber(sqlite3_column_int(statement, 5));

      PersonalData personal_data = builder.build();

      users.push_back(std::move(personal_data));
    }
  }

  sqlite3_finalize(statement);

  return users;
}
