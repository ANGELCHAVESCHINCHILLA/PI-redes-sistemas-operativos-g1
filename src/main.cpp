//

#include <iostream>

#include "error.hpp"
#include "fs.hpp"

void printError(int error);

int main(int argc, char** argv) {
  int error = EXIT_SUCCESS;

  FS fs;

  fs.create("a.dat");
  // std::cout << fs.toString() << "\n";
  fs.append("a.dat", 'a');
  std::cout << fs.toString() << "\n";

  fs.create("b.dat");
  // std::cout << fs.toString() << "\n";
  fs.append("b.dat", 'b');
  std::cout << fs.toString() << "\n";

  fs.append("b.dat", 'b');
  std::cout << fs.toString() << "\n";

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
