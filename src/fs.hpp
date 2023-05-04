//

#include <string>

/*
Directory:
"a.dat" 0

FAT:
0 1 2 3 4 5 6 7 8 9
* _ _ _ _ _ _ _ _ _

Blocks:
0 1 2 3 4 5 6 7 8 9
_ _ _ _ _ _ _ _ _ _
*/

/*
Directory:
"a.dat" 0

FAT:
0 1 2 3 4 5 6 7 8 9
1 * _ _ _ _ _ _ _ _

Blocks:
0 1 2 3 4 5 6 7 8 9
a _ _ _ _ _ _ _ _ _
*/

/*
Directory:
"a.dat"   0
"b.dat"   1

FAT:
0 1 2 3 4 5 6 7 8
* 2 * _ _ _ _ _ _

Blocks:
0 1 2 3 4 5 6 7 8
a b 2 _ _ _ _ _ _
*/

#define DIRECTORY_COUNT 10
#define DIRECTORY_UNDEFINED -1

#define BLOCK_COUNT 10
#define BLOCK_UNDEFINED -1
#define BLOCK_EOF -2

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

  int searchFile(std::string name);
};
