// Copyright 2022 Ángel Chaves Chinchilla

#ifndef PACKER_HPP
#define PACKER_HPP

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "common.hpp"
#include "Assembler.hpp"
#include "NumInfo.hpp"

/**
 * @brief This object is in charge of waiting until all the `NumInfo` objects
 * that are of the same *request* have arrived. This is achieved by means of a
 * decrement to the counter of numbers that have the shared data. When this
 * reaches 0 it means that all the `NumInfo` of given *request* are ready to be
 * packed together. In reality though, the packaging is already given as the
 * `GoldbachResults` shared data object itself, so it produces said object in a
 * queue.
 * 
 */
class Packer : public Assembler<NumInfo, GoldbachResults*> {
 public:
  DISABLE_COPY(Packer);
  /// @brief Default constructor
  Packer() = default;

  /// Default Destructor
  ~Packer() = default;

  // Override from Thread
  int run() override;

  /// @brief override from Consume class, while there are NumInfo to consume
  /// Note: is not necesary override the produce method
  void consume(NumInfo data) override;

  /// @brief Pushes stop condition to consuming queue
  void pushStopCondition();
};

#endif  // PACKER_HPP
