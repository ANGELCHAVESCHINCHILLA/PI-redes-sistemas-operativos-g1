// Copyright 2022 Ángel Chaves Chinchilla

#ifndef NUM_INFO_HPP
#define NUM_INFO_HPP

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "common.hpp"
#include "GoldbachResults.hpp"

/**
 * @brief Stores the information about a number (private data):
 * 1. The index of the numbers in a vector of numbers
 * 2. A pointer to the GoldbachResults class (shared data) that has that vector.
 * 
 */
struct NumInfo {
 private:
  /**
  * @brief the position of the number in the numbers field of GoldbachResults
  * class
  * 
  */
  size_t index;

  /**
   * @brief Pointer to the shared data with the numbers vector and other
   * attributes
   * 
   */
  GoldbachResults* goldbachResults;

 public:
  // Debe aceptar copias ya que el método consume recibe lo que consume por
  // copia
  DECLARE_RULE4(NumInfo, default);
  // Both classes need to access to the attributes
  friend class SumGoldbachCalculator;
  friend class Packer;

  /**
   * @brief Default Constructor: Construct a new Num Info object
   * 
   * @param index position of the number in the numbers field of goldbachResults
   * @param goldbachResults pointer to the "shared data" GoldbachResults
   */
  explicit NumInfo(size_t index = 0
    , GoldbachResults* goldbachResults = nullptr);

  /**
   * @brief If `this` and `other` parameters has the same attributes return
   * true.
   * 
   * @param other the right parameter of operator==
   * @return true If this and other parameters has the same attributes
   * @return false another case
   */
  bool operator==(const NumInfo& other) const;
};

#endif  // NUM_INFO_HPP
