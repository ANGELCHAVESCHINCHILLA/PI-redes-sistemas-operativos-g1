// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <sqlite3.h>

#include <string>
#include <vector>

#include "Annotation.hpp"
#include "HRRequest.hpp"
#include "JobData.hpp"
#include "PersonalData.hpp"

class Database {
 private:
  /**
   * @brief Default constructor.
   *
   */
  explicit Database(const char* absolute_path);

 public:
  sqlite3* reference;

  /**
   * @brief Destructor.
   *
   */
  ~Database();

  // Copy Constructor
  Database(const Database& other) = delete;

  // Copy Assignment Operator
  Database& operator=(const Database& other) = delete;

  // Move Constructor
  Database(Database&& other) = delete;

  // Move Assignment Operator
  Database& operator=(Database&& other) = delete;

  static Database& getInstance(const char* absolute_path);

  int query(const char* query);

  int addPersonalData(const PersonalData& personal_data);

  int addAnnotation(const Annotation& annotation);

  int addHRRequest(const HRRequest& hr_request);

  int addJobData(const JobData& job_data);

  std::vector<PersonalData> searchPersonalDataByUser(const std::string& user);

  std::vector<JobData> searchJobDataByUser(const std::string& user);

  int removePersonalDataByUser(const std::string& user);

  int removeJobDataByUser(const std::string& user);

  int editPersonalData(const PersonalData& personal_data);

  int editJobData(const JobData& job_data);

 private:
  int createTables();
};

#endif  // DATABASE_HPP_
