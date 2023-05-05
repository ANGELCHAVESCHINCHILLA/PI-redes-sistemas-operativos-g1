// @Copyright 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <iostream>

#include "error.hpp"
#include "fs.hpp"

void printError(int error);

int main() {
  int error = EXIT_SUCCESS;

  FS fs;

  fs.create("a.dat");
  // std::cout << fs.toString() << "\n";
  error = fs.append("a.dat", 'a');
  std::cout << "----- Created a.dat and added a -----" << "\n";
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  fs.create("b.dat");
  // std::cout << fs.toString() << "\n";
  error = fs.append("b.dat", 'b');
  std::cout << "----- Created b.dat and added b -----" << "\n";
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  error = fs.append("b.dat", 'b');
  std::cout << "----- Added b to b.dat -----" << "\n";
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  error = fs.append("a.dat", 'a');
  std::cout << "----- Added a to a.dat -----" << "\n";
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  std::cout << "----- Removed a.dat -----" << "\n";
  error = fs.remove("a.dat");
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  std::cout << "----- Deeply removed b.dat -----" << "\n";
  error = fs.deepRemove("b.dat");
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  fs.create("c.dat");
  std::cout << "----- Created c.dat empty -----" << "\n";
  if (error != Error::OK) {
    printError(error);
    return error;
  }
  std::cout << fs.toString() << "\n";

  std::cout << "----- Removed c.dat -----" << "\n";
  error = fs.remove("c.dat");
  if (error != Error::OK) {
    printError(error);
    return error;
  }
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
