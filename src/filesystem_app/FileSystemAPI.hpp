#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_FILESYSTEMAPI_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_FILESYSTEMAPI_H
#include <functional>
#include <string>

#include "../../././src/authenticator.hpp"



class FileSystemAPI {
 public:
  /// Default constructor
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
      const std::string& error_message, const std::function<bool(int)>& predicate);

  static std::string readString(const std::string& message,
      const std::string& error_message,
      const std::function<bool(std::string&)>& predicate);

 public:
  bool addUser(std::string username, const std::string& hashkey, int role);

  bool authenticateUser(const std::string& username, const std::string& hashkey);

  int getUserType(const std::string& username);

  std::string viewFS();

  bool userExists(const std::string& username);

  std::string getUserSalt(const std::string& username);
};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_FILESYSTEMAPI_H
