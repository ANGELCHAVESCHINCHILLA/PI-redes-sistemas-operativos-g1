// Copyright 2022 Ángel Chaves Chinchilla

/**
 * @file SumGoldbachCalculatorTest.cpp
 * @brief To test the model used to calculate goldbach sums, define TESTGOLDBACH
 * in Makefile
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright Ángel Chaves Chinchilla 2022
 * 
 */

#include "SumGoldbachCalculator.hpp"

#ifdef TESTGOLDBACH

#include <iostream>
#include <vector>

void readNumbers(std::istream& input, std::vector<int_t>& numbers);

int main() {
  SumGoldbachCalculator goldbach;

  // std::vector<int_t> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int_t> numbers;
  readNumbers(std::cin, numbers);

  goldbach.run(numbers);

  // goldbach.printGoldbachSums(std::cout);
  goldbach.printGoldbachSums(std::cout);
}

void readNumbers(std::istream& input, std::vector<int_t>& numbers) {
  int_t number = 0;

  while (input >> number) {
    numbers.push_back(number);
  }
}

#endif  // TESTGOLDBACH
