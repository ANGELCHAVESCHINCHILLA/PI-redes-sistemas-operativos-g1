// Copyright © Ignacio Robles Mayorga

#include "./DatabaseApp.hpp"
// TODO: include all requestHandlers

DatabaseApp::DatabaseApp() {
  // this->initHandlers();
  // this->database = Database::getInstance(path);
}

DatabaseApp::~DatabaseApp() {

}

bool DatabaseApp::start() {
  return true;
}

bool DatabaseApp::run(HttpRequest& request, HttpResponse& response) {
  /*
  for (auto& handler : this->requestHandlers) {
    if (handler->canHandle(request, response)) {
      return true;
    }
  }
  */
  return false;
}

static int consultVacationBalanceByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  std::cout << szColName[0] << " = " << argv[0] << std::endl;
  strcpy(reinterpret_cast<char*>(NotUsed), argv[0]);
  return 0;
}

std::string DatabaseApp::consultVacationBalanceByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::string result = "          ";

  char* error_message;

  std::string query = "SELECT VacationDays from JobData where User = '";
  query.append(user);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultVacationBalanceByUserCallback, const_cast<char*>(result.c_str()), &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult vacations balance" );
  }

  return result;
}

static int consultSalaryByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  std::vector<std::vector<std::string>>* matrix = reinterpret_cast<std::vector<std::vector<std::string>>*>(NotUsed);
  std::vector<std::string> row;
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << " "; 
    std::string value = argv[i];
    row.push_back(value);
  }
  matrix->push_back(row);
  std::cout << std::endl;
  return 0;
}

std::vector<std::vector<std::string>> DatabaseApp::consultSalaryByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::vector<std::vector<std::string>> result;
  std::vector<std::vector<std::string>>* pointer = &result;

  char* error_message;

  std::string query = "SELECT GrossSalary, NetSalary, SalaryStartDate from JobData where User = '";
  query.append(user);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultSalaryByUserCallback, pointer, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult salary" );
  }
  
  return result;
}

static int consultRecordAnnotationsByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(NotUsed);
  vector->push_back(argv[0]);
  std::cout << "the annotation was: " << argv[0] << std::endl;
  return 0;
}

std::vector<std::string> DatabaseApp::consultRecordAnnotationsByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::vector<std::string> result;
  std::vector<std::string>* pointer = &result;

  char* error_message;

  std::string query = "SELECT Information from Annotation where User = '";
  query.append(user);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultRecordAnnotationsByUserCallback, pointer, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult annotation" );
  }
  
  return result;
}

static int consultNameAndEnterpriseByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(NotUsed);
  vector->push_back(argv[0]);
  vector->push_back(argv[1]);
  std::cout << "the name is: " << argv[0] << "and the company is: " << argv[1] << std::endl;
  return 0;
}

std::vector<std::string> DatabaseApp::consultNameAndEnterpriseByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::vector<std::string> result;
  std::vector<std::string>* pointer = &result;

  char* error_message;

  std::string query = "SELECT EmployeeName, CompanyName from PersonalData where User = '";
  query.append(user);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultNameAndEnterpriseByUserCallback, pointer, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult name and enterprise" );
  }
  
  return result;
}

static int consultRequestsMadeByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  std::vector<std::vector<std::string>>* matrix = reinterpret_cast<std::vector<std::vector<std::string>>*>(NotUsed);
  std::vector<std::string> row;
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << " "; 
    std::string value = argv[i];
    row.push_back(value);
  }
  matrix->push_back(row);
  std::cout << std::endl;
  return 0;
}

std::vector<std::vector<std::string>> DatabaseApp::consultRequestsMadeByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::vector<std::vector<std::string>> result;
  std::vector<std::vector<std::string>>* pointer = &result;

  char* error_message;

  std::string query = "SELECT * from HRRequest where User = '";
  query.append(user);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultRequestsMadeByUserCallback, pointer, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult requests" );
  }
  
  return result;
}
