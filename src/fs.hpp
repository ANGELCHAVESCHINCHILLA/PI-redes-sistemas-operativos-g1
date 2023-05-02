//

#include <memory>
#include <string>
#include <vector>

/*

Directory:
"a.dat"   0
"b.dat"   1

FAT
0 1 2 3 4 5 6 7 8
x 2 x _ _ _ _ _ _

Blocks
0 1 2 3 4 5 6 7 8
a b 2 _ _ _ _ _ _

*/

#define DIRECTORY_COUNT 10
#define DIRECTORY_UNDEFINED -1

#define BLOCK_COUNT 10
#define BLOCK_UNDEFINED -1
#define BLOCK_EOF 0

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
  // std::unique_ptr<DirectoryEntry[]> directory;
  std::vector<DirectoryEntry> directory;
  // std::unique_ptr<int[]> fat;
  std::vector<int> fat;
  // std::unique_ptr<char[]> blocks;
  std::vector<char> blocks;

 public:
  FS();
  ~FS();

  /**
   * @brief Throws an exception if there's no space to create a file.
   *
   * @param name
   * @return The initial block number of the file created
   */
  int create(std::string name);

  /**
   * @brief Throws an exception if there's no space to add the data to the file.
   *
   * @param name
   * @param character
   */
  void append(std::string name, char character);

  std::string toString();

 private:
  int findDirectorySpace();

  int findBlockSpace();
};

