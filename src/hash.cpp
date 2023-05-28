//

#include "hash.hpp"

#include <math.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <time.h>

#include <iomanip>
#include <iostream>
#include <sstream>

const std::string Hash::MAP =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Hash::getHash(const std::string& input, size_t length,
    const std::string& salt, const std::string& pepper) {
  std::string copy = input + salt + pepper;

  SHA256_CTX sha_256;

  unsigned char hash[SHA256_DIGEST_LENGTH];

  SHA256_Init(&sha_256);
  SHA256_Update(&sha_256, copy.c_str(), copy.length());
  SHA256_Final(hash, &sha_256);

  std::stringstream ss;

  for (size_t index = 0; index < SHA256_DIGEST_LENGTH; index++) {
    ss << std::hex << std::setfill('0') << std::setw(2)
       << static_cast<int>(hash[index]);
  }

  return ss.str().substr(0, length);
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
