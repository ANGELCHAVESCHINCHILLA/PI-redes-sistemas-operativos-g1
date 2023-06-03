// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include "database/DatabaseApp.hpp"

int main(int argc, char* argv[]) {
  int error = SQLITE_OK;

  // this path didn't work, changed to database.bd
  // char* path = "/home/usr/PI-redes-sistemas-operativos-g1/database.db";
  char* path = "database.db";

  // Database& database = Database::getInstance(path);
  DatabaseApp databaseApp;

  JobData::Builder builder = JobData::Builder();

  builder.setUser("1");
  builder.setVacationDays(2);
  builder.setGrossSalary(3);
  builder.setNetSalary(4);
  builder.setSalaryStartDate(5);
  builder.setSalaryEndDate(6);

  JobData job_data = builder.build();

  error = databaseApp.database.addJobData(job_data);

  if (!error) {
    // error = database.printAllPersonalData();
    try {
      std::string vacationBalance = databaseApp.consultVacationBalanceByUser("1");
      std::cout << "we got " << vacationBalance << std::endl;
    } catch (std::runtime_error e) {
      std::cout << "exception " << e.what() << std::endl;
    }
  } else {
    std::cout << "error at adding job data" << std::endl;
  }

  return error;
}
