// Copyright 2022 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef SUM_GOLDBACH_CALCULATOR_HPP_
#define SUM_GOLDBACH_CALCULATOR_HPP_

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "common.hpp"
#include "Assembler.hpp"
#include "NumInfo.hpp"

/**
 * @brief A model class that consumes and produces NumInfo objects. Computes the
 * goldbach sums of the number that the `NumInfo` object's index points to in
 * the array of numbers in the `GoldbachResults` data share. In addition, it
 * increments the sum counter for each number and places the sums in the sum
 * vector located in the shared data.
 */
class SumGoldbachCalculator : Assembler<NumInfo, NumInfo> {
 public:
  DISABLE_COPY(SumGoldbachCalculator);
  /// @brief Default constructor
  SumGoldbachCalculator();

  /**
   * @brief Destructor.
   *
   */
  ~SumGoldbachCalculator() = default;

 public:
  /**
   * @brief The thread routine, consume forever from the consuming queue
   * 
   * @return int 
   */
  int run() override;

  /**
   * @brief override from Consumer class, calculate the sums for the number
   * filed stored in data and enqueue the data in the producing queue.
   * 
   * @param data the Nun info object to consumes.
   */
  void consume(NumInfo data) override;

  /**
   * @brief Pushes stop condition to consuming queue
   * 
   */
  void pushStopCondition();

  /**
   * @brief Returns true a number is prime.
   *
   * @param number The number.
   * @return true If a number is prime.
   */
  static bool isPrime(const int_t number);

  /**
   * @brief Calculates the goldbach sums of the number field of numInfo and
   * store them in the sums filed, also increase the count of sums for that
   * number.
   * 
   * @param numInfo 
   */
  void calculateGolbachSumsVs2(NumInfo& numInfo);


  /**
   * @brief Calculates the Goldbach sum counts and the Goldbach sums of the
   * numbers for an even number. This version don't use a prime numbers array.
   *
   * @param number The number.
   * @param count The sums count for this number.
   * @param sum The sum array for this number.
   */
  void calculateGoldbachSumsEvenVs2(const int_t number, int_t& count,
                                 std::vector<int_t>& sum);


  /**
   * @brief Calculates the Goldbach sum counts and the Goldbach sums of the
   * numbers for an odd number. This version don't use a prime numbers array.
   * @param number The number.
   * @param count The sums count for this number.
   * @param sum The sum array for this number.
   */
  void calculateGoldbachSumsOddVs2(const int_t number, int_t& count,
                                std::vector<int_t>& sum);

  /* The next attributes and methods are for the version of a non concurrent
  calculator. Are not used in the current version but could be useful to
  optimize the said version.
  */
  friend class SumGoldbachWebApp;

 protected:
  /**
   * @brief An array with the numbers to calculate the Goldbach sums.
   *
   */
  std::vector<int_t> numbers;

  /**
   * @brief The max number.
   *
   */
  int_t maxNumber;

  /**
   * @brief An array with the prime numbers less than the max number.
   *
   */
  std::vector<int_t> primeNumbers;

  /**
   * @brief An array that stores the Goldbach sum counts of each number.
   *
   */
  std::vector<int_t> counts;

  /**
   * @brief An array that stores the Goldbach sums of each number.
   *
   */
  std::vector<std::vector<int_t>> sums;

 public:
  /**
   * @brief Default constructor.
   * 
   * @param numbers An array with the numbers.
   */
  explicit SumGoldbachCalculator(std::vector<int_t>& numbers);

  /**
   * @brief Calculates the Goldbach sum counts and the Goldbach sums of the
   * numbers for an odd number. This version use a prime numbers array.
   * @param number The number.
   * @param count The sums count for this number.
   * @param sum The sum array for this number.
   */
  void calculateGoldbachSumsOdd(const int_t number, int_t& count,
                                std::vector<int_t>& sum);

  /**
   * @brief Calculates the Goldbach sum counts and the Goldbach sums of the
   * numbers for an even number. This version use a prime numbers array.
   *
   * @param number The number.
   * @param count The sums count for this number.
   * @param sum The sum array for this number.
   */
  void calculateGoldbachSumsEven(const int_t number, int_t& count,
                                 std::vector<int_t>& sum);

  /**
   * @brief Calculates the Goldbach sum counts and the Goldbach sums of the
   * numbers
   *
   */
  void calculateGolbachSums();

  /**
   * @brief Calculates the Goldbach sums of the numbers.
   */
  void run1();

  /**
   * @brief Calculates the max number, ignoring the sign.
   *
   * @return int_t The max number.
   */
  int_t calculateMaxNumber() const;

  /**
   * @brief Calculates the prime numbers less than the max number.
   *
   */
  void calculatePrimeNumbers();
};

#endif  // SUM_GOLDBACH_CALCULATOR_HPP_
