// Copyright © 2023 Camilo Suárez Sandí

#include "HttpRequest.hpp"

#include <sstream>

HttpRequest::HttpRequest(const std::string& input) : input(input) {
  std::string copy = this->input;

  this->parse(copy);
}

HttpRequest::~HttpRequest() {
}

const std::string& HttpRequest::getMethod() const {
  return this->method;
}

const URL& HttpRequest::getTarget() const {
  return this->target;
}

const std::string& HttpRequest::getBody() const {
  return this->body;
}

std::string HttpRequest::toString() {
  std::stringstream ss;

  ss << this->method << " " << this->target.getInput() << " " << HTTP_VERSION
     << "\n";

  for (auto& [key, value] : this->headers) {
    ss << key << ": " << value << "\n";
  }

  ss << "\n";

  ss << this->body;

  return ss.str();
}

bool HttpRequest::hasHeader(const std::string& key) const {
  return this->headers.count(key) > 0;
}

std::string HttpRequest::getHeader(const std::string& key) const {
  return this->headers.at(key);
}

void HttpRequest::parse(std::string& input) {
  this->parseLine(input);

  this->parseHeaders(input);

  this->body = input;
}

void HttpRequest::parseLine(std::string& input) {
  size_t pos = std::string::npos;

  pos = input.find(" ");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  this->method = input.substr(0, pos);

  input = input.substr(pos + 1);

  pos = input.find(" ");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  this->target = URL(input.substr(0, pos));

  input = input.substr(pos + 1);

  pos = input.find("\n");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  std::string version = input.substr(0, pos);

  input = input.substr(pos + 1);

  if (version != HTTP_VERSION) {
    // throw an exception
    return;
  }
}

void HttpRequest::parseHeaders(std::string& input) {
  size_t pos = input.find("\n");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  std::string header = input.substr(0, pos);

  input = input.substr(pos + 1);

  while (header.size() > 1) {
    this->parseHeader(header);

    pos = input.find("\n");

    if (pos == std::string::npos) {
      // throw an exception
      return;
    }

    header = input.substr(0, pos);

    input = input.substr(pos + 1);
  }
}

void HttpRequest::parseHeader(std::string& input) {
  size_t pos = input.find(":");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  std::string key = input.substr(0, pos);

  std::string value = input.substr(pos + 2);

  this->headers.insert({key, value});
}
