//

#include "authenticator.hpp"

#include <iostream>

#include "./common/Util.hpp"
#include "hash.hpp"

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

std::string Authenticator::getSalt(const std::string& usersFile,
    const std::string& username, const std::string& password) {
  
  std::string info_salt = "";

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
      // This is the salt store in the file system for the user
      info_salt = info.substr(25, 15);

      found_user = true;
    }

    user_offset += user_bytes;
  }
  return info_salt;
}

int Authenticator::authPass(const std::string& usersFile,
    const std::string& username, const std::string& hash) {
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

    // If the username was found in FS then
    if (username == info_username) {
      // This ise the hash stored in file system for the user
      std::string info_hashed_password = info.substr(10, 30);
      Util::trimLeft(info_hashed_password);

      if (hash == info_hashed_password) {
        error = Error::OK;
      } else {
        error = Error::INVALID_PASSWORD;
      }
      std::cout << "Hash: " + hash << std::endl;
      std::cout << "Hash: " + info_hashed_password << std::endl;
      found_user = true;
    }

    user_offset += user_bytes;
  }

  if (!found_user) {
    error = Error::USER_NOT_FOUND;
  }
  return error;
}
