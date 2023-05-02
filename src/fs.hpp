//

#include <memory>
#include <string>

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
  std::unique_ptr<DirectoryEntry[]> directory;
  std::unique_ptr<int[]> fat;
  std::unique_ptr<char[]> blocks;

 public:
  FS();
  ~FS();

  /**
   * @brief Throws an exception if there's no space to create a file.
   *
   * @param name
   */
  void create(std::string name);

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
