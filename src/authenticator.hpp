#pragma once

#include "fs.hpp"
#include "error.hpp"

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
  static const std::string PEPPER;
  /// @brief Default Constructor
  // Authenticator();
  /// @brief Default Destructor
  ~Authenticator();
  /// @brief Constructs an auth using a predefined fs
  /// @param fs predefined fs
  Authenticator(FS* fs);
  /// @brief Authenticates a user by their username and password.
  /// @param userName user's username to be identificate
  /// @param password user's password
  /// @param usersFile the filename of the users file
  /// @return error code:
  /// OK if auth
  /// INVALID_PASSWORD if the password is invalid
  /// USER_NOT_FOUND -2 if the users was not found.
  int authUser(const std::string& usersFile, const std::string& userFame,
    const std::string& password);
};  // end class Authenticator
