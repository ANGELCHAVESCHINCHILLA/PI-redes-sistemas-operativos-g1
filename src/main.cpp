// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <string.h>

#include <iostream>

#include "net/Socket.hpp"

int runServer();

int runClient();

int main(int argc, char** argv) {
  int error = EXIT_SUCCESS;

  if (argc == 1) {
    std::cout << "Running server...\n";

    error = runServer();
  }

  if (argc == 2) {
    std::cout << "Running client...\n";

    error = runClient();
  }

  std::cout << error << "\n";

  return error;
}

int runServer() {
  int error = EXIT_SUCCESS;

  Socket socket;

  error = socket.create();

  if (!error) {
    error = socket.bind("127.0.0.1", 8000);
  }

  std::cout << error << "\n";

  if (!error) {
    error = socket.listen();
  }

  std::cout << error << "\n";

  if (!error) {
    while (true) {
      error = socket.accept();
    }
  }

  std::cout << error << "\n";

  return error;
}

int runClient() {
  int error = EXIT_SUCCESS;

  Socket socket;

  error = socket.create();

  if (!error) {
    error = socket.connect("127.0.0.1", 8000);
  }

  std::cout << error << "\n";

  return error;
}
