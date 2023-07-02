// Copyright © 2023 Camilo Suárez Sandí

#ifndef LOG_HANDLER_HPP_
#define LOG_HANDLER_HPP_

#include <string>
#include <vector>

#include "../common/common.hpp"

class LogHandler {
  DISABLE_COPY(LogHandler);

 private:
  std::string path;
  std::vector<std::string> lines;

 public:
  /// Constructor
  LogHandler(std::string path);

  /// Destructor
  ~LogHandler() = default;

  int read();

  size_t getLinesCount();

  std::string getLine(size_t offset);
};

#endif  // LOG_HANDLER_HPP_
