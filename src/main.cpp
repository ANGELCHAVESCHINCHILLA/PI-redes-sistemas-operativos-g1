#include <iostream>

#include "fs.hpp"

int main(int, char**) {
  FS fs;

  try {
    if (fs.create("a.dat") == BLOCK_UNDEFINED) {
      throw std::runtime_error("There is no space in the directory.");
    }
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << "\n";
  }

  std::cout << fs.toString() << "\n";
}
