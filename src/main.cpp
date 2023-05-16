// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <assert.h>

#include <fstream>
#include <iostream>

#include "error.hpp"
#include "menu/FSMenu.hpp"

void printError(int error);

int writeUsers(FS* fs, const std::string& usersFileName,
    const std::string& usersSourceFileName);

int main() {
  int error = EXIT_SUCCESS;

  FSMenu* menu = FSMenu::getInstance();

  menu->start();

  return error;
}

int writeUsers(FS* fs, const std::string& usersFileName,
    const std::string& usersSourceFileName) {
  assert(fs);
  int error = EXIT_SUCCESS;
  // Open the source file
  std::ifstream usersSourceFile(usersSourceFileName, std::ifstream::in);
  // If could open the users source file
  if (usersSourceFile) {
    // Read from the file and write in our file system
    char character = '\0';

    while (usersSourceFile >> character && error == EXIT_SUCCESS) {
      error = fs->append(usersFileName, character);
    }

    usersSourceFile.close();
  } else {
    error = FILE_NOT_FOUND;
  }
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
