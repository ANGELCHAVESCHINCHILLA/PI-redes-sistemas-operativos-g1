// Copyright © 2023 Camilo Suárez Sandí

#include "configuration.hpp"

#include <jsoncpp/json/json.h>

#include <fstream>
#include <iostream>

Configuration::Configuration() {
}

Configuration::~Configuration() {
}

Configuration& Configuration::getInstance() {
  static Configuration instance;

  return instance;
}

int Configuration::configure(const std::string& configuration_path) {
  int error = EXIT_SUCCESS;

  std::ifstream configuration_file(configuration_path);

  if (!configuration_file) {
    error = EXIT_FAILURE;

    std::cerr << "Error when reading a file.\n";
  }

  Json::Reader reader;
  Json::Value root;

  if (!error) {
    if (!reader.parse(configuration_file, root)) {
      error = EXIT_FAILURE;

      std::cerr << "Can't parse the JSON file.\n";
    }
  }

  if (!error) {
    Json::Value apps = root["apps"];

    for (size_t index = 0; index < root["apps"].size(); index++) {
      this->apps.push_back(root["apps"][(int) index].asString());
    }

    this->port = root["port"].asInt();
  }

  return error;
}

bool Configuration::hasApp(const std::string& app) const {
  return std::find(this->apps.begin(), this->apps.end(), app) !=
         this->apps.end();
}
