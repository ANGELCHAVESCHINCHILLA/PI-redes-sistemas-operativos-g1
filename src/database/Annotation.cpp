// Copyright © 2023 Camilo Suárez Sandí

#include "Annotation.hpp"

#include <sstream>

const std::string Annotation::CREATE_TABLE_QUERY =
    R"(CREATE TABLE IF NOT EXISTS Annotation (
    User CHAR(16),
    ID INT,
    Information CHAR(256)
);
)";

const std::string Annotation::INSERT_INTO_QUERY =
    R"(INSERT INTO Annotation (User, ID, Information) )";

const std::string Annotation::SELECT_FROM_QUERY = R"(SELECT * FROM Annotation )";

const std::string& Annotation::getUser() const {
  return this->user;
}

int Annotation::getID() const {
  return this->id;
}

const std::string& Annotation::getInformation() const {
  return this->information;
}

std::string Annotation::getInsertIntoQuery() const {
  std::stringstream ss;

  ss << Annotation::INSERT_INTO_QUERY;
  ss << "VALUES ('";
  ss << this->user;
  ss << "', '";
  ss << this->id;
  ss << "', '";
  ss << this->information;
  ss << ");";

  return std::move(ss.str());
}

std::string Annotation::getSelectFromWhereQuery(const std::string& user) {
  std::stringstream ss;

  ss << Annotation::SELECT_FROM_QUERY;
  ss << "WHERE ";
  ss << "user = " << user;
  ss << ";";

  return std::move(ss.str());
}

Annotation::Builder& Annotation::Builder::setUser(const std::string& value) {
  this->object.user = value;
  return *this;
}

Annotation::Builder& Annotation::Builder::setID(int value) {
  this->object.id = value;
  return *this;
}

Annotation::Builder& Annotation::Builder::setInformation(
    const std::string& value) {
  this->object.information = value;
  return *this;
}

Annotation Annotation::Builder::build() {
  return std::move(this->object);
}
