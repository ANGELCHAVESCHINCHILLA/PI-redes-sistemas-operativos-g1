//

#include "hash.hpp"

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

const std::string Hash::MAP =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t Hash::getHash(const std::string& input) {
  size_t hash = HASH_PRIME_NUMBER;

  for (size_t index = 0; index < input.size(); index++) {
    hash = ((hash << 5) + hash) + input.at(index);
  }

  return hash;
}

std::string Hash::getSalt(size_t length) {
  std::string salt;

  ::srand(::time(NULL));

  for (size_t index = 0; index < length; index++) {
    int random_number = ::rand() % Hash::MAP.size();

    salt += Hash::MAP[random_number];
  }

  return salt;
}

std::string Hash::getString(const std::string& input, const std::string& salt,
  const std::string& pepper) {
  std::string new_input = input + salt + pepper;

  size_t hash = Hash::getHash(new_input);

  return Hash::toBase64(hash);
}

std::string Hash::toBase64(size_t number) {
  std::string output;

  while (number > 0) {
    size_t remainder = number % 64;

    char character = Hash::MAP[remainder];

    output = character + output;

    number /= 64;
  }

  return output;
}
