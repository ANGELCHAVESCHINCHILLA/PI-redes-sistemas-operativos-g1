// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include "app/Database.hpp"

int main(int argc, char* argv[]) {
  int error = SQLITE_OK;

  char* path = "/home/usr/PI-redes-sistemas-operativos-g1/database.db";

  Database& database = Database::getInstance(path);

  error = database.addPersonalData("1", "2", "3", "4", "5", 6);

  if (!error) {
    error = database.printAllPersonalData();
  }

  return error;
}
