// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <sqlite3.h>

#include <string>

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

  // TODO: Create a class that stores this data then pass an instance of that
  // class as a parameter.
  int addPersonalData(const std::string usuario,
      const std::string nombre_empleado, const std::string nombre_puesto,
      const std::string nombre_empresa, const std::string correo,
      unsigned int telefono);

  int printAllPersonalData();

 private:
  int createTables();

  int createPersonalDataTable();

  int createAnnotationTable();

  int createRequestTable();

  int createWorkDataTable();
};

#endif  // DATABASE_HPP_
