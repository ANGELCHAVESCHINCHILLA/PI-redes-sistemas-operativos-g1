// @Copyright 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

enum Error {
  OK = 0,
  NOT_OK = -1,

  NO_SPACE_IN_DIRECTORY = -2,
  NO_SPACE_IN_FAT = -3,

  FILE_NOT_FOUND = -4,

  INVALID_FILE = -5,
};
