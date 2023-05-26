#pragma once

#include "fs.hpp"

class Authenticator {
 private:
  /// @brief FileSystem to access authentication method.
  FS fs;

 public:
  /// @brief Default Constructor
  Authenticator();
  /// @brief Default Destructor
  ~Authenticator();
}; // end class Authenticator
