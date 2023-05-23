// Copyright 2022 Ángel Chaves Chinchilla, Camilo Suarez Sandí

#ifndef DISPATCHER_GOLDBACH_HPP
#define DISPATCHER_GOLDBACH_HPP

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

#include "common.hpp"
#include "Consumer.hpp"
#include "NumInfo.hpp"

/**
 * @brief A consumer class that generate the HttpResponse to the peer. Consume
 * while there are GoldbachResults generated
 * 
 */
class DispatcherGoldbach : public Consumer<GoldbachResults*> {
 public:
  DISABLE_COPY(DispatcherGoldbach);
  /// @brief Default constructor
  DispatcherGoldbach() = default;

  /// Default Destructor
  ~DispatcherGoldbach() = default;

  /**
   * @brief override from Thread class, is the routine of the DispatcherGoldbach
   * thread
   * 
   * @return int EXIT_SUCCESS
   */
  int run() override;

  /// @brief override from Consume class, while there are NumInfo to consume
  /// Note: is not necesary override the produce method
  void consume(GoldbachResults* data) override;

  /**
   * @brief Send an HTML form to read the numbers or read the numbers from the
   * URL and calculate the Goldbach sums of the numbers.
   *
   * @param goldbachResults A object with the HTTP response as a field.
   * @return true If the request was successfully handled by this dispatcher.
   */
  bool serveSumGoldbach(GoldbachResults* goldbachResults);

  /**
   * @brief Reads a file and writes the text of the file to an output stream.
   *
   * @param os The output stream.
   * @param path The path of the file, relative to the project directory.
   */
  void readFile(std::ostream& os, std::string path);

  /**
   * @brief Writes the HTML text of the numbers and the Goldbach sums to the
   * output stream of the HTTP response.
   *
   * @param os The output stream of the HTTP response.
   * @param goldbachResults The object with the results of the goldbach sums.
   */
  void writeGoldbachSums(std::ostream& os
    , const GoldbachResults* goldbachResults);

  /**
   * @brief If the number is even then writes the HTML text of the sum of a
   * number.
   *
   * @param os The output stream of the HTTP response.
   * @param sum The sum of the number.
   */
  void writeGoldbachSumsEven(std::ostream& os, const std::vector<int_t>& sum);

  /**
   * @brief If the number is odd then writes the HTML text of the sum of a
   * number.
   *
   * @param os The output stream of the HTTP response.
   * @param sum The sum of the number.
   */
  void writeGoldbachSumsOdd(std::ostream& os, const std::vector<int_t>& sum);

  /// @brief Pushes stop condition to consuming queue
  void pushStopCondition();
};

#endif  // DISPATCHER_GOLDBACH_HPP
