// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <stdlib.h>

enum Error {
  OK = EXIT_SUCCESS,
  NOT_OK = EXIT_FAILURE,

  NO_SPACE_IN_DIRECTORY,
  NO_SPACE_IN_FAT,

  INVALID_FILE,

  FILE_NOT_FOUND,

  USER_NOT_FOUND,
  INVALID_PASSWORD
};

#endif  // ERROR_HPP_
