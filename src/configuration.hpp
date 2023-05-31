// Copyright © 2023 Camilo Suárez Sandí

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <string>

class Configuration {
 public:
  static Configuration& getInstance();

  std::string app;

  int port;

 private:
  // Constructor
  Configuration();

  // Destructor
  ~Configuration();

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
};

#endif  // CONFIGURATION_HPP_
