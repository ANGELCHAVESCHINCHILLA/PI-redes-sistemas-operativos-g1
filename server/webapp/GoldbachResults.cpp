// Copyright 2022 Ángel Chaves Chinchilla

#include "GoldbachResults.hpp"

GoldbachResults::GoldbachResults()
  : httpResponse(Socket()) { }

GoldbachResults::GoldbachResults(std::vector<int_t>& numbers
    , HttpResponse& httpResponse)
  : numbers(numbers)
  , counts(numbers.size())
  , sums(numbers.size())
  , pendingNumCount(numbers.size())
  , httpResponse(httpResponse) { }

bool GoldbachResults::operator==(const GoldbachResults& other) const {
  return this->httpResponse == other.httpResponse;
}

