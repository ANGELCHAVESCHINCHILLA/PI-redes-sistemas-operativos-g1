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

int Database::addPersonalData(const PersonalData& personal_data) {
  int error = SQLITE_OK;

  error = this->query(personal_data.getInsertIntoQuery().c_str());

  return error;
}

// Don't use
// Add a method to every table that searches in the database
// The method should use the builder and return the instance with the data
int Database::printAllPersonalData() {
  int error = SQLITE_OK;

  const char* query = "SELECT * FROM ???;";

  sqlite3_stmt* statement;

  error = sqlite3_prepare_v2(this->reference, query, -1, &statement, nullptr);

  if (error != SQLITE_OK) {
    // TODO: Replace with an exception
    std::cerr << "Can't read the database.\n";
  }

  while (sqlite3_step(statement) == SQLITE_ROW) {
    // Remove when fixed
    break;
  }

  sqlite3_finalize(statement);

  return error;
}
