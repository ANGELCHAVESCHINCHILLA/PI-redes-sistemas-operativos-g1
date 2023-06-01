// Copyright © 2023 Camilo Suárez Sandí

#ifndef PERSONAL_DATA_HPP_
#define PERSONAL_DATA_HPP_

#include <string>

typedef unsigned char byte;

class JobData {
 private:
  static const std::string CREATE_TABLE_QUERY;

  static const std::string INSERT_INTO_QUERY;

  std::string user;
  byte vacation_days;
  int gross_salary;
  int net_salary;
  int salary_start_date;
  int salary_end_date;

  // Constructor
  JobData() = default;

  // Destructor
  ~JobData() = default;

  // Copy Constructor
  JobData(const JobData& other) = delete;

  // Copy Assignment Operator
  JobData& operator=(const JobData& other) = delete;

  // Move Constructor
  JobData(JobData&& other) = default;

  // Move Assignment Operator
  JobData& operator=(JobData&& other) = default;

 public:
  const std::string& getUser() const;
  byte getVacationDays() const;
  int getGrossSalary() const;
  int getNetSalary() const;
  int getSalaryStartDate() const;
  int getSalaryEndDate() const;

  std::string getInsertIntoQuery() const;

  // Inner Class
  class Builder;
};

class JobData::Builder {
 private:
  JobData object;

 public:
  Builder& setUser(const std::string& value);
  Builder& setVacationDays(byte value);
  Builder& setGrossSalary(int value);
  Builder& setNetSalary(int value);
  Builder& setSalaryStartDate(int value);
  Builder& setSalaryEndDate(int value);

  JobData build();
};

#endif  // PERSONAL_DATA_HPP_
