// @Copyright 2023 Universidad de Costa Rica
// Ángel Chaves Chinchilla (c12113) angel.chaveschichilla@ucr.ac.cr
// David Cerdas Alvarado (C02001) david.cerdasalvarado@ucr.ac.cr
// Camilo Suárez Sandí (C17811) camilo.suarez@ucr.ac.cr
// Ignacio Robles Mayorga (B96549) ignacio.robles@ucr.ac.cr

#include <string>

#define DIRECTORY_COUNT 10
#define DIRECTORY_UNDEFINED -1

#define FAT_COUNT 10
#define FAT_UNDEFINED -1
#define FAT_RESERVED -2
#define FAT_EOF -3

struct DirectoryEntry {
 public:
  int startBlock;
  std::string name;
  time_t date;

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
  DirectoryEntry(int block, std::string name);

  void reset();
};

class FS {
 private:
  DirectoryEntry* directory;
  int* fat;
  char* blocks;

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
   * @return int The position of the first block of the file created or an error
   * code.
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

  std::string toString();

 private:
  /**
  * @brief Find the EOF in the FAT starting at @a index. Index must be a valid
  * start block
  * 
  * @param index start block of a file 
  * @return int The index of EOF in the FAT if successful, another case return
  * FAT_UNDEFINED
  */
  int searchEOF(int index);

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
   * @brief Search the file in directory and return its index in that directory.
   *
   * @param name the file name
   * @return int If the file exists then it returns its index in the directory.
   * Otherwise it returns an error code.
   */
  int searchFile(std::string name);
};
