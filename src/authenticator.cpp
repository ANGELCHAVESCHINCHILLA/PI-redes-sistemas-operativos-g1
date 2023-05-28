#include <iostream>

#include "authenticator.hpp"
#include "hash.hpp"
#include "./common/Util.hpp"

const std::string Authenticator::PEPPER = "Universidad de Costa Rica";

// Authenticator::Authenticator() {
//     this->fs = new FS();
// }

Authenticator::Authenticator(FS* fs) {
    this->fs = fs;
}

Authenticator::~Authenticator() {
    // delete this->fs;
}

int Authenticator::authPass(const std::string& usersFile
    , const std::string& username, const std::string& password) {
  int error = Error::OK;

  bool found_user = false;

  size_t user_offset = 0;

  const size_t user_bytes = 41;

  while (!found_user &&
        user_offset < static_cast<size_t>(this->fs->getFileSize(usersFile))) {
    char* address = this->fs->readAddress(usersFile, user_offset);

    std::string info(address, address + user_bytes);
    // info username is the username stored in FileSystem
    std::string info_username = info.substr(0, 10);
    Util::trimLeft(info_username);

    // If the user name was found in FS then
    if (username == info_username) {
      // This ise the hash stored in file system for the user
      std::string info_hashed_password = info.substr(10, 15);
      Util::trimLeft(info_hashed_password);
      // This is the salt store in the file system for the user
      std::string info_salt = info.substr(25, 15);

      // Calculate the hash with the input password and the salt stored in FS
      std::string hashed_password =
          Hash::getString(password, info_salt, Authenticator::PEPPER);

      if (hashed_password == info_hashed_password) {
        error = Error::OK;
      } else {
        error = Error::INVALID_PASSWORD;
      }

      found_user = true;
    }

    user_offset += user_bytes;
  }

  if (!found_user) {
    error = Error::USER_NOT_FOUND;
  }
  return error;
}


