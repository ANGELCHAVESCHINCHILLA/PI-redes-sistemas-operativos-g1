//

#ifndef HASH_HPP_
#define HASH_HPP_

#include <string>

/**
 * @brief Class with functions to generate hashes.
 *
 */
class Hash {
 public:
  static const std::string MAP;

  /**
   * @brief Generates a hash string from an input.
   *
   * @param input The input.
   * @param length The length of the hash.
   * @param salt An optional salt.
   * @param pepper An optional pepper.
   * @return std::string
   */
  static std::string getHash(const std::string& input, size_t length,
      const std::string& salt = std::string(),
      const std::string& pepper = std::string());

  /**
   * @brief Generates a random string with characters in base 64.
   *
   * @param length The length of the random string.
   * @return std::string The random string.
   */
  static std::string getSalt(size_t length);
};

#endif  // HASH_HPP_
