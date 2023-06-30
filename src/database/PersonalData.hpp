// Copyright © 2023 Camilo Suárez Sandí

#ifndef PERSONAL_DATA_HPP_
#define PERSONAL_DATA_HPP_

#include <string>

class PersonalData {
 public:
  static const std::string CREATE_TABLE_QUERY;

  static const std::string INSERT_INTO_QUERY;

  static const std::string SELECT_FROM_QUERY;

 private:
  std::string user;
  std::string employee_name;
  std::string job_name;
  std::string area;
  std::string email;
  int phone_number;

  // Constructor
  PersonalData() = default;

 public:
  // Destructor
  ~PersonalData() = default;

 private:
  // Copy Constructor
  PersonalData(const PersonalData& other) = delete;

  // Copy Assignment Operator
  PersonalData& operator=(const PersonalData& other) = delete;

 public:
  // Move Constructor
  PersonalData(PersonalData&& other) = default;

  // Move Assignment Operator
  PersonalData& operator=(PersonalData&& other) = default;

  const std::string& getUser() const;
  const std::string& getEmployeeName() const;
  const std::string& getJobName() const;
  const std::string& getArea() const;
  const std::string& getEmail() const;
  int getPhoneNumber() const;

  std::string getInsertIntoQuery() const;

  std::string getUpdateQuery() const;

  static std::string getSelectFromWhereQuery(const std::string& user);

  // Inner Class
  class Builder;
};

class PersonalData::Builder {
 private:
  PersonalData object;

 public:
  Builder& setUser(const std::string& value);
  Builder& setEmployeeName(const std::string& value);
  Builder& setJobName(const std::string& value);
  Builder& setArea(const std::string& value);
  Builder& setEmail(const std::string& value);
  Builder& setPhoneNumber(int value);

  PersonalData build();
};

#endif  // PERSONAL_DATA_HPP_
