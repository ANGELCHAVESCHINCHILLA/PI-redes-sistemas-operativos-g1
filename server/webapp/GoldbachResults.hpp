// Copyright 2022 Ángel Chaves Chinchilla

#ifndef GOLDBACH_RESULTS
#define GOLDBACH_RESULTS

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "HttpResponse.hpp"

#include "common.hpp"

typedef int64_t int_t;

/**
 * @brief The shared data of the SumGoldbachCalculators threads. Stores the
 * goldbach sums for a specific vector of numbers and also stores its
 * HttpResponse 
 * 
 */
struct GoldbachResults {
 private:
  /**
  * @brief numbers vector to calculate its goldbach sums
  * 
  */
  std::vector<int_t> numbers;

  /**
   * @brief Each element represents the amount of sums found for the number
   * in the position of said element in the numbers vector
   * 
   */
  std::vector<int_t> counts;

  /**
   * @brief vector of vectors to store the sums of Goldbach, each vector of sums
   * stores the addends of a specific number of numbers vector
   * 
   */
  std::vector<std::vector<int_t>> sums;

  /**
   * @brief Amount of pending numbers to be dequeue by the Packer
   * 
   */
  size_t pendingNumCount;

  /*
   * @brief An HTTP response for this specific attributes.
   * 
   */
  HttpResponse httpResponse;

 public:
  friend class SumGoldbachCalculator;
  friend class Packer;
  friend struct NumInfo;
  friend class DispatcherGoldbach;

  // abble copies
  DECLARE_RULE4(GoldbachResults, default);

  /**
   * @brief Construct a new Goldbach Results object
   * 
   * @param numbers Vector with the numbers to calculate the Goldbach sums.
   * @param httpResponse An HTTP response.
   */
  explicit GoldbachResults(std::vector<int_t>& numbers
    , HttpResponse& httpResponse);

  /**
   * @brief Default constructor
   * 
   */
  GoldbachResults();
  /**
   * @brief if the httpResponse field of this and of other are same then return
   * true
   * @details it is not used, but could be need it in another version of the
   * design of this project.
   * 
   * @param other right GoldbachResults of the operator
   * @return true if has the same httpResponse
   * @return false another case
   */
  bool operator==(const GoldbachResults& other) const;
};

#endif  // GOLDBACH_RESULTS
