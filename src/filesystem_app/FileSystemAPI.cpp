//
// Created by David Cerdas Alvarado on 31/05/23.
//

#include "FileSystemAPI.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../common/Log.hpp"
#include "../common/Util.hpp"

#define USERNAME_LENGTH 10
#define HASH_LENGTH 15
#define SALT_LENGTH 15
#define USER_BYTES 41

FileSystemAPI::FileSystemAPI() : authenticator(&this->fs) {
  this->readFromFile(this->users_file);
}

bool FileSystemAPI::addUser(std::string username,
    const std::string& hashed_password, const std::string& salt, int role) {
  if (username.length() > USERNAME_LENGTH) {
    Log::getInstance().write(
        Log::MessageType::ERROR, "FileSystemAPI", "Invalid username length.");
    return false;
  }

  if (hashed_password.length() > HASH_LENGTH) {
    Log::getInstance().write(
        Log::MessageType::ERROR, "FileSystemAPI", "Invalid hash length.");
    return false;
  }

  if (salt.length() > SALT_LENGTH) {
    Log::getInstance().write(
        Log::MessageType::ERROR, "FileSystemAPI", "Invalid salt length.");
    return false;
  }

  Util::padLeft(username, 10);

  this->writeString(users_file, username);
  this->writeString(users_file, hashed_password);
  this->writeString(users_file, salt);
  this->writeString(users_file, std::to_string(role));

  this->writeToFile("usuarios.dat");

  return true;
}

bool FileSystemAPI::removeUser(std::string username) {
  //
}

bool FileSystemAPI::editUser(std::string username, const std::string& hashkey,
    const std::string& salt, int role) {
  //
}

bool FileSystemAPI::authenticateUser(
    const std::string& username, const std::string& hash) {
  if (username.length() > USERNAME_LENGTH) {
    Log::getInstance().write(
        Log::ERROR, "ErrorUsername", "On auth user, username.length > 10");
    return false;
  }

  int error = this->authenticator.authPass(users_file, username, hash);

  return error == Error::OK;
}

void FileSystemAPI::readFromFile(const std::string& source_file_name) {
  int error = Error::OK;

  this->fs.create(source_file_name);

  std::ifstream source_file(source_file_name);

  if (source_file) {
    char character = '\0';

    while (source_file >> std::noskipws >> character && !error) {
      error = fs.append(source_file_name, character);
    }

    source_file.close();
  }
}

void FileSystemAPI::writeToFile(const std::string& source_file_name) {
  std::ofstream source_file(source_file_name);

  if (source_file) {
    char* address = this->fs.readAddress(source_file_name, 0);

    std::string info = address;

    source_file << info;
  }
}

void FileSystemAPI::writeString(
    const std::string& file, const std::string& string) {
  for (char index : string) {
    this->fs.append(file, index);
  }
}

int FileSystemAPI::readInteger(const std::string& message,
    const std::string& error_message,
    const std::function<bool(int)>& predicate) {
  int result;

  std::cout << message << std::endl;

  while (true) {
    if (std::cin >> result && predicate(result)) {
      break;
    } else {
      std::cout << error_message << "\n";
    }
  }

  return result;
}

std::string FileSystemAPI::readString(const std::string& message,
    const std::string& error_message,
    const std::function<bool(std::string&)>& predicate) {
  std::string result;

  std::cout << message << std::endl;

  while (true) {
    if (std::cin >> result && predicate(result)) {
      break;
    } else {
      std::cout << error_message << "\n";
    }
  }

  return result;
}

std::string FileSystemAPI::viewFS() {
  return this->fs.toString();
}

int FileSystemAPI::getUserType(const std::string& username) {
  char* address = this->getUserOffset(username);

  if (address == nullptr) {
    return -1;
  }

  std::string info(address, address + USER_BYTES);

  char charType = info[info.length() - 1];
  int type = charType - 48;

  return type;
}

char* FileSystemAPI::getUserOffset(const std::string& username) {
  size_t user_offset = 0;
  const size_t user_bytes = 41;

  while (user_offset <
         static_cast<size_t>(this->fs.getFileSize(this->users_file))) {
    char* address = this->fs.readAddress(this->users_file, user_offset);

    std::string info(address, address + user_bytes);

    std::string info_username = info.substr(0, USERNAME_LENGTH);

    Util::trimLeft(info_username);

    if (username == info_username) {
      return address;
    }

    user_offset += user_bytes;
  }

  return nullptr;
}

bool FileSystemAPI::userExists(const std::string& username) {
  return this->getUserOffset(username) != nullptr;
}

std::string FileSystemAPI::getUserSalt(const std::string& username) {
  char* address = this->getUserOffset(username);

  if (address == nullptr) {
    return "";
  }

  std::string info(address, address + USER_BYTES);

  info = info.substr(USERNAME_LENGTH);
  std::string info_hash = info.substr(0, HASH_LENGTH);
  info = info.substr(HASH_LENGTH);
  std::string info_salt = info.substr(0, SALT_LENGTH);

  return info_salt;
}
