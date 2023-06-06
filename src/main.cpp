// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <signal.h>

#include <iostream>

#include "configuration.hpp"
#include "database/DatabaseWebApp.hpp"
#include "error.hpp"
#include "filesystem_app/FileSystemWebApp.hpp"
#include "http/HttpServer.hpp"
#include "menu/FSMenu.hpp"
#include "webapp/GuachisWebApp.hpp"

int main(int argc, char** argv) {
  int error = EXIT_SUCCESS;

  if (argc != 2) {
    error = EXIT_FAILURE;

    std::cerr << "You have to set a configuration file.\n";
  }

  Configuration& configuration = Configuration::getInstance();

  if (!error) {
    std::string configuration_path = argv[1];

    error = configuration.configure(configuration_path);
  }

  if (!error) {
    try {
      // Register the ctrl + c and kill signals for program termination
      ::signal(SIGTERM, HttpServer::stopServer);
      ::signal(SIGINT, HttpServer::stopServer);

      std::string address = "127.0.0.1";

      if (configuration.hasApp("web")) {
        GuachisWebApp webapp;

        HttpServer::getInstance().appendApp(&webapp);
      }

      if (configuration.hasApp("fs")) {
        FileSystemWebApp webapp;

        HttpServer::getInstance().appendApp(&webapp);
      }

      if (configuration.hasApp("db")) {
        DatabaseWebApp webapp;

        HttpServer::getInstance().appendApp(&webapp);
      }

      // Start the web server
      HttpServer::getInstance().start(address, configuration.port);

      std::cout << "Servidor finalizado";
    } catch (const std::runtime_error& error) {
      std::cerr << "error: " << error.what() << std::endl;
    }
  }

  return error;
}
