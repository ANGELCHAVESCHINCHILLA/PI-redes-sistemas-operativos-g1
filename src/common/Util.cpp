// Copyright 2023 Ángel Chaves Chinchilla

#include "Util.hpp"

void Util::padLeft(std::string& string, size_t length, char pad) {
  while (string.size() < length) {
    string.insert(0, 1, pad);
  }
}

void Util::trimLeft(std::string& string) {
  while (string[0] == ' ') {
    string.erase(0, 1);
  }
}
