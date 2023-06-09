// Copyright © 2023 Camilo Suárez Sandí

#include "URL.hpp"

#include <sstream>
#include <stdexcept>

URL::URL() {
}

URL::URL(const std::string& input) : input(input) {
  std::string copy = this->input;

  this->parse(copy);
}

URL::~URL() {
}

const std::string& URL::getInput() const {
  return this->input;
}

const std::string& URL::getScheme() const {
  return this->scheme;
}

const std::string& URL::getHost() const {
  return this->host;
}

int URL::getPort() const {
  return this->port;
}

const std::string& URL::getPath() const {
  return this->path;
}

const std::map<std::string, std::string>& URL::getQuery() const {
  return this->query;
}

const std::string& URL::getFragment() const {
  return this->fragment;
}

URL URL::copy() const {
  URL url;

  url.input = std::string(this->input);
  url.scheme = std::string(this->scheme);
  url.host = std::string(this->host);
  url.port = this->port;
  url.path = std::string(this->path);
  url.query = std::map(this->query);
  url.fragment = std::string(fragment);

  return url;
}

std::string URL::toString() const {
  std::stringstream ss;

  if (!this->scheme.empty()) {
    ss << this->scheme << "://";
  }

  ss << host;

  if (this->port != -1) {
    ss << ":" << this->port;
  }

  ss << this->path;

  if (!this->query.empty()) {
    ss << "?";

    size_t index = 0;

    for (auto& [key, value] : this->query) {
      ss << key << "=" << value;

      if (index < this->query.size() - 1) {
        ss << "&";
      }

      index++;
    }
  }

  if (!this->fragment.empty()) {
    ss << "#" << this->fragment;
  }

  return ss.str();
}

void URL::parse(std::string& input) {
  this->parseFragment(input);

  this->parseQuery(input);

  this->parseScheme(input);

  this->parsePath(input);

  this->parsePort(input);

  this->parseHost(input);
}

void URL::parseFragment(std::string& input) {
  size_t pos = input.find_last_of("#");

  if (pos != std::string::npos) {
    this->fragment = input.substr(pos + 1);

    input = input.substr(0, pos);
  }
}

void URL::parseQuery(std::string& input) {
  size_t pos = input.find_last_of("?");

  if (pos != std::string::npos) {
    std::string parameters = input.substr(pos + 1);

    input = input.substr(0, pos);

    this->parseQueryParameters(parameters);
  }
}

void URL::parseQueryParameters(std::string& input) {
  size_t pos = input.find_last_of("&");

  while (pos != std::string::npos) {
    std::string parameter = input.substr(0, pos);

    this->parseQueryParameter(parameter);

    input = input.substr(pos + 1);

    pos = input.find("&");
  }

  this->parseQueryParameter(input);
}

void URL::parseQueryParameter(const std::string& input) {
  size_t pos = input.find_first_of("=");

  if (pos == std::string::npos) {
    // throw std::runtime_error("A query parameter is missing the '=' sign.");
    return;
  }

  std::string key = input.substr(0, pos);

  std::string value = input.substr(pos + 1);

  this->query.insert({key, value});
}

void URL::parsePath(std::string& input) {
  size_t pos = input.find_first_of("/");

  if (pos == std::string::npos) {
    throw std::runtime_error("The url is missing the path.");
  }

  this->path = input.substr(pos);

  input = input.substr(0, pos);
}

void URL::parseScheme(std::string& input) {
  size_t pos = input.find("://");

  if (pos != std::string::npos) {
    this->scheme = input.substr(0, pos);

    input = input.substr(pos + 3);
  }
}

void URL::parsePort(std::string& input) {
  size_t pos = input.find_last_of(":");

  if (pos == std::string::npos) {
    this->port = -1;
  } else {
    this->port = std::stoi(input.substr(pos + 1));

    input = input.substr(0, pos);
  }
}

void URL::parseHost(std::string& input) {
  this->host = input;

  input.clear();

  if (this->host.empty() && this->port != -1) {
    throw std::runtime_error("The url can't have a port without a host.");
  }
}
