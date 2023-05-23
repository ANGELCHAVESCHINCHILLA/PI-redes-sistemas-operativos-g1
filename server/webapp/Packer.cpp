// Copyright 2022 Ángel Chaves Chinchilla

#include "Packer.hpp"

int Packer::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void Packer::consume(NumInfo data) {
  GoldbachResults* goldbachResults = data.goldbachResults;
  assert(goldbachResults->pendingNumCount > 0);
  // decrease the num of pendingNumCount, just the packet can modify it
  goldbachResults->pendingNumCount -= 1;
  // if all the numbers of a specific shared data were proccessed
  if (goldbachResults->pendingNumCount == 0) {
    // enqueue the goldbachResults that already have all the sums results
    this->produce(goldbachResults);
  }
}

void Packer::pushStopCondition() {
  this->consumingQueue->push(NumInfo());
}
