// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

/*
Si quiere usar el menú, defina la macro FS_MENU
Si quiere usar el server, defina la macron FS_WEBSERVER*/

// #define FS_MENU
#define WEBSERVER

#ifdef FS_MENU

#include "error.hpp"
#include "menu/FSMenu.hpp"

int main1(int argc, char** argv) {
  int error = EXIT_SUCCESS;

  FSMenu* menu = FSMenu::getInstance();

  menu->start();

  return error;
}

#endif

#ifdef WEBSERVER

#include "http/HttpServer.hpp"

#include <csignal>
#include <iostream>

/// Start the web server
int main(int argc, char* argv[]) {
  // Register the ctrl + c and kill signals for program termination
  std::signal(SIGTERM, HttpServer::stopServer);
  std::signal(SIGINT, HttpServer::stopServer);

  std::string address = "127.0.0.1";

  int port = 8000;

  if (argc == 2) {
    port = std::stoi(argv[1]);
  }

  // Start the web server
  return HttpServer::getInstance().start(address, port);

  std::cout << "Servidor finalizado";
}

#endif  // WEBSERVER
