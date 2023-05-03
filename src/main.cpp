#include <iostream>

#include "fs.hpp"

int main(int, char**) {
  FS fs;

  fs.create("a.dat");
  fs.append("a.dat", 'a');

  std::cout << fs.toString() << "\n";
}
