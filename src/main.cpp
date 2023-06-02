// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <iostream>

#include "database/Database.hpp"

int main(int argc, char* argv[]) {
  int error = SQLITE_OK;

  // this path didn't work, changed to database.bd
  // char* path = "/home/usr/PI-redes-sistemas-operativos-g1/database.db";
  char* path = "database.db";

  Database& database = Database::getInstance(path);

  PersonalData::Builder builder = PersonalData::Builder();

  builder.setUser("1");
  builder.setEmployeeName("2");
  builder.setJobName("3");
  builder.setCompanyName("4");
  builder.setEmail("5");
  builder.setPhoneNumber(6);

  PersonalData personal_data = builder.build();

  error = database.addPersonalData(personal_data);

  if (!error) {
    std::vector<PersonalData> users = database.searchPersonalDataByUser("1");

    for (auto& personal_data : users) {
      std::cout << personal_data.getEmail() << "\n";
    }
  }

  return error;
}
