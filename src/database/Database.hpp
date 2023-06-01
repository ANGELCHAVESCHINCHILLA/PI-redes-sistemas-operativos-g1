// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <sqlite3.h>

#include <string>

#include "Annotation.hpp"
#include "HRRequest.hpp"
#include "JobData.hpp"
#include "PersonalData.hpp"

class Database {
 private:
  sqlite3* reference;

  /**
   * @brief Default constructor.
   *
   */
  explicit Database(const char* absolute_path);

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

 public:
  static Database& getInstance(const char* absolute_path);

  int query(const char* query);

  int addPersonalData(const PersonalData& personal_data);

  int printAllPersonalData();

 private:
  int createTables();
};

#endif  // DATABASE_HPP_
