//

#include "FSMenu.hpp"

#include <fstream>
#include <iostream>

#include "../hash.hpp"

const std::string FSMenu::TEXT =
    "-------------\n"
    " File System \n"
    "-------------\n"
    "Opciones:\n"
    "[1]: Agregar usuario.\n"
    "[2]: Autenticar usuario.\n"
    "[3]: Actualizar usuarios.\n"
    "[4]: Ver contenido.\n"
    "[0]: Salir del programa.\n";

FSMenu* FSMenu::instance = nullptr;

const std::string FSMenu::PEPPER = "Universidad de Costa Rica";

FSMenu::FSMenu() {
  //
  this->fs.create("usuarios.dat");
}

FSMenu* FSMenu::getInstance() {
  if (FSMenu::instance == nullptr) {
    FSMenu::instance = new FSMenu();
  }

  return FSMenu::instance;
}

void FSMenu::start() {
  bool run = true;

  while (run) {
    std::cout << FSMenu::TEXT;

    int option = -1;

    std::cin >> option;

    switch (option) {
      case 1: {
        // [1]: Agregar usuario.
        this->addUser();
        break;
      }

      case 2: {
        // [2]: Autenticar usuario.
        this->authenticateUser();
        break;
      }

      case 3: {
        // [3]: Actualizar usuarios.
        this->updateUsersFile();
        break;
      }

      case 4: {
        // [4]: Ver contenido.
        std::cout << this->fs.toString() << "\n";
        break;
      }

      case 0: {
        // [0]: Salir del programa.
        run = false;
        break;
      }

      default: {
        break;
      }
    }

    std::cout << "\n";
  }
}

void FSMenu::addUser() {
  const std::string users_file = "usuarios.dat";

  std::string username = FSMenu::readString(
      "Escriba el nombre de usuario de máximo 10 caracteres: ",
      "Por favor escriba un nombre de usuario de máximo 10 caracteres.",
      [](std::string& string) { return string.length() <= 10; });

  FSMenu::padLeft(username, 10);

  std::string password = FSMenu::readString("Escribe la contraseña: ", "",
      [](std::string& string) { return string.length() > 0; });

  int type = FSMenu::readInteger("Escriba el tipo de usuario del 0 al 5",
      "Por favor escriba un tipo de usuario del 0 al 5.",
      [](int integer) { return integer >= 0 && integer <= 5; });

  std::string salt = Hash::getSalt(15);

  std::string hashed_password = Hash::getString(password, salt, FSMenu::PEPPER);
  FSMenu::padLeft(hashed_password, 15);

  this->writeString(users_file, username);
  this->writeString(users_file, hashed_password);
  this->writeString(users_file, salt);
  this->writeString(users_file, std::to_string(type));
}

void FSMenu::authenticateUser() {
  const std::string users_file = "usuarios.dat";
  const size_t user_bytes = 41;

  std::string username = FSMenu::readString("Escriba su nombre de usuario: ",
      "Por favor escriba un nombre de usuario de máximo 10 caracteres.",
      [](std::string& string) { return string.length() <= 10; });

  std::string password = FSMenu::readString("Escribe su contraseña: ", "",
      [](std::string& string) { return string.length() > 0; });

  bool found_user = false;

  size_t user_offset = 0;

  while (!found_user && user_offset < this->fs.getFileSize(users_file)) {
    char* address = this->fs.readAddress(users_file, user_offset);

    std::string info(address, address + user_bytes);

    std::string info_username = info.substr(0, 10);
    FSMenu::trimLeft(info_username);

    if (username == info_username) {
      std::string info_hashed_password = info.substr(10, 15);
      FSMenu::trimLeft(info_hashed_password);

      std::string info_salt = info.substr(25, 15);

      std::string hashed_password =
          Hash::getString(password, info_salt, FSMenu::PEPPER);

      if (hashed_password == info_hashed_password) {
        std::cout << "Contraseña correcta.\n";
      } else {
        std::cout << "Contraseña incorrecta.\n";
      }

      found_user = true;
    }

    user_offset += user_bytes;
  }

  if (!found_user) {
    std::cout << "Usuario no encontrado.\n";
  }
}

void FSMenu::updateUsersFile() {
  //
}

void FSMenu::writeString(const std::string& file, const std::string& string) {
  for (size_t index = 0; index < string.length(); index++) {
    this->fs.append(file, string.at(index));
  }
}

int FSMenu::readInteger(const std::string& message,
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

std::string FSMenu::readString(const std::string& message,
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

void FSMenu::padLeft(std::string& string, size_t length) {
  while (string.size() < length) {
    string.insert(0, 1, ' ');
  }
}

void FSMenu::trimLeft(std::string& string) {
  while (string[0] == ' ') {
    string.erase(0, 1);
  }
}
