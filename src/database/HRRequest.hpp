// Copyright © 2023 Camilo Suárez Sandí

#ifndef HR_REQUEST_HPP_
#define HR_REQUEST_HPP_

#include <string>

typedef unsigned char byte;

class HRRequest {
 public:
  static const std::string CREATE_TABLE_QUERY;

  static const std::string INSERT_INTO_QUERY;

 private:
  std::string user;
  int id;
  byte state;
  std::string padding;
  std::string information;
  std::string feedback;
  std::string requestType;
  int vacationDays;
  int vacationStartDate;
  int vacationEndDate;
  std::string area;

  // Constructor
  HRRequest() = default;

 public:
  // Destructor
  ~HRRequest() = default;

 private:
  // Copy Constructor
  HRRequest(const HRRequest& other) = delete;

  // Copy Assignment Operator
  HRRequest& operator=(const HRRequest& other) = delete;

  // Move Constructor
  HRRequest(HRRequest&& other) = default;

  // Move Assignment Operator
  HRRequest& operator=(HRRequest&& other) = default;

 public:
  const std::string& getUser() const;
  int getID() const;
  byte getState() const;
  const std::string& getPadding() const;
  const std::string& getInformation() const;
  const std::string& getFeedback() const;
  const std::string& getRequestType() const;
  int getVacationDays() const;
  int getVacationStartDate() const;
  int getVacationEndDate() const;
  const std::string& getArea() const;

  std::string getInsertIntoQuery() const;

  // Inner Class
  class Builder;
};

class HRRequest::Builder {
 private:
  HRRequest object;

 public:
  Builder& setUser(const std::string& value);
  Builder& setID(int value);
  Builder& setState(byte value);
  Builder& setPadding(const std::string& value);
  Builder& setInformation(const std::string& value);
  Builder& setFeedback(const std::string& value);
  Builder& setRequestType(const std::string& value);
  Builder& setVacationDays(int value);
  Builder& setVacationStartDate(int value);
  Builder& setVacationEndDate(int value);
  Builder& setArea(const std::string& value);

  HRRequest build();
};

#endif  // HR_REQUEST_HPP_
