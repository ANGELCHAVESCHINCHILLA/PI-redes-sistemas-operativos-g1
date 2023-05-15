//

#ifndef HASH_HPP_
#define HASH_HPP_

#include <string>

#define HASH_LENGTH 15

#define HASH_PRIME_NUMBER 31

/**
 * @brief Class with functions to generate hashes.
 *
 */
class Hash {
 public:
  static const std::string MAP;

  /**
   * @brief Generates an integer from a string.
   *
   * @param input The string input.
   * @return size_t
   */
  static size_t getHash(const std::string& input);

  /**
   * @brief Generates a random string with characters in base 64.
   *
   * @param length The length of the random string.
   * @return std::string The random string.
   */
  static std::string getSalt(size_t length);

  /**
   * @brief Generates a hash string from an input. Usage: @code{.cpp}
   * Hash::getString("Hello!", Hash::getSalt(64), "Pepper!") @endcode
   *
   *
   * @param input The string input.
   * @param salt An optional salt.
   * @param pepper An optional pepper.
   * @return std::string The hash.
   */
  static std::string getString(const std::string& input,
      const std::string& salt, const std::string& pepper);

  /**
   * @brief Returns the base 64 string from an integer.
   *
   * @param number The integer.
   * @return std::string The base 64 string.
   */
  static std::string toBase64(size_t number);
};

#endif  // HASH_HPP_
