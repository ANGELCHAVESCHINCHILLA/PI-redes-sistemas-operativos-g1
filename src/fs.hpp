//

#include <string>

#define DIRECTORY_COUNT 10
#define DIRECTORY_UNDEFINED -1

#define FAT_COUNT 10
#define FAT_UNDEFINED -1
#define FAT_EOF -2

struct DirectoryEntry {
 public:
  int block;
  std::string name;
  time_t date;

  DirectoryEntry();
  ~DirectoryEntry();

  DirectoryEntry(int block, std::string name);
};

class FS {
 private:
  DirectoryEntry* directory;
  int* fat;
  char* blocks;

 public:
  FS();
  ~FS();

  /**
   * @brief Creates a file.
   *
   * @param name The name of the file.
   * @return The initial block number of the file created
   */
  int create(std::string name);

  /**
   * @brief Adds data to a file.
   *
   * @param name The name of the file.
   * @param character The data.
   */
  int append(std::string name, char character);

  /**
   * @brief Delete the file, the unit of storage will have garbage.
   * 
   * @param name The filename
   * @return int 
   */
  int remove(std::string name);

  std::string toString();

 private:
  /**
   * @brief Returns the position of a free space in the directory.
   *
   */
  int findDirectorySpace();

  /**
   * @brief Returns the position of a free space in the FAT.
   *
   */
  int findFATSpace();

  /**
   * @brief Search the file in directory and return its index in that directory.
   * 
   * @param name the file name
   * @return int If the file exists then return its index in the directory.
   * Another case return DIRECTORY_UNDEFINED
   */
  int searchFile(std::string name);
};
