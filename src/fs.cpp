// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (C12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include "fs.hpp"

#include <time.h>

#include <cstring>
#include <iostream>
#include <sstream>

#include "error.hpp"

DirectoryEntry::DirectoryEntry() : startBlock(DIRECTORY_UNDEFINED) {
  //
}

DirectoryEntry::~DirectoryEntry() {
  //
}

DirectoryEntry::DirectoryEntry(
    int block, std::string name, char* permissions, std::string belongsFolder)
    : startBlock(block),
      name(name),
      permissions(permissions),
      belongsFolder(belongsFolder) {
  this->date = ::time(0);
}

void DirectoryEntry::reset() {
  this->startBlock = FAT_UNDEFINED;
  this->name = "";
  this->date = 0;
}

void DirectoryEntry::changePermissions(char* newPermissions) {
  this->permissions = newPermissions;
}

FS::FS() {
  this->directory = new DirectoryEntry[DIRECTORY_COUNT];
  this->fat = new int[FAT_COUNT];
  this->unit = new char[FAT_COUNT * BLOCK_SIZE];

  // Initialize the fat table to undefined
  ::memset(this->fat, FAT_UNDEFINED, FAT_COUNT * sizeof(int));

  // Initialize the unit to empty
  ::memset(this->unit, (char) BLOCK_EOF, FAT_COUNT * BLOCK_SIZE);
}

FS::~FS() {
  delete[] this->directory;
  delete[] this->fat;
  delete[] this->unit;
}

int FS::create(std::string name) {
  int error = Error::OK;
  // Find a space in the directory
  const int directory_index = this->findDirectorySpace();

  if (directory_index == DIRECTORY_UNDEFINED) {
    error = Error::NO_SPACE_IN_DIRECTORY;
  }

  if (!error) {
    // Find a space in the fat
    const int fat_index = this->findFATSpace();

    if (fat_index == FAT_UNDEFINED) {
      error = Error::NO_SPACE_IN_FAT;
    }

    if (!error) {
      DirectoryEntry directory_entry(fat_index, name);

      this->directory[directory_index] = directory_entry;

      this->fat[fat_index] = FAT_RESERVED;
    }
  }

  if (!error) {
    return directory_index;
  } else {
    return -1;
  }
}

// ¿Deberíamos controlar que el parámetro character no sea el caracter nulo?
int FS::append(std::string name, char character) {
  int error = Error::OK;

  // Search if the file exists in the directory
  const int directory_index = this->searchFile(name);

  if (directory_index == DIRECTORY_UNDEFINED) {
    error = Error::FILE_NOT_FOUND;
  }

  if (!error) {
    const int start_block = this->directory[directory_index].startBlock;

    // If is the first time that a character will be added to the file
    if (this->fat[start_block] == FAT_RESERVED) {
      // Write the data
      this->unit[start_block * BLOCK_SIZE] = character;
      // The next character is set as EOF
      this->unit[start_block * BLOCK_SIZE + 1] = BLOCK_EOF;
      // Set the EOF in the FAT
      this->fat[start_block] = FAT_EOF;
      // If the file already had at least one character
    } else {
      // Find the EOF in FAT
      const int fat_index = this->searchEOF(start_block);
      if (this->fat[fat_index] == FAT_EOF) {
        // Find the EOF in the block
        int index = 0;
        while (this->unit[fat_index * BLOCK_SIZE + index] != BLOCK_EOF &&
               index < BLOCK_SIZE) {
          ++index;
        }
        const int block_index = index;

        // Write the data (a character) where the EOF was storaged
        this->unit[fat_index * BLOCK_SIZE + block_index] = character;

        // If there is not space in the block
        if (block_index == BLOCK_SIZE - 1) {
          // Find a new free block in FAT
          const int next_fat_index = this->findFATSpace();
          if (next_fat_index == FAT_UNDEFINED) {
            error = Error::NO_SPACE_IN_FAT;
          }

          if (!error) {
            // Update the EOF In FAT
            this->fat[fat_index] = next_fat_index;
            this->fat[next_fat_index] = FAT_EOF;

            // Set the EOF in the unit
            this->unit[next_fat_index * BLOCK_SIZE] = BLOCK_EOF;
          }

          // If there's space in the block
        } else if (index < BLOCK_SIZE - 1) {
          // Set the EOF in the unit
          this->unit[fat_index * BLOCK_SIZE + block_index + 1] = BLOCK_EOF;
        } else {
          error = Error::NOT_OK;
        }
      } else {
        error = Error::INVALID_FILE;
      }
    }
  }
  return error;
}

int FS::getFileSize(const std::string& filename) {
  int size = 0;
  int directory_index = this->searchFile(filename);

  if (directory_index != DIRECTORY_UNDEFINED) {
    int fat_index = this->directory[directory_index].startBlock;
    // find size of full blocks
    while (this->fat[fat_index] != FAT_EOF &&
           this->fat[fat_index] != FAT_RESERVED &&
           this->fat[fat_index] != FAT_UNDEFINED) {
      size += static_cast<int>(BLOCK_SIZE);
      fat_index = this->fat[fat_index];
    }

    // find size of uncomplete blocks
    int block_index = fat_index * static_cast<int>(BLOCK_SIZE);
    while (this->unit[block_index] != BLOCK_EOF) {
      size++;
      block_index++;
    }
  } else {
    std::cerr << "directory undefined" << std::endl;
  }

  return size;
}

char FS::read(std::string fileName, size_t position, char* permissions) {
  char* address = this->readAddress(fileName, position);

  if (address != nullptr) {
    return *address;
  }

  return '\0';
}

char* FS::readAddress(std::string file_name, size_t position) {
  int error = Error::OK;
  int directory_index = this->searchFile(file_name);

  if (directory_index == DIRECTORY_UNDEFINED) {
    error = Error::FILE_NOT_FOUND;
  }

  if (!error) {
    // validate if position is out of bounds or not
    error = static_cast<size_t>(this->getFileSize(file_name)) >= position
                ? Error::OK
                : Error::NOT_OK;

    if (!error) {
      // start block of the file
      const int start_block = this->directory[directory_index].startBlock;
      // The amount of blocks to traverse to reach the desired character
      const int block_number = position / static_cast<int>(BLOCK_SIZE);
      // Number of positions to go through in the block to reach the desired
      // character
      const int char_number = position - block_number * BLOCK_SIZE;

      // Find the block in which the character is stored
      int fat_index = start_block;
      int block_count = 0;
      while (block_count < block_number) {
        fat_index = this->fat[fat_index];
        ++block_count;
      }

      // Find the char in the block
      int char_index = 0;
      while (this->unit[fat_index * BLOCK_SIZE + char_index] != BLOCK_EOF &&
             char_index < char_number) {
        ++char_index;
      }

      return &this->unit[fat_index * BLOCK_SIZE + char_index];
    }
  }

  return nullptr;
}

int FS::remove(std::string name) {
  //
  return this->privateRemove(name, false);
}

int FS::deepRemove(std::string name) {
  //
  return this->privateRemove(name, true);
}

int FS::privateRemove(std::string name, bool deep) {
  int error = Error::OK;

  int directory_index = this->searchFile(name);

  if (directory_index == DIRECTORY_UNDEFINED) {
    error = Error::FILE_NOT_FOUND;
  }

  if (!error) {
    // Remove each block of the FAT assigned to the file.
    int fat_index = this->directory[directory_index].startBlock;
    int tmp_fat_index = fat_index;

    while (this->fat[fat_index] != FAT_EOF &&
           this->fat[fat_index] != FAT_UNDEFINED &&
           this->fat[fat_index] != FAT_RESERVED && fat_index < FAT_COUNT) {
      // Update fat index
      fat_index = this->fat[fat_index];
      // Remove FAT data
      this->fat[tmp_fat_index] = FAT_UNDEFINED;

      // Remove unit data
      if (deep) {
        ::memset(&this->unit[tmp_fat_index], BLOCK_EOF, BLOCK_SIZE);
      }

      // Update temporal fat index
      tmp_fat_index = fat_index;
    }

    if (this->fat[fat_index] != FAT_EOF &&
        this->fat[fat_index] != FAT_RESERVED) {
      error = Error::INVALID_FILE;
    }

    if (!error) {
      // Remove the EOF
      this->fat[fat_index] = FAT_UNDEFINED;

      // Remove unit at last block
      if (deep) {
        ::memset(&this->unit[fat_index], BLOCK_EOF, BLOCK_SIZE);
      }

      // Remove directory entry
      this->directory[directory_index].reset();
    }
  }

  return error;
}

int FS::findDirectorySpace() {
  int index = 0;
  bool found = false;

  while (index < DIRECTORY_COUNT && !found) {
    if (this->directory[index].startBlock == DIRECTORY_UNDEFINED) {
      found = true;
      break;
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
      break;
    } else {
      ++index;
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
         this->fat[fat_index] != FAT_UNDEFINED && fat_index < FAT_COUNT) {
    fat_index = this->fat[fat_index];
  }

  return fat_index;
}

int FS::searchFile(std::string name) {
  int index = 0;
  bool found = false;

  while (index < DIRECTORY_COUNT && !found) {
    DirectoryEntry entry = this->directory[index];

    if (entry.name == name) {
      found = true;
      break;
    } else {
      ++index;
    }
  }

  if (!found) {
    index = DIRECTORY_UNDEFINED;
  }

  return index;
}

std::string FS::toString() {
  std::stringstream ss;

  ss << "Directory:\n";

  for (size_t index = 0; index < DIRECTORY_COUNT; ++index) {
    if (this->directory[index].name != "") {
      ss << "\"" << this->directory[index].name << "\" "
         << this->directory[index].startBlock << "\n";
    }
  }

  ss << "\nFAT:\n";

  for (size_t index = 0; index < FAT_COUNT; ++index) {
    ss << index << " ";
  }

  ss << "\n";

  for (size_t index = 0; index < FAT_COUNT; ++index) {
    const int entry = this->fat[index];

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

  for (size_t index = 0; index < FAT_COUNT; ++index) {
    // ss << index << " ";
    for (size_t unit_index = 0; unit_index < BLOCK_SIZE; ++unit_index) {
      char data = this->unit[unit_index + index * BLOCK_SIZE];

      if (data == '\0') {
        ss << "_ ";
      } else {
        ss << data << " ";
      }
    }
    ss << "\n";
  }

  ss << "\n";

  return ss.str();
}

int FS::changePermissionsToEntry(std::string name, char* newPermissions) {
  int error = Error::OK;
  // Search directory entry
  int directory_index = this->searchFile(name);
  // If not exists change error value
  if (directory_index == DIRECTORY_UNDEFINED) {
    error = Error::FILE_NOT_FOUND;
  }
  // If not error, so the entry exists
  if (!error) {
    // change permissions
    this->directory[directory_index].changePermissions(newPermissions);
  }
  return error;
}
