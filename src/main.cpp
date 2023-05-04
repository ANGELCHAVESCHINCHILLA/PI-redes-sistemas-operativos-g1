//

#include <iostream>

#include "error.hpp"
#include "fs.hpp"

void printError(int error);

int main(int, char**) {
  int error = EXIT_SUCCESS;

  FS fs;

  error = fs.create("a.dat");

  if (error != EXIT_SUCCESS) {
    printError(error);
    return error;
  }

  error = fs.append("a.dat", 'a');

  if (error != EXIT_SUCCESS) {
    printError(error);
    return error;
  }

  std::cout << fs.toString() << "\n";

  return error;
}

void printError(int error) {
  switch (error) {
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
