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

  Socket server_socket;
  Socket client_socket;

  error = server_socket.create();

  if (!error) {
    error = server_socket.bind("127.0.0.1", 8000);
  }

  if (!error) {
    error = server_socket.listen();
  }

  if (!error) {
    while (true) {
      error = server_socket.accept(client_socket);

      std::string message;

      if (!error) {
        std::cout << "I will receive a message!\n";

        error = client_socket.receive(message);
      }

      if (!error) {
        std::cout << message << "\n";

        break;
      }
    }
  }

  return error;
}

int runClient() {
  int error = EXIT_SUCCESS;

  Socket client_socket;

  error = client_socket.create();

  if (!error) {
    error = client_socket.connect("127.0.0.1", 8000);
  }

  if (!error) {
    std::cout << "I will send a message!\n";

    error = client_socket.send("Hello, World!");
  }

  return error;
}
