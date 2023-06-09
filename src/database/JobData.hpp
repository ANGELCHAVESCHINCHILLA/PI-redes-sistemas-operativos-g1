// Copyright © 2023 Camilo Suárez Sandí

#ifndef JOB_DATA_HPP_
#define JOB_DATA_HPP_

#include <string>

typedef unsigned char byte;

class JobData {
 public:
  static const std::string CREATE_TABLE_QUERY;

  static const std::string INSERT_INTO_QUERY;

  static const std::string SELECT_FROM_QUERY;

 private:
  std::string user;
  int vacation_days;
  int gross_salary;
  int net_salary;
  int salary_start_date;
  int salary_end_date;

  // Constructor
  JobData() = default;

 public:
  // Destructor
  ~JobData() = default;

 private:
  // Copy Constructor
  JobData(const JobData& other) = delete;

  // Copy Assignment Operator
  JobData& operator=(const JobData& other) = delete;

 public:
  // Move Constructor
  JobData(JobData&& other) = default;

  // Move Assignment Operator
  JobData& operator=(JobData&& other) = default;

 public:
  const std::string& getUser() const;
  int getVacationDays() const;
  int getGrossSalary() const;
  int getNetSalary() const;
  int getSalaryStartDate() const;
  int getSalaryEndDate() const;

  std::string getInsertIntoQuery() const;

  std::string getUpdateQuery() const;

  static std::string getSelectFromWhereQuery(const std::string& user);

  // Inner Class
  class Builder;
};

class JobData::Builder {
 private:
  JobData object;

 public:
  Builder& setUser(const std::string& value);
  Builder& setVacationDays(int value);
  Builder& setGrossSalary(int value);
  Builder& setNetSalary(int value);
  Builder& setSalaryStartDate(int value);
  Builder& setSalaryEndDate(int value);

  JobData build();
};

#endif  // JOB_DATA_HPP_
