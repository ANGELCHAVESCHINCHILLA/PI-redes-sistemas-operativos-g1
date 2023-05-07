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

  return error;
}

int runServer() {
  int error = EXIT_SUCCESS;

  Socket socket;

  error = socket.create();

  if (!error) {
    error = socket.bind("127.0.0.1", 8000);
  }

  if (!error) {
    error = socket.listen();
  }

  if (!error) {
    while (true) {
      error = socket.accept();

      std::string message;

      if (!error) {
        std::cout << "I will receive a message!\n";

        error = socket.receive(message);
      }

      if (!error) {
        std::cout << message << "\n";
      }
    }
  }

  return error;
}

int runClient() {
  int error = EXIT_SUCCESS;

  Socket socket;

  error = socket.create();

  if (!error) {
    error = socket.connect("127.0.0.1", 8000);
  }

  if (!error) {
    std::cout << "I will send a message!\n";

    error = socket.send("Hello, World!");
  }

  return error;
}
