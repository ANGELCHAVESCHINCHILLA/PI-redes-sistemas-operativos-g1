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

  std::string query = "SELECT VacationDays from JobData where User = ";
  query.append(user);

  error =
    sqlite3_exec(this->database.reference, query.c_str(), consultVacationBalanceByUserCallback, const_cast<char*>(result.c_str()), &error_message);

  if (error != SQLITE_OK) {
    std::cerr << error_message << "\n";
    sqlite3_free(error_message);
    throw std::runtime_error("failed at exec from consult vacations balance" );
  }

  return result;
}
