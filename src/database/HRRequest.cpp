// Copyright © 2023 Camilo Suárez Sandí

#include "HRRequest.hpp"

#include <sstream>
#include <iostream> // remove later

const std::string HRRequest::CREATE_TABLE_QUERY =
    R"(CREATE TABLE IF NOT EXISTS HRRequest (
    User CHAR(16),
    ID INTEGER PRIMARY KEY,
    State TINYINT,
    Padding BLOB(391),
    Information BLOB(412),
    Feedback BLOB(256),
    RequestType CHAR(20),
    VacationDays INT,
    VacationStartDate INT,
    VacationEndDate INT,
    Area CHAR(20)
);
)";

const std::string HRRequest::INSERT_INTO_QUERY =
    R"(INSERT INTO HRRequest (User, State, Padding, Information, Feedback, RequestType, VacationDays, VacationStartDate, VacationEndDate, Area) )";

const std::string& HRRequest::getUser() const {
  return this->user;
}

int HRRequest::getID() const {
  return this->id;
}

int HRRequest::getState() const {
  return this->state;
}

const std::string& HRRequest::getPadding() const {
  return this->padding;
}

const std::string& HRRequest::getInformation() const {
  return this->information;
}

const std::string& HRRequest::getFeedback() const {
  return this->feedback;
}

const std::string& HRRequest::getRequestType() const {
  return this->requestType;
}

int HRRequest::getVacationDays() const {
  return this->vacationDays;
}

int HRRequest::getVacationStartDate() const {
  return this->vacationStartDate;
}

int HRRequest::getVacationEndDate() const {
  return this->vacationEndDate;
}

const std::string& HRRequest::getArea() const {
  return this->area;
}

std::string HRRequest::getInsertIntoQuery() const {
  std::stringstream ss;

  ss << HRRequest::INSERT_INTO_QUERY;
  ss << "VALUES ('";
  ss << this->user;
  ss << "', '";
  ss << this->state;
  ss << "', '";
  ss << this->padding;
  ss << "', '";
  ss << this->information;
  ss << "', '";
  ss << this->feedback;
  ss << "', '";
  ss << this->requestType;
  ss << "', '";
  ss << this->vacationDays;
  ss << "', '";
  ss << this->vacationStartDate;
  ss << "', '";
  ss << this->vacationEndDate;
  ss << "', '";
  ss << this->area;
  ss << "');";

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

HRRequest::Builder& HRRequest::Builder::setState(int value) {
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

HRRequest::Builder& HRRequest::Builder::setFeedback(
    const std::string& value) {
  this->object.feedback = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setRequestType(
    const std::string& value) {
  this->object.requestType = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setVacationDays(int value) {
  this->object.vacationDays = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setVacationStartDate(int value) {
  this->object.vacationStartDate = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setVacationEndDate(int value) {
  this->object.vacationEndDate = value;
  return *this;
}

HRRequest::Builder& HRRequest::Builder::setArea(
    const std::string& value) {
  this->object.area = value;
  return *this;
}

HRRequest HRRequest::Builder::build() {
  return std::move(this->object);
}
