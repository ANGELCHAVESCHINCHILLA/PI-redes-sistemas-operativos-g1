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

  HRRequest::Builder builder = HRRequest::Builder();

  builder.setUser("Miguel");
  builder.setID(23);
  builder.setState(2);
  builder.setPadding("      ");
  builder.setInformation("Buenas tardes, quiero pedir la renuncia");
  builder.setFeedback("buenas tardes, no le podemos permitir renunciar");
  builder.setRequestType("Vacaciones");
  builder.setVacationDays(30);
  builder.setVacationStartDate(12345678);
  builder.setVacationEndDate(12345678);
  builder.setArea("San Jose");

  HRRequest hr_request = builder.build();

  error = databaseApp.database.addHRRequest(hr_request);

  if (error) {
    std::cout << "error at adding job data 1" << std::endl;
    return 0;
  }

  builder.setUser("Miguel");
  builder.setID(24);
  builder.setState(1);
  builder.setPadding("      ");
  builder.setInformation("Buenas tardes, quiero pedir mas vacaciones");
  builder.setFeedback("buenas tardes, esta bien, puede retirarse");
  builder.setRequestType("Vacaciones");
  builder.setVacationDays(30);
  builder.setVacationStartDate(12345678);
  builder.setVacationEndDate(12345678);
  builder.setArea("Cartago");

  HRRequest hr_request2 = builder.build();

  error = databaseApp.database.addHRRequest(hr_request2);

  if (!error) {
    try {
      std::vector<std::vector<std::string>> requests = databaseApp.consultRequestsMadeByUser("Miguel");
      for (int i = 0; i < requests.size(); i++) {
        for (int j = 0; j < requests[i].size(); ++j) {
          std::cout << requests[i][j] << " "; 
        }
        std::cout << std::endl;
      }
    } catch (std::runtime_error e) {
      std::cout << "exception " << e.what() << std::endl;
    }
  } else {
    std::cout << "error at adding job data 2" << std::endl;
  }

  return error;
}
