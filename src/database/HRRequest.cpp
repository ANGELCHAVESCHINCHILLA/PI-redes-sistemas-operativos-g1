// Copyright © 2023 Camilo Suárez Sandí

#include "HRRequest.hpp"

#include <sstream>

const std::string HRRequest::CREATE_TABLE_QUERY =
    R"(CREATE TABLE HRRequest (
    User CHAR(16),
    ID INT,
    State TINYINT,
    Padding BLOB(391),
    Information BLOB(412)
);
)";

const std::string HRRequest::INSERT_INTO_QUERY =
    R"(INSERT INTO HRRequest (User, ID, State, Padding, Information) )";

const std::string& HRRequest::getUser() const {
  return this->user;
}

int HRRequest::getID() const {
  return this->id;
}

byte HRRequest::getState() const {
  return this->state;
}

const std::string& HRRequest::getPadding() const {
  return this->padding;
}

const std::string& HRRequest::getInformation() const {
  return this->information;
}

std::string HRRequest::getInsertIntoQuery() const {
  std::stringstream ss;

  ss << HRRequest::INSERT_INTO_QUERY;
  ss << "VALUES ('";
  ss << this->user;
  ss << "', '";
  ss << this->id;
  ss << "', '";
  ss << this->state;
  ss << "', '";
  ss << this->padding;
  ss << "', '";
  ss << this->information;
  ss << ");";

  return std::move(ss.str());
}

HRRequest::Builder& HRRequest::Builder::setUser(const std::string& value) {
  this->object.user = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setID(int value) {
  this->object.id = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setState(byte value) {
  this->object.state = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setPadding(const std::string& value) {
  this->object.padding = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setInformation(
    const std::string& value) {
  this->object.information = value;
  return *this;
}

HRRequest HRRequest::Builder::build() {
  return std::move(this->object);
}
