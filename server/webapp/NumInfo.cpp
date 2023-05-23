// Copyright 2022 Ángel Chaves Chinchilla

#include "NumInfo.hpp"

NumInfo::NumInfo(const size_t index, GoldbachResults* goldbachResults)
  : index(index)
  , goldbachResults(goldbachResults) { }

bool NumInfo::operator==(const NumInfo& other) const {
  // if both has the same "shared data" and the same index
  return this->goldbachResults == other.goldbachResults
    && this->index == other.index;
}
