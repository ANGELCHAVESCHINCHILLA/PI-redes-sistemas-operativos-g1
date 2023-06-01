//
// Created by daviddev on 31/05/23.
//

#include "FileSystemAPI.hpp"

#include <fstream>
#include <iostream>

#include "../common/Util.hpp"
#include "../hash.hpp"


FileSystemAPI::FileSystemAPI() : authenticator(&this->fs) {
  //
  this->readFromFile(this->users_file);
}


bool FileSystemAPI::addUser(std::string username, std::string hashed_password, int role) {

  if (username.length() > USERNAME_LENGTH) {
    return false;
  }

  Util::padLeft(username, 10);

  this->writeString(users_file, username);
  this->writeString(users_file, hashed_password);
  this->writeString(users_file, std::to_string(role));

  this->writeToFile("usuarios.dat");

}

bool FileSystemAPI::authenticateUser(std::string username, std::string hash) {

  if (username.length() > USERNAME_LENGTH) {
    return false;
  }
  // debug lines TODO(ANY): remove this after debugging
  int error =  this->authenticator.authPass(users_file, username, hash);
  switch (error) {
    case Error::OK: {
      std::cout << "Contraseña correcta.\n";
      break;
    }

    case Error::INVALID_PASSWORD: {
      std::cout << "Contraseña incorrecta.\n";
      break;
    }

    case Error::USER_NOT_FOUND: {
      std::cout << "Usuario no encontrado.\n";
      break;
    }

    default: {
      break;
    }
  }
  if (error == Error::OK) {
    return true;
  } else {
    return false;
  }
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

void FileSystemAPI::writeString(const std::string& file, const std::string& string) {
  for (size_t index = 0; index < string.length(); index++) {
    this->fs.append(file, string.at(index));
  }
}

int FileSystemAPI::readInteger(const std::string& message,
    const std::string& error_message, std::function<bool(int)> predicate) {
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
    std::function<bool(std::string&)> predicate) {
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