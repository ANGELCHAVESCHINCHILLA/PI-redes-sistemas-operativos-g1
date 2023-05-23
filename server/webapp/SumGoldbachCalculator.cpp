// Copyright 2022 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#include "SumGoldbachCalculator.hpp"

#include <algorithm>

SumGoldbachCalculator::SumGoldbachCalculator() = default;

int SumGoldbachCalculator::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void SumGoldbachCalculator::consume(NumInfo data) {
  this->calculateGolbachSumsVs2(data);
}

void SumGoldbachCalculator::pushStopCondition() {
  this->consumingQueue->push(NumInfo());
}



bool SumGoldbachCalculator::isPrime(const int_t number) {
  // The numbers 2 and 3 are prime
  if (number == 2 || number == 3) {
    return true;
  }

  // The numbers divisible by 2 or 3 are not prime
  if (number <= 1 || number % 2 == 0 || number % 3 == 0) {
    return false;
  }

  // Start with 5 and then move every 6 numbers
  for (int_t divisor = 5; divisor * divisor <= number; divisor += 6) {
    // If the number has a divisor it is not prime
    if (number % divisor == 0 || number % (divisor + 2) == 0) {
      return false;
    }
  }

  return true;
}


void SumGoldbachCalculator::calculateGolbachSumsVs2(NumInfo& numInfo) {
  GoldbachResults* goldbachResults = numInfo.goldbachResults;

  int_t number = std::abs(goldbachResults->numbers[numInfo.index]);

  if (number > 5 || number == 4) {
    if (number % 2 == 0) {
      // If the number is even
      calculateGoldbachSumsEvenVs2(number
                                , goldbachResults->counts[numInfo.index],
                                goldbachResults->sums[numInfo.index]);
    } else {
      // If the number is odd
      calculateGoldbachSumsOddVs2(number
                                , goldbachResults->counts[numInfo.index],
                                goldbachResults->sums[numInfo.index]);
    }
  }

  this->produce(numInfo);
}



void SumGoldbachCalculator::calculateGoldbachSumsEvenVs2(const int_t number,
                                                      int_t& count,
                                                      std::vector<int_t>& sum) {
  int_t possiblePrime1 = 2;

  while (possiblePrime1 < number - 2) {
    if (this->isPrime(possiblePrime1)) {
      int_t difference = number - possiblePrime1;

      if (difference >= possiblePrime1) {
        // Verify if the difference is a prime number.
        if (this->isPrime(difference)) {
          // Add the prime numbers to the sum array of the number
          sum.push_back(possiblePrime1);

          sum.push_back(difference);

          // Increment the sums count of the number
          count++;
        }
      }
    }
    possiblePrime1 = possiblePrime1 == 2 ? possiblePrime1 + 1
      : possiblePrime1 + 2;
  }
}


void SumGoldbachCalculator::calculateGoldbachSumsOddVs2(const int_t number,
                                                     int_t& count,
                                                     std::vector<int_t>& sum) {
  int_t possiblePrime1 = 2;

  while (possiblePrime1 < number - 2) {
    if (this->isPrime(possiblePrime1)) {
      int_t possiblePrime2 = possiblePrime1;

      while (possiblePrime2 < number - possiblePrime1 - 2) {
        if (this->isPrime(possiblePrime2)) {
          int_t difference = number - possiblePrime1 - possiblePrime2;
          if (difference >= possiblePrime2) {
            // Verify if the difference is a prime number.
            if (this->isPrime(difference)) {
              // Add the prime numbers the the sum array of the number
              sum.push_back(possiblePrime1);

              sum.push_back(possiblePrime2);

              sum.push_back(difference);
              // Increment the sums count of the number
              count++;
            }
          }
        }
        possiblePrime2 = possiblePrime2 == 2 ? possiblePrime2 + 1
          : possiblePrime2 + 2;
      }
    }
    possiblePrime1 = possiblePrime1 == 2 ? possiblePrime1 + 1
      : possiblePrime1 + 2;
  }
}

/* The next methods are for the version of a non concurrent calculator. Are not
  used in the current version but could be useful to optimize the said version.
  */

SumGoldbachCalculator::SumGoldbachCalculator(std::vector<int_t>& numbers)
  : numbers(numbers) { }

void SumGoldbachCalculator::run1() {
  // Calculates the max number
  this->maxNumber = this->calculateMaxNumber();

  // Adds the prime numbers less than the max number
  this->calculatePrimeNumbers();

  // Calculates the Goldbach sum counts and the Goldbach sums of the numbers
  this->calculateGolbachSums();
}

int_t SumGoldbachCalculator::calculateMaxNumber() const {
  // Return 0 if there are no numbers
  if (this->numbers.size() == 0) {
    return 0;
  }

  // Iterate the numbers and find the max number
  int_t number1 = std::abs(this->numbers[0]);

  for (int_t number2 : this->numbers) {
    number2 = std::abs(number2);

    if (number2 > number1) {
      number1 = number2;
    }
  }

  return number1;
}

void SumGoldbachCalculator::calculatePrimeNumbers() {
  // Add the 2
  if (this->maxNumber > 2) {
    primeNumbers.push_back(2);
  }

  // Move every two numbers and verify if it is prime
  for (int_t number = 3; number < this->maxNumber - 2; number += 2) {
    if (this->isPrime(number)) {
      this->primeNumbers.push_back(number);
    }
  }
}

void SumGoldbachCalculator::calculateGolbachSums() {
  // Initialize the counts array and the sums array
  this->counts.resize(this->numbers.size());

  this->sums.resize(this->numbers.size());

  // Iterate the numbers and calculate the Goldbach sums
  for (size_t index = 0; index < this->numbers.size(); index++) {
    int_t number = std::abs(this->numbers[index]);

    if (number > 5 || number == 4) {
      if (number % 2 == 0) {
        // If the number is even
        calculateGoldbachSumsEven(number, this->counts[index],
                                  this->sums[index]);
      } else {
        // If the number is odd
        calculateGoldbachSumsOdd(number, this->counts[index],
                                 this->sums[index]);
      }
    }
  }
}

void SumGoldbachCalculator::calculateGoldbachSumsEven(const int_t number,
                                                      int_t& count,
                                                      std::vector<int_t>& sum) {
  size_t index1 = 0;

  int_t primeNumber2 = this->primeNumbers[index1];

  while (index1 < this->primeNumbers.size() && primeNumber2 < number) {
    int_t difference = number - primeNumber2;

    // Verify if the difference is a prime number with a binary search
    if (difference >= primeNumber2 &&
        std::binary_search(this->primeNumbers.begin(), this->primeNumbers.end(),
                           difference)) {
      // Add the prime numbers the the sum array of the number
      sum.push_back(primeNumber2);

      sum.push_back(difference);

      // Increment the sums count of the number
      count++;
    }

    index1++;

    if (index1 < this->primeNumbers.size()) {
      primeNumber2 = primeNumbers[index1];
    }
  }
}

void SumGoldbachCalculator::calculateGoldbachSumsOdd(const int_t number,
                                                     int_t& count,
                                                     std::vector<int_t>& sum) {
  size_t index1 = 0;

  int_t primeNumber1 = this->primeNumbers[index1];

  while (index1 < this->primeNumbers.size() && primeNumber1 < number) {
    size_t index2 = index1;

    int_t prime_number_2 = this->primeNumbers[index2];

    while (index2 < this->primeNumbers.size() && prime_number_2 < number) {
      int_t difference = number - primeNumber1 - prime_number_2;

      // Verify if the difference is a prime number with a binary search
      if (difference >= primeNumber1 && difference >= prime_number_2 &&
          std::binary_search(this->primeNumbers.begin(),
                             this->primeNumbers.end(), difference)) {
        // Add the prime numbers the the sum array of the number
        sum.push_back(primeNumber1);

        sum.push_back(prime_number_2);

        sum.push_back(difference);

        // Increment the sums count of the number
        count++;
      }

      index2++;

      if (index2 < this->primeNumbers.size()) {
        prime_number_2 = this->primeNumbers[index2];
      }
    }

    index1++;

    if (index1 < this->primeNumbers.size()) {
      primeNumber1 = this->primeNumbers[index1];
    }
  }
}
