// Copyright © 2023 Camilo Suárez Sandí

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <algorithm>
#include <string>
#include <vector>

class Configuration {
 public:
  static Configuration& getInstance();

  // TODO: Maybe change to a set
  std::vector<std::string> apps;

  int port;

 private:
  // Constructor
  Configuration();

 public:
  // Destructor
  ~Configuration();

 private:
  // Copy Constructor
  Configuration(const Configuration&) = delete;

  // Copy Assignment
  Configuration& operator=(const Configuration&) = delete;

  // Move Constructor
  Configuration(Configuration&& other) = delete;

  // Move Assignment
  Configuration& operator=(Configuration&& other) = delete;

 public:
  int configure(const std::string& configuration_path);

  bool hasApp(const std::string& app) const;
};

#endif  // CONFIGURATION_HPP_
