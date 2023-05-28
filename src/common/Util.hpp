// Copyright 2023 Ángel Chaves Chinchilla

#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include "common.hpp"

/**
 * @brief Container class for utility methods
 * This code is not needed for real projects
 */
class Util {
  DISABLE_COPY(Util);
  /// Constructor
  Util() = delete;
  /// Destructor
  ~Util() = delete;

 public:
  static void padLeft(std::string& string, size_t length);

  static void trimLeft(std::string& string);
};

#endif  // UTIL_HPP
