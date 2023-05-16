// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <assert.h>

#include <iostream>

#include "error.hpp"
#include "menu/FSMenu.hpp"

void printError(int error);

int main() {
  int error = EXIT_SUCCESS;

  FSMenu* menu = FSMenu::getInstance();

  menu->start();

  return error;
}

void printError(int error) {
  switch (error) {
    case Error::OK:
      std::cerr << "Everything is ok.\n";
      break;

    case Error::NOT_OK:
      std::cerr << "Something went wrong.\n";
      break;

    case Error::NO_SPACE_IN_DIRECTORY:
      std::cerr << "There is no space in the directory.\n";
      break;

    case Error::NO_SPACE_IN_FAT:
      std::cerr << "There is no space in the FAT.\n";
      break;

    case Error::FILE_NOT_FOUND:
      std::cerr << "File not found in the directory.\n";
      break;

    case Error::INVALID_FILE:
      std::cerr << "Found an invalid file.\n";
      break;

    default:
      std::cerr << "Unknown error happened.\n";
      break;
  }
}
