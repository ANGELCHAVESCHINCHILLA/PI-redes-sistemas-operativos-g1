// Copyright © 2023 Camilo Suárez Sandí

#include "Database.hpp"

#include <iostream>
#include <sstream>

Database::Database(const char* absolute_path) : reference(nullptr) {
  int error = SQLITE_OK;

  error = sqlite3_open(absolute_path, &this->reference);

  if (error) {
    // TODO: Replace with an exception
    std::cerr << "Can't open the database.\n";
  }

  if (!error) {
    error = this->createTables();

    if (error) {
      std::cerr << "Can't create the tables.\n";
    }
  }
}

Database::~Database() {
  if (this->reference != nullptr) {
    sqlite3_close(this->reference);
  }
}

Database& Database::getInstance(const char* absolute_path) {
  static Database instance(absolute_path);

  return instance;
}

int Database::createTables() {
  int error = SQLITE_OK;

  error = this->createPersonalDataTable();

  if (!error) {
    error = this->createAnnotationTable();
  }

  if (!error) {
    error = this->createRequestTable();
  }

  if (!error) {
    error = this->createWorkDataTable();
  }

  return error;
}

int Database::addPersonalData(const std::string usuario,
    const std::string nombre_empleado, const std::string nombre_puesto,
    const std::string nombre_empresa, const std::string correo,
    unsigned int telefono) {
  int error = SQLITE_OK;

  std::stringstream ss;

  ss << "INSERT INTO DatosPersonales (";
  ss << "Usuario, NombreEmpleado, NombrePuesto, NombreEmpresa, Correo, "
        "Telefono";
  ss << ") ";

  // TODO: Make the instance that stores this data to have a method that returns
  // this string.
  ss << "VALUES (";
  ss << "'" << usuario << "', ";
  ss << "'" << nombre_empleado << "', ";
  ss << "'" << nombre_puesto << "', ";
  ss << "'" << nombre_empresa << "', ";
  ss << "'" << correo << "', ";
  ss << telefono;
  ss << ");";

  std::string string = ss.str();

  const char* query = string.c_str();

  #ifdef DEBUG
  std::cout << query << "\n";
  #endif  // DEBUG

  char* error_message;

  error =
      sqlite3_exec(this->reference, query, nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";

    sqlite3_free(error_message);
  }

  return error;
}

int Database::printAllPersonalData() {
  int error = SQLITE_OK;

  const char* query = "SELECT * FROM DatosPersonales;";

  sqlite3_stmt* statement;

  error = sqlite3_prepare_v2(this->reference, query, -1, &statement, nullptr);

  if (error != SQLITE_OK) {
    // TODO: Replace with an exception
    std::cerr << "Can't read the database.\n";
  }

  while (sqlite3_step(statement) == SQLITE_ROW) {
    const char* usuario =
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
    const char* nombre_empleado =
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
    const char* nombre_puesto =
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
    const char* nombre_empresa =
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
    const char* correo =
        reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
    int telefono = sqlite3_column_int(statement, 5);

    std::cout << "Usuario: " << usuario << "\n";
    std::cout << "NombreEmpleado: " << nombre_empleado << "\n";
    std::cout << "NombrePuesto: " << nombre_puesto << "\n";
    std::cout << "NombreEmpresa: " << nombre_empresa << "\n";
    std::cout << "Correo: " << correo << "\n";
    std::cout << "Telefono: " << telefono << "\n";
    std::cout << "\n";
  }

  sqlite3_finalize(statement);

  return error;
}

int Database::createPersonalDataTable() {
  int error = SQLITE_OK;

  const char* query =
      "CREATE TABLE IF NOT EXISTS "
      "DatosPersonales "
      "("
      "Usuario CHAR(16), "
      "NombreEmpleado CHAR(32), "
      "NombrePuesto CHAR(32), "
      "NombreEmpresa CHAR(32), "
      "Correo CHAR(32), "
      "Telefono INT"
      ");";

  #ifdef DEBUG
  std::cout << query << "\n";
  #endif  // DEBUG

  char* error_message;

  error =
      sqlite3_exec(this->reference, query, nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";

    sqlite3_free(error_message);
  }

  return error;
}

int Database::createAnnotationTable() {
  int error = SQLITE_OK;

  const char* query =
      "CREATE TABLE IF NOT EXISTS "
      "Anotacion "
      "("
      "Usuario CHAR(16), "
      "ID INT, "
      "Informacion CHAR(256)"
      ");";

  #ifdef DEBUG
  std::cout << query << "\n";
  #endif  // DEBUG

  char* error_message;

  error =
      sqlite3_exec(this->reference, query, nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";

    sqlite3_free(error_message);
  }

  return error;
}

int Database::createRequestTable() {
  int error = SQLITE_OK;

  const char* query =
      "CREATE TABLE IF NOT EXISTS "
      "Solicitud "
      "("
      "Usuario CHAR(16), "
      "ID INT, "
      "Estado TINYINT, "
      "Relleno BLOB(391), "
      "Informacion BLOB(412)"
      ");";

  #ifdef DEBUG
  std::cout << query << "\n";
  #endif  // DEBUG

  char* error_message;

  error =
      sqlite3_exec(this->reference, query, nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";

    sqlite3_free(error_message);
  }

  return error;
}

int Database::createWorkDataTable() {
  int error = SQLITE_OK;

  const char* query =
      "CREATE TABLE IF NOT EXISTS "
      "DatosLaborales "
      "("
      "Usuario CHAR(16), "
      "SaldoVacaciones TINYINT, "
      "SalarioBruto INT, "
      "SalarioNeto INT, "
      "FechaInicioSalario INT, "
      "FechaFinSalario INT"
      ");";

  #ifdef DEBUG
  std::cout << query << "\n";
  #endif  // DEBUG

  char* error_message;

  error =
      sqlite3_exec(this->reference, query, nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";

    sqlite3_free(error_message);
  }

  return error;
}
