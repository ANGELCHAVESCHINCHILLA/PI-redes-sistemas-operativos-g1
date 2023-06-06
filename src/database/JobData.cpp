// Copyright © 2023 Camilo Suárez Sandí

#include "JobData.hpp"

#include <sstream>

const std::string JobData::CREATE_TABLE_QUERY =
    R"(CREATE TABLE IF NOT EXISTS JobData (
    User CHAR(16),
    VacationDays TINYINT,
    GrossSalary INT,
    NetSalary INT,
    SalaryStartDate INT,
    SalaryEndDate INT
);
)";

const std::string JobData::INSERT_INTO_QUERY =
    R"(INSERT INTO JobData (User, VacationDays, GrossSalary, NetSalary, SalaryStartDate, SalaryEndDate) )";

const std::string& JobData::getUser() const {
  return this->user;
}

int JobData::getVacationDays() const {
  return this->vacation_days;
}

int JobData::getGrossSalary() const {
  return this->gross_salary;
}

int JobData::getNetSalary() const {
  return this->net_salary;
}

int JobData::getSalaryStartDate() const {
  return this->salary_start_date;
}

int JobData::getSalaryEndDate() const {
  return this->salary_end_date;
}

std::string JobData::getInsertIntoQuery() const {
  std::stringstream ss;

  ss << JobData::INSERT_INTO_QUERY;
  ss << "VALUES ('";
  ss << this->user;
  ss << "', '";
  ss << this->vacation_days;
  ss << "', '";
  ss << this->gross_salary;
  ss << "', '";
  ss << this->net_salary;
  ss << "', '";
  ss << this->salary_start_date;
  ss << "', ";
  ss << this->salary_end_date;
  ss << ");";

  return std::move(ss.str());
}

JobData::Builder& JobData::Builder::setUser(const std::string& value) {
  this->object.user = value;
  return *this;
}

JobData::Builder& JobData::Builder::setVacationDays(int value) {
  this->object.vacation_days = value;
  return *this;
}

JobData::Builder& JobData::Builder::setGrossSalary(int value) {
  this->object.gross_salary = value;
  return *this;
}

JobData::Builder& JobData::Builder::setNetSalary(int value) {
  this->object.net_salary = value;
  return *this;
}

JobData::Builder& JobData::Builder::setSalaryStartDate(int value) {
  this->object.salary_start_date = value;
  return *this;
}

JobData::Builder& JobData::Builder::setSalaryEndDate(int value) {
  this->object.salary_end_date = value;
  return *this;
}

JobData JobData::Builder::build() {
  return std::move(this->object);
}
