//

#ifndef FS_MENU_HPP_
#define FS_MENU_HPP_

#include <functional>
#include <string>

#include "../fs.hpp"
#include "../authenticator.hpp"

class FSMenu {
 private:
  static const std::string TEXT;

  static FSMenu* instance;

  FS fs;

	Authenticator authenticator;

  FSMenu();

  ~FSMenu() = default;

  // Copy Constructor
  FSMenu(const FSMenu& other) = delete;

  // Copy Assignment Operator
  FSMenu& operator=(const FSMenu& other) = delete;

  // Move Constructor
  FSMenu(FSMenu&& other) = delete;

  // Move Assignment Operator
  FSMenu& operator=(FSMenu&& other) = delete;

 public:
  static FSMenu* getInstance();

  void start();

 private:
  void addUser();

  void authenticateUser();

  void readFromFile(const std::string& source_file_name);

  void writeToFile(const std::string& source_file_name);

  void writeString(const std::string& file, const std::string& string);

  static int readInteger(const std::string& message,
      const std::string& error_message, std::function<bool(int)> predicate);

  static std::string readString(const std::string& message,
      const std::string& error_message,
      std::function<bool(std::string&)> predicate);
};

#endif  // FS_MENU_HPP_
