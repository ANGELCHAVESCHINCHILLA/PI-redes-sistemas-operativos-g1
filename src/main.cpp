// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <iostream>

#include "http/HttpServer.hpp"

int main(int argc, char** argv) {
  int error = EXIT_SUCCESS;

  HttpServer server;

  std::cout << "Server running at http://127.0.0.1:8000\n";

  error = server.start("127.0.0.1", 8000);

  return error;
}
