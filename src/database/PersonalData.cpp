// Copyright © 2023 Camilo Suárez Sandí

#include "PersonalData.hpp"

#include <sstream>

#include "Database.hpp"

const std::string PersonalData::CREATE_TABLE_QUERY =
    R"(CREATE TABLE IF NOT EXISTS PersonalData (
    User CHAR(16),
    EmployeeName CHAR(32),
    JobName CHAR(32),
    Area CHAR(32),
    Email CHAR(32),
    PhoneNumber INT
);
)";

const std::string PersonalData::INSERT_INTO_QUERY =
    R"(INSERT INTO PersonalData (User, EmployeeName, JobName, Area, Email, PhoneNumber) )";

const std::string PersonalData::SELECT_FROM_QUERY =
    R"(SELECT * FROM PersonalData )";

const std::string& PersonalData::getUser() const {
  return this->user;
}

const std::string& PersonalData::getEmployeeName() const {
  return this->employee_name;
}

const std::string& PersonalData::getJobName() const {
  return this->job_name;
}

const std::string& PersonalData::getArea() const {
  return this->area;
}

const std::string& PersonalData::getEmail() const {
  return this->email;
}

int PersonalData::getPhoneNumber() const {
  return this->phone_number;
}

std::string PersonalData::getInsertIntoQuery() const {
  std::stringstream ss;

  ss << PersonalData::INSERT_INTO_QUERY;
  ss << "VALUES ('";
  ss << this->user;
  ss << "', '";
  ss << this->employee_name;
  ss << "', '";
  ss << this->job_name;
  ss << "', '";
  ss << this->area;
  ss << "', '";
  ss << this->email;
  ss << "', ";
  ss << this->phone_number;
  ss << ");";

  return std::move(ss.str());
}

std::string PersonalData::getUpdateQuery() const {
  std::stringstream ss;

  ss << "UPDATE PersonalData SET ";
  ss << "User = '" << this->user << "', ";
  ss << "EmployeeName = '" << this->employee_name << "', ";
  ss << "JobName = '" << this->job_name << "', ";
  ss << "Area = '" << this->area << "', ";
  ss << "Email = '" << this->email << "', ";
  ss << "PhoneNumber = " << this->phone_number << " ";
  ss << "WHERE user = '" << this->user << "'";

  return ss.str();
}

std::string PersonalData::getSelectFromWhereQuery(const std::string& user) {
  std::stringstream ss;

  ss << PersonalData::SELECT_FROM_QUERY;
  ss << "WHERE ";
  ss << "user = '" << user << "'";
  ss << ";";

  return std::move(ss.str());
}

PersonalData::Builder& PersonalData::Builder::setUser(
    const std::string& value) {
  this->object.user = value;
  return *this;
}

PersonalData::Builder& PersonalData::Builder::setEmployeeName(
    const std::string& value) {
  this->object.employee_name = value;
  return *this;
}

PersonalData::Builder& PersonalData::Builder::setJobName(
    const std::string& value) {
  this->object.job_name = value;
  return *this;
}

PersonalData::Builder& PersonalData::Builder::setArea(
    const std::string& value) {
  this->object.area = value;
  return *this;
}

PersonalData::Builder& PersonalData::Builder::setEmail(
    const std::string& value) {
  this->object.email = value;
  return *this;
}

PersonalData::Builder& PersonalData::Builder::setPhoneNumber(int value) {
  this->object.phone_number = value;
  return *this;
}

PersonalData PersonalData::Builder::build() {
  return std::move(this->object);
}
