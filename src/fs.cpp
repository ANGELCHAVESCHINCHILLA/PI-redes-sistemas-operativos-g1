//

#include "fs.hpp"

#include <ctime>
#include <iostream>
#include <sstream>

#include "error.hpp"

DirectoryEntry::DirectoryEntry() : block(DIRECTORY_UNDEFINED) {
  //
}

DirectoryEntry::~DirectoryEntry() {
  //
}

DirectoryEntry::DirectoryEntry(int block, std::string name)
    : block(block), name(name) {
  this->date = std::time(0);
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
  // Search if the file exists in the directory
  int directory_index = this->searchFile(name);

  if (directory_index == DIRECTORY_UNDEFINED) {
    return Error::FILE_NOT_FOUND;
  }

  // Search if it's reserved or if it's the EOF
  int fat_index = this->directory[directory_index].block;

  if (this->fat[fat_index] == FAT_RESERVED) {
    // Write the data
    this->blocks[fat_index] = character;

    // Set the EOF
    this->fat[fat_index] = FAT_EOF;

    return EXIT_SUCCESS;
  }

  // Find a space in the fat
  int next_index = this->findFATSpace();

  if (next_index == FAT_UNDEFINED) {
    return Error::NO_SPACE_IN_FAT;
  }

  // Search the EOF
  while (this->fat[fat_index] != FAT_EOF &&
         this->fat[fat_index] != FAT_UNDEFINED) {
    fat_index = this->fat[fat_index];
  }

  if (this->fat[fat_index] != FAT_EOF) {
    return Error::INVALID_FILE;
  }

  // Write the data
  this->blocks[next_index] = character;

  // Update the EOF
  this->fat[fat_index] = next_index;
  this->fat[next_index] = FAT_EOF;

  return EXIT_SUCCESS;
}

std::string FS::toString() {
  std::stringstream ss;

  ss << "Directory:\n";

  for (size_t index = 0; index < DIRECTORY_COUNT; index++) {
    if (this->directory[index].name != "") {
      ss << "\"" << this->directory[index].name << "\" "
         << this->directory[index].block << "\n";
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

int FS::findDirectorySpace() {
  for (int index = 0; index < DIRECTORY_COUNT; index++) {
    if (this->directory[index].block == DIRECTORY_UNDEFINED) {
      return index;
    }
  }

  return DIRECTORY_UNDEFINED;
}

int FS::findFATSpace() {
  for (int index = 0; index < FAT_COUNT; index++) {
    if (this->fat[index] == FAT_UNDEFINED) {
      return index;
    }
  }

  return FAT_UNDEFINED;
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

int FS::remove(std::string name) {
  int directory_index = this->searchFile(name);

  if (directory_index == DIRECTORY_UNDEFINED) {
    return Error::FILE_NOT_FOUND;
  }

  // Remove each block of the FAT assigned to the file.
  int fat_index = this->directory[directory_index].block;
  int previous_fat_index = fat_index;

  while (this->fat[fat_index] != FAT_EOF &&
         this->fat[fat_index] != FAT_UNDEFINED) {
    // Update the fat index
    fat_index = this->fat[fat_index];
    // Remove the data of the FAT
    this->fat[previous_fat_index] = FAT_UNDEFINED;
    previous_fat_index = fat_index;
  }

  if (this->fat[fat_index] != FAT_EOF) {
    return Error::INVALID_FILE;
  }

  // Remove the EOF
  this->fat[fat_index] = FAT_UNDEFINED;

  this->directory[directory_index].block = FAT_UNDEFINED;
  this->directory[directory_index].name = "";
  this->directory[directory_index].date = 0;

  return EXIT_SUCCESS;
}

int FS::deepRemove(std::string name) {
  int directory_index = this->searchFile(name);

  if (directory_index == DIRECTORY_UNDEFINED) {
    return Error::FILE_NOT_FOUND;
  }

  // Remove each block of the FAT assigned to the file.
  int fat_index = this->directory[directory_index].block;
  int previous_fat_index = fat_index;

  while (this->fat[fat_index] != FAT_EOF &&
         this->fat[fat_index] != FAT_UNDEFINED) {
    // Update the fat index
    fat_index = this->fat[fat_index];
    // Remove the data of the FAT
    this->fat[previous_fat_index] = FAT_UNDEFINED;
    this->blocks[previous_fat_index] = '\0';
    previous_fat_index = fat_index;
  }

  if (this->fat[fat_index] != FAT_EOF) {
    return Error::INVALID_FILE;
  }

  // Remove the EOF
  this->fat[fat_index] = FAT_UNDEFINED;

  // Remove unit at last block
  this->blocks[fat_index] = '\0';

  this->directory[directory_index].block = FAT_UNDEFINED;
  this->directory[directory_index].name = "";
  this->directory[directory_index].date = 0;

  return EXIT_SUCCESS;
}
