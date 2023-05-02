//

#include <iostream>

#include "fs.hpp"

int main(int, char**) {
  FS fs;

  try {
    fs.create("a.dat");
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << "\n";
  }

  std::cout << fs.toString() << "\n";
}
