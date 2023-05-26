#pragma once

#include "fs.hpp"
/**
 * @brief This class contributes to handling the authentication.
 * The idea is use this class using sockets communication or CLI.
 * 
 */
class Authenticator {
 private:
  /// @brief FileSystem to access authentication method.
  FS* fs;

 public:
  /// @brief Default Constructor
  Authenticator();
  /// @brief Default Destructor
  ~Authenticator();
  /// @brief Constructs an auth using a predefined fs
  /// @param fs predefined fs
  Authenticator(FS* fs);
  /// @brief Authenticates a user by their username and hashkey.
  /// @param userName user's username to be identificate
  /// @param hashKey user's hashkey
  /// @return true if auth. False otherwise.
  bool authUser(const std::string& username, const std::string& hashKey);
}; // end class Authenticator
