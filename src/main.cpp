// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <signal.h>

#include "database/DatabaseWebApp.hpp"
#include "error.hpp"
#include "http/HttpServer.hpp"

int main(int argc, char* argv[]) {

  try {
    ::signal(SIGTERM, HttpServer::stopServer);
    ::signal(SIGINT, HttpServer::stopServer);

    std::string address = "127.0.0.1";

    DatabaseWebApp webApp;

    HttpServer::getInstance().appendApp(&webApp);

    HttpServer::getInstance().start(address, 8080);

    std::cout << "server finalized" << std::endl;

  } catch (const std::runtime_error e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}
