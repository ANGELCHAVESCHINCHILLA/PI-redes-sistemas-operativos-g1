// Copyright © 2023 Camilo Suárez Sandí

#ifndef PERSONAL_DATA_HPP_
#define PERSONAL_DATA_HPP_

#include <string>

class PersonalData {
 public:
  static const std::string CREATE_TABLE_QUERY;

  static const std::string INSERT_INTO_QUERY;

 private:
  std::string user;
  std::string employee_name;
  std::string job_name;
  std::string company_name;
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

  // Move Constructor
  PersonalData(PersonalData&& other) = default;

  // Move Assignment Operator
  PersonalData& operator=(PersonalData&& other) = default;

 public:
  const std::string& getUser() const;
  const std::string& getEmployeeName() const;
  const std::string& getJobName() const;
  const std::string& getCompanyName() const;
  const std::string& getEmail() const;
  int getPhoneNumber() const;

  std::string getInsertIntoQuery() const;

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
  Builder& setCompanyName(const std::string& value);
  Builder& setEmail(const std::string& value);
  Builder& setPhoneNumber(int value);

  PersonalData build();
};

#endif  // PERSONAL_DATA_HPP_
