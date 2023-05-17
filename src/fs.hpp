// Copyright © 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#ifndef FS_HPP_
#define FS_HPP_

#include <string>

#define DIRECTORY_COUNT 8
#define DIRECTORY_UNDEFINED -1

#define FAT_COUNT 8
#define FAT_UNDEFINED -1
#define FAT_RESERVED -2
#define FAT_EOF -3

#define BLOCK_SIZE 64
#define BLOCK_EOF '\0'

struct DirectoryEntry {
 public:
  /**
   * @brief The position of the first block in the FAT.
   *
   */
  int startBlock;

  /**
   * @brief The name of the file.
   *
   */
  std::string name;

  /**
   * @brief The time the file was created.
   *
   */
  time_t date;

  /**
   */
  std::string owner;

  /**
   */
  char* permissions;

  /**
   */
  std::string belongsFolder;

  /**
   */
  bool isFile;

  /**
   * @brief Default constructor.
   *
   */
  DirectoryEntry();

  /**
   * @brief Constructor.
   *
   */
  ~DirectoryEntry();

  /**
   * @brief Construct a directory entry with a block, name and the current time.
   *
   * @param block The index of the block.
   * @param name The name of the file.
   */
  DirectoryEntry(int block, std::string name, char* permissions = "111",
      std::string belongsFolder = "");

  /**
   * @brief Resets all the properties of the entry.
   *
   */
  void reset();

  /**
   * @brief Changes the current permissions to new permisssions given by param.
   *
   * @param newPermissions The new permissions to set to the directory.
   */
  void changePermissions(char* newPermissions);
};

class FS {
 private:
  /**
   * @brief An array that stores the directory entries.
   *
   */
  DirectoryEntry* directory;

  /**
   * @brief The file allocation table.
   *
   */
  int* fat;

  /**
   * @brief The data of the files.
   *
   */
  char* unit;

 public:
  /**
   * @brief Default constructor.
   *
   */
  FS();

  /**
   * @brief Destructor.
   *
   */
  ~FS();

  /**
   * @brief Creates a file.
   *
   * @param name The name of the file.
   * @return int The position of the first block of the file created or a -1 if
   * there's an error.
   */
  int create(std::string name);

  /**
   * @brief Adds data to a file.
   *
   * @param name The name of the file.
   * @param character The data.
   * @return int An error code.
   */
  int append(std::string name, char character);

  /**
   * @brief Get the size in bytes of a file
   *
   * @param filename the name of the file
   * @return int the size of the file
   */
  int getFileSize(const std::string& filename);

  /**
   */
  char read(std::string fileName, size_t position, char* permissions);

  char* readAddress(std::string file_name, size_t position);

  /**
   * @brief Delete the file, the unit of storage will have garbage.
   *
   * @param name The name of the file.
   * @return int An error code.
   */
  int remove(std::string name);

  /**
   * @brief Delete the file, the unit of storage will be emptied.
   *
   * @param name The name of the file.
   * @return int An error code.
   */
  int deepRemove(std::string name);

  /**
   * @brief Returns the contents of the file system.
   *
   * @return std::string The contents of the file system.
   */
  std::string toString();

 private:
  /**
   * @brief Delete the file. If deep is set to true the unit of storage will be
   * emptied.
   *
   * @param name The name of the file.
   * @param deep If the unit of storage will be emptied.
   * @return int An error code.
   */
  int privateRemove(std::string name, bool deep);

  /**
   * @brief Returns the position of a free space in the directory.
   *
   * @return int The position of a free space in the directory.
   */
  int findDirectorySpace();

  /**
   * @brief Returns the position of a free space in the FAT.
   *
   * @return The position of a free space in the FAT.
   */
  int findFATSpace();

  /**
   * @brief Find the EOF in the FAT starting at @a index. Index must be a valid
   * start block.
   *
   * @param index Start block of a file.
   * @return int If successful it will return the index of EOF in the FAT,
   * otherwide it returns FAT_UNDEFINED.
   */
  int searchEOF(int index);

  /**
   * @brief Search the file in directory and return its index in that directory.
   *
   * @param name the file name
   * @return int If the file exists then it returns its index in the directory.
   * Otherwise it returns an error code.
   */
  int searchFile(std::string name);

 public:
  bool validateUser(const std::string& userName, const std::string& hashKey);
};

#endif  // FS_HPP_
