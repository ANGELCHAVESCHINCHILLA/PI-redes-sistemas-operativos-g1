// Copyright © 2023 Camilo Suárez Sandí

#include "URL.hpp"

URL::URL(const std::string& input) : input(input) {
  std::string copy = this->input;

  this->parse(copy);
}

URL::~URL() {
  //
}

const std::string& URL::getInput() const {
  //
  return this->input;
}

const std::string& URL::getPath() const {
  //
  return this->path;
}

const std::map<std::string, std::string>& URL::getQuery() const {
  //
  return this->query;
}

const std::string& URL::getFragment() const {
  //
  return this->fragment;
}

void URL::parse(std::string& input) {
  this->parseFragment(input);

  this->parseQuery(input);

  this->path = input;
}

void URL::parseFragment(std::string& input) {
  size_t pos = input.find("#");

  if (pos != std::string::npos) {
    this->fragment = input.substr(pos + 1);

    input = input.substr(0, pos);
  }
}

void URL::parseQuery(std::string& input) {
  size_t pos = input.find("?");

  if (pos != std::string::npos) {
    std::string parameters = input.substr(pos + 1);

    input = input.substr(0, pos);

    this->parseQueryParameters(parameters);
  }
}

void URL::parseQueryParameters(std::string& input) {
  size_t pos = input.find("&");

  while (pos != std::string::npos) {
    std::string parameter = input.substr(0, pos);

    this->parseQueryParameter(parameter);

    input = input.substr(pos + 1);

    pos = input.find("&");
  }

  this->parseQueryParameter(input);
}

void URL::parseQueryParameter(std::string& input) {
  size_t pos = input.find("=");

  if (pos != std::string::npos) {
    std::string key = input.substr(0, pos);

    std::string value = input.substr(pos + 1);

    this->query.insert({key, value});
  }
}
