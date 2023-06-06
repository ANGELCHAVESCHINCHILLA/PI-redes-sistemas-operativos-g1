// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#ifndef TEST

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

      GuachisWebApp webapp_1;
      FileSystemWebApp webapp_2;
      DatabaseWebApp webapp_3;

      if (configuration.hasApp("web")) {
        HttpServer::getInstance().appendApp(&webapp_1);
      }

      if (configuration.hasApp("fs")) {
        HttpServer::getInstance().appendApp(&webapp_2);
      }

      if (configuration.hasApp("db")) {
        HttpServer::getInstance().appendApp(&webapp_3);
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

#endif  // TEST
