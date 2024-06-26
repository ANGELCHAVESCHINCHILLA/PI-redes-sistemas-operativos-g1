// Copyright © Ignacio Robles Mayorga

#include "./DatabaseAPI.hpp"

DatabaseAPI::DatabaseAPI() {
  
}

DatabaseAPI::~DatabaseAPI() {

}

static int consultVacationBalanceByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  (void) argc;
  (void) szColName;

  std::cout << szColName[0] << " = " << argv[0] << std::endl;
  strcpy(reinterpret_cast<char*>(NotUsed), argv[0]);
  return 0;
}

std::string DatabaseAPI::consultVacationBalanceByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::string result = "user not found";

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
  (void) szColName;

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

std::vector<std::vector<std::string>> DatabaseAPI::consultSalaryByUser(const std::string user) const {
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
  (void) argc;
  (void) szColName;

  std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(NotUsed);
  vector->push_back(argv[0]);
  std::cout << "the annotation was: " << argv[0] << std::endl;
  return 0;
}

std::vector<std::string> DatabaseAPI::consultRecordAnnotationsByUser(const std::string user) const {
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

static int consultNameAndAreaByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  (void) argc;
  (void) szColName;

  std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(NotUsed);
  vector->push_back(argv[0]);
  vector->push_back(argv[1]);
  std::cout << "the name is: " << argv[0] << "and the area is: " << argv[1] << std::endl;
  return 0;
}

std::vector<std::string> DatabaseAPI::consultNameAndAreaByUser(const std::string user) const {
  int error = SQLITE_OK;

  std::vector<std::string> result;
  std::vector<std::string>* pointer = &result;

  char* error_message;

  std::string query = "SELECT EmployeeName, Area from PersonalData where User = '";
  query.append(user);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultNameAndAreaByUserCallback, pointer, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult name and area" );
  }
  
  return result;
}

static int consultRequestsMadeByUserCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  (void) szColName;

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

std::vector<std::vector<std::string>> DatabaseAPI::consultRequestsMadeByUser(const std::string user) const {
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

bool DatabaseAPI::makeRequest(const std::string user, const std::string requestType,
 const std::string information, const std::string area, const int vacationDays,
 const int vacationStartDate, const int vacationEndDate) const {
  int error = SQLITE_OK;

  bool result = false;

  HRRequest::Builder builder = HRRequest::Builder();

  builder.setUser(user);
  // builder.setID(23); // generate it
  builder.setState(0);
  builder.setSupState(0);
  builder.setInformation(information);
  builder.setFeedback(" "); // empty for now
  builder.setRequestType(requestType);
  builder.setVacationDays(vacationDays);
  builder.setVacationStartDate(vacationStartDate);
  builder.setVacationEndDate(vacationEndDate);
  builder.setArea(area);

  HRRequest hr_request = builder.build();

  error = this->database.addHRRequest(hr_request);

  if (!error) {
    result = true;
  } else {
    std::cerr << "could not add row to HRRequest database" << std::endl;
  }
  
  return result;
}

static int getRequestsMadeByAreaCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  (void) szColName;

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

std::vector<std::vector<std::string>> DatabaseAPI::getRequestsMadeByArea(const std::string area) const {
  int error = SQLITE_OK;

  std::vector<std::vector<std::string>> result;
  std::vector<std::vector<std::string>>* pointer = &result;

  char* error_message;

  std::string query = "SELECT * from HRRequest where Area = '";
  query.append(area);
  query.append("'");

  error =
    sqlite3_exec(this->database.reference, query.c_str(), getRequestsMadeByAreaCallback, pointer, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from get requests by area" );
  }
  
  return result;
}

bool DatabaseAPI::checkRequest(const int requestID, const int state,  const int supState, const std::string feedback) const {
  int error = SQLITE_OK;
  bool result = false;
  char* error_message;

  std::string query = "UPDATE HRRequest SET State = ";
  query.append(std::to_string(state));
  query.append(", Feedback = '");
  query.append(feedback);
  query.append("', SupState = ");
  query.append(std::to_string(supState));
  std::cout << supState << std::endl;
  query.append(" WHERE ID = ");
  query.append(std::to_string(requestID));
  query.append(";");

  error = sqlite3_exec(this->database.reference, query.c_str(),
      nullptr, nullptr, &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "PPP"<< "\n";
    sqlite3_free(error_message);
  } else {
    result = true;
  }
  
  return result;
}

static int getRequestByIDCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  (void) szColName;
  std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(NotUsed);

  for (int i = 0; i < argc; ++i) {
    std::string value = argv[i] != nullptr ? argv[i] : " ";
    vector->push_back(value);
  }
  return 0;
}

std::vector<std::string> DatabaseAPI::getRequestByID(const int requestID) const {
  int error = SQLITE_OK;

  std::vector<std::string> result;
  std::vector<std::string>* pointer = &result;
  char* error_message;

  std::string query = "SELECT * from HRRequest where ID = ";
  query.append(std::to_string(requestID));
  error =
    sqlite3_exec(this->database.reference, query.c_str(), getRequestByIDCallback, pointer, &error_message);
  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from get request by id" );
  }
  return result;
}

static int idWasFoundCallback(void* NotUsed, int argc, char** argv, char** szColName) {
  (void) argc;
  (void) argv;
  (void) szColName;

  bool* result = reinterpret_cast<bool*>(NotUsed);
  *result = true;
  return 0;
}

bool DatabaseAPI::idWasFound(const int id) const {
  int error = SQLITE_OK;

  bool result = false;

  char* error_message;

  std::string query = "SELECT * from HRRequest where ID = ";
  query.append(std::to_string(id));

  error =
    sqlite3_exec(this->database.reference, query.c_str(), idWasFoundCallback, &result, &error_message);

  if (error != SQLITE_OK) {
    result = false;
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
  }
  
  return result;
}

bool DatabaseAPI::makeAnnotation(const std::string user, const std::string information) const {
  int error = SQLITE_OK;

  bool result = false;

  Annotation::Builder builder = Annotation::Builder();

  builder.setUser(user);
  builder.setInformation(information);

  Annotation annotation = builder.build();

  error = this->database.addAnnotation(annotation);

  if (!error) {
    result = true;
  } else {
    std::cerr << "could not add row to Annotation database" << std::endl;
  }
  
  return result;
}
