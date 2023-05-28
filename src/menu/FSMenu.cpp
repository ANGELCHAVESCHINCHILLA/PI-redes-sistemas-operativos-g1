//

#include "FSMenu.hpp"

#include <fstream>
#include <iostream>

#include "../error.hpp"
#include "../hash.hpp"
#include "../common/Util.hpp"

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


FSMenu::FSMenu() 
  : authenticator(&this->fs) {
  //

  this->readFromFile("usuarios.dat");
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
        this->writeToFile("usuarios.dat");
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

  Util::padLeft(username, 10);

  std::string password = FSMenu::readString("Escribe la contraseña: ", "",
      [](std::string& string) { return string.length() > 0; });

  int type = FSMenu::readInteger("Escriba el tipo de usuario del 0 al 5",
      "Por favor escriba un tipo de usuario del 0 al 5.",
      [](int integer) { return integer >= 0 && integer <= 5; });

  std::string salt = Hash::getSalt(15);

  std::string hashed_password = Hash::getString(password, salt
                                , Authenticator::PEPPER);
  Util::padLeft(hashed_password, 15);

  this->writeString(users_file, username);
  this->writeString(users_file, hashed_password);
  this->writeString(users_file, salt);
  this->writeString(users_file, std::to_string(type));
}

void FSMenu::authenticateUser() {
  const std::string users_file = "usuarios.dat";

  std::string username = FSMenu::readString("Escriba su nombre de usuario: ",
      "Por favor escriba un nombre de usuario de máximo 10 caracteres.",
      [](std::string& string) { return string.length() <= 10; });

  std::string password = FSMenu::readString("Escribe su contraseña: ", "",
      [](std::string& string) { return string.length() > 0; });

  switch (this->authenticator.authUser(users_file, username, password)) {
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
}

void FSMenu::readFromFile(const std::string& source_file_name) {
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

void FSMenu::writeToFile(const std::string& source_file_name) {
  std::ofstream source_file(source_file_name);

  if (source_file) {
    char* address = this->fs.readAddress(source_file_name, 0);

    std::string info = address;

    source_file << info;
  }
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

