// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <assert.h>

#include <iostream>

#include "error.hpp"
#include "menu/FSMenu.hpp"

int main(int argc, char** argv) {
  int error = EXIT_SUCCESS;

  FSMenu* menu = FSMenu::getInstance();

  menu->start();

  return error;
}
