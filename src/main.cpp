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

      std::string address = configuration.servers["default"].address;
      int port = configuration.servers["default"].port;

      GuachisWebApp webapp_1;
      FileSystemWebApp webapp_2;
      DatabaseWebApp webapp_3;

      if (configuration.hasApp("web")) {
        std::cout << "Running the web app in this server...\n";
        // Cheat code for now
        // TODO: Remove in release
        port = 8001;
        HttpServer::getInstance().appendApp(&webapp_1);
      }

      if (configuration.hasApp("fs")) {
        std::cout << "Running the fs app in this server...\n";
        port = 8002;
        HttpServer::getInstance().appendApp(&webapp_2);
      }

      if (configuration.hasApp("db")) {
        std::cout << "Running the db app in this server...\n";
        port = 8003;
        HttpServer::getInstance().appendApp(&webapp_3);
      }

      // Start the web server
      HttpServer::getInstance().start(address, port);

      std::cout << "Servidor finalizado";
    } catch (const std::runtime_error& error) {
      std::cerr << "error: " << error.what() << std::endl;
    }
  }

  return error;
}

#endif  // TEST
