#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_FILESYSTEMAPI_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_FILESYSTEMAPI_H
#include <functional>
#include <string>

#include "../../././src/authenticator.hpp"

#define USERNAME_LENGTH 10

class FileSystemAPI {
 public:
  FileSystemAPI();

 private:
  FS fs;
  Authenticator authenticator;
  /// Users data file. It going to have full users info
  /// data like username, hash and role
  const std::string users_file = "usuarios.dat";

  void readFromFile(const std::string& source_file_name);

  void writeToFile(const std::string& source_file_name);

  void writeString(const std::string& file, const std::string& string);

  static int readInteger(const std::string& message,
      const std::string& error_message, std::function<bool(int)> predicate);

  static std::string readString(const std::string& message,
      const std::string& error_message,
      std::function<bool(std::string&)> predicate);

 public:
  bool addUser(std::string username, std::string hashkey, int role);

  bool authenticateUser(std::string username, std::string hashkey);

  std::string viewFS();
};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_FILESYSTEMAPI_H
