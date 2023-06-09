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
  try {
    std::ifstream configuration_file(configuration_path);

    Json::Reader reader;
    Json::Value root;

    reader.parse(configuration_file, root);

    Json::Value apps = root["apps"];

    for (const Json::Value& app : root["apps"]) {
      this->apps.insert(app.asString());
    }

    // TODO: Remove after it stops being used.
    this->port = root["port"].asInt();

    Json::Value servers = root["servers"];

    for (const Json::String& key : servers.getMemberNames()) {
      Json::Value server = servers[key];

      std::string address = server["address"].asString();
      int port = server["port"].asInt();

      ServerConfiguration server_configuration = {
          .address = address,
          .port = port,
      };

      this->servers.insert({key, server_configuration});
    }
  } catch (const std::runtime_error& error) {
    std::cerr << error.what() << "\n";

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

bool Configuration::hasApp(const std::string& app) const {
  return this->apps.find(app) != this->apps.end();
}

const ServerConfiguration& Configuration::getServer(const std::string& app) {
  return this->servers.at(app);
}
