// @Copyright 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include "fs.hpp"

#include <ctime>
#include <iostream>
#include <sstream>

#include "error.hpp"

DirectoryEntry::DirectoryEntry() : startBlock(DIRECTORY_UNDEFINED) {
  //
}

DirectoryEntry::~DirectoryEntry() {
  //
}

DirectoryEntry::DirectoryEntry(int block, std::string name)
    : startBlock(block), name(name) {
  this->date = std::time(0);
}

void DirectoryEntry::reset() {
  this->startBlock = FAT_UNDEFINED;
  this->name = "";
  this->date = 0;
}

FS::FS() {
  this->directory = new DirectoryEntry[DIRECTORY_COUNT];
  this->fat = new int[FAT_COUNT];
  this->blocks = new char[FAT_COUNT];

  // Initialize the fat table to undefined
  for (size_t index = 0; index < FAT_COUNT; index++) {
    this->fat[index] = FAT_UNDEFINED;
  }

  // Initialize the blocks to empty
  for (size_t index = 0; index < FAT_COUNT; index++) {
    this->blocks[index] = '\0';
  }
}

FS::~FS() {
  delete[] this->directory;
  delete[] this->fat;
  delete[] this->blocks;
}

int FS::create(std::string name) {
  // Find a space in the directory
  int directory_index = this->findDirectorySpace();

  if (directory_index == DIRECTORY_UNDEFINED) {
    return Error::NO_SPACE_IN_DIRECTORY;
  }

  // Find a space in the fat
  int fat_index = this->findFATSpace();

  if (fat_index == FAT_UNDEFINED) {
    return Error::NO_SPACE_IN_FAT;
  }

  DirectoryEntry directory_entry(fat_index, name);

  this->directory[directory_index] = directory_entry;

  this->fat[fat_index] = FAT_RESERVED;

  return directory_index;
}

int FS::append(std::string name, char character) {
  int error = Error::OK;

  // Search if the file exists in the directory
  int directory_index = this->searchFile(name);

  if (directory_index != DIRECTORY_UNDEFINED) {
    int fat_index = this->directory[directory_index].startBlock;

    // Search if it's reserved or if it's the EOF
    if (this->fat[fat_index] == FAT_RESERVED) {
      // Write the data
      this->blocks[fat_index] = character;

      // Set the EOF
      this->fat[fat_index] = FAT_EOF;
    } else {
      // Find a space in the fat
      int next_index = this->findFATSpace();

      if (next_index != FAT_UNDEFINED) {
        // Search the EOF
        fat_index = this->searchEOF(fat_index);

        if (this->fat[fat_index] == FAT_EOF) {
          // Write the data
          this->blocks[next_index] = character;

          // Update the EOF
          this->fat[fat_index] = next_index;
          this->fat[next_index] = FAT_EOF;
        } else {
          error =  Error::INVALID_FILE;
        }
      } else {
        error = Error::NO_SPACE_IN_FAT;
      }
    }
  } else {
    error = Error::FILE_NOT_FOUND;
  }
  return error;
}

int FS::remove(std::string name) {
  int error = Error::OK;
  int directory_index = this->searchFile(name);

  if (directory_index != DIRECTORY_UNDEFINED) {
    // Remove each block of the FAT assigned to the file.
    int fat_index = this->directory[directory_index].startBlock;
    int tmp_fat_index = fat_index;

    while (this->fat[fat_index] != FAT_EOF &&
        this->fat[fat_index] != FAT_UNDEFINED &&
        this->fat[fat_index] != FAT_RESERVED) {
      // Update the fat index
      fat_index = this->fat[fat_index];

      // Remove the data of the FAT
      this->fat[tmp_fat_index] = FAT_UNDEFINED;
      tmp_fat_index = fat_index;
    }

    if (this->fat[fat_index] == FAT_EOF ||
        this->fat[fat_index]== FAT_RESERVED) {
      // Remove the EOF
      this->fat[fat_index] = FAT_UNDEFINED;

      // Remove directory entry
      this->directory[directory_index].reset();
    } else {
      error = Error::INVALID_FILE;
    }
  } else {
    error = Error::FILE_NOT_FOUND;
  }

  return error;
}

int FS::deepRemove(std::string name) {
  int error = Error::OK;
  int directory_index = this->searchFile(name);

  if (directory_index != DIRECTORY_UNDEFINED) {
    // Remove each block of the FAT assigned to the file.
    int fat_index = this->directory[directory_index].startBlock;
    int tmp_fat_index = fat_index;

    while (this->fat[fat_index] != FAT_EOF &&
          this->fat[fat_index] != FAT_UNDEFINED &&
          this->fat[fat_index] != FAT_RESERVED) {
      // Update fat index
      fat_index = this->fat[fat_index];
      // Remove FAT data
      this->fat[tmp_fat_index] = FAT_UNDEFINED;

      // Remove Unit data
      this->blocks[tmp_fat_index] = '\0';
      // update temporal fat index
      tmp_fat_index = fat_index;
    }

    if (this->fat[fat_index] == FAT_EOF ||
        this->fat[fat_index]== FAT_RESERVED) {
      // Remove the EOF
      this->fat[fat_index] = FAT_UNDEFINED;

      // Remove unit at last block
      this->blocks[fat_index] = '\0';

      // Remove directory entry
      this->directory[directory_index].reset();
    } else {
      error = Error::INVALID_FILE;
    }
  } else {
    error = Error::FILE_NOT_FOUND;
  }
  return error;
}


int FS::findDirectorySpace() {
  int index = 0;
  bool found = false;
  while (index < DIRECTORY_COUNT && !found) {
    if (this->directory[index].startBlock == DIRECTORY_UNDEFINED) {
      found = true;
    } else {
      index++;
    }
  }
  if (!found) {
    index = DIRECTORY_UNDEFINED;
  }
  return index;
}

int FS::findFATSpace() {
  int index = 0;
  bool found = false;
  while (index < FAT_COUNT && !found) {
    if (this->fat[index] == FAT_UNDEFINED) {
      found = true;
    } else {
      index++;
    }
  }
  if (!found) {
    index = FAT_UNDEFINED;
  }
  return index;
}

int FS::searchEOF(int index) {
  int fat_index = index;
  while (this->fat[fat_index] != FAT_EOF &&
        this->fat[fat_index] != FAT_UNDEFINED) {
    fat_index = this->fat[fat_index];
  }
  return fat_index;
}

int FS::searchFile(std::string name) {
  for (int index = 0; index < DIRECTORY_COUNT; index++) {
    DirectoryEntry entry = this->directory[index];

    if (entry.name == name) {
      return index;
    }
  }

  return DIRECTORY_UNDEFINED;
}

std::string FS::toString() {
  std::stringstream ss;

  ss << "Directory:\n";

  for (size_t index = 0; index < DIRECTORY_COUNT; index++) {
    if (this->directory[index].name != "") {
      ss << "\"" << this->directory[index].name << "\" "
         << this->directory[index].startBlock << "\n";
    }
  }

  ss << "\nFAT:\n";

  for (size_t index = 0; index < FAT_COUNT; index++) {
    ss << index << " ";
  }

  ss << "\n";

  for (size_t index = 0; index < FAT_COUNT; index++) {
    int entry = this->fat[index];

    if (entry == FAT_UNDEFINED) {
      ss << "_ ";
    } else if (entry == FAT_RESERVED) {
      ss << "R ";
    } else if (entry == FAT_EOF) {
      ss << "E ";
    } else {
      ss << entry << " ";
    }
  }

  ss << "\n\nBlocks:\n";

  for (size_t index = 0; index < FAT_COUNT; index++) {
    ss << index << " ";
  }

  ss << "\n";

  for (size_t index = 0; index < FAT_COUNT; index++) {
    char data = this->blocks[index];

    if (data == '\0') {
      ss << "_ ";
    } else {
      ss << data << " ";
    }
  }

  ss << "\n";

  return ss.str();
}
