//

#include "fs.hpp"

#include <iostream>
#include <sstream>

DirectoryEntry::DirectoryEntry() : block(DIRECTORY_UNDEFINED) {
  //
}

DirectoryEntry::~DirectoryEntry() {
  //
}

DirectoryEntry::DirectoryEntry(int block, std::string name)
    : block(block), name(name) {
  this->date = time(0);
}

FS::FS() {
  this->directory = new DirectoryEntry[DIRECTORY_COUNT];
  this->fat = new int[BLOCK_COUNT];
  this->blocks = new char[BLOCK_COUNT];

  // Initialize the fat table to undefined
  for (size_t index = 0; index < BLOCK_COUNT; index++) {
    this->fat[index] = BLOCK_UNDEFINED;
  }

  // Initialize the blocks to empty
  for (size_t index = 0; index < BLOCK_COUNT; index++) {
    this->blocks[index] = '\0';
  }
}

FS::~FS() {
  //
}

int FS::create(std::string name) {
  // Find a space in the directory
  int directory_index = this->findDirectorySpace();

  if (directory_index == DIRECTORY_UNDEFINED) {
    return DIRECTORY_UNDEFINED;
  }

  int block_index = this->findBlockSpace();

  if (block_index == BLOCK_UNDEFINED) {
    return BLOCK_UNDEFINED;
  }

  DirectoryEntry directory_entry(block_index, name);

  this->directory[directory_index] = directory_entry;

  this->fat[block_index] = BLOCK_EOF;

  return directory_index;
}

void FS::append(std::string name, char character) {
  //
}

std::string FS::toString() {
  std::stringstream ss;

  ss << "Directory:\n";

  for (size_t index = 0; index < DIRECTORY_COUNT; index++) {
    ss << "\"" << this->directory[index].name << "\" "
       << this->directory[index].block << "\n";
  }

  ss << "\nFAT:\n";

  for (size_t index = 0; index < BLOCK_COUNT; index++) {
    ss << index << " ";
  }

  ss << "\n";

  for (size_t index = 0; index < BLOCK_COUNT; index++) {
    int entry = this->fat[index];

    if (entry == BLOCK_UNDEFINED) {
      ss << "_ ";
    } else if (entry == BLOCK_EOF) {
      ss << "* ";
    } else {
      ss << entry << " ";
    }
  }

  ss << "\n\nBlocks:\n";

  for (size_t index = 0; index < BLOCK_COUNT; index++) {
    ss << index << " ";
  }

  ss << "\n";

  for (size_t index = 0; index < BLOCK_COUNT; index++) {
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

int FS::findBlockSpace() {
  for (int index = 0; index < BLOCK_COUNT; index++) {
    if (this->fat[index] == BLOCK_UNDEFINED) {
      return index;
    }
  }

  return BLOCK_UNDEFINED;
}
