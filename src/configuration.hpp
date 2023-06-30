// Copyright © 2023 Camilo Suárez Sandí

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <map>
#include <set>
#include <string>

struct ServerConfiguration {
  std::string address;
  int port;
};

class Configuration {
 public:
  static Configuration& getInstance();

  std::set<std::string> apps;
  std::map<std::string, ServerConfiguration> servers;

  std::string certificate_file_path;
  std::string private_key_file_path;

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

  const ServerConfiguration& getServer(const std::string& app);
};

#endif  // CONFIGURATION_HPP_
