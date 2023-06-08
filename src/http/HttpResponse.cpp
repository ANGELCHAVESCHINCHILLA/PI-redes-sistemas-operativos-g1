// Copyright © 2023 Camilo Suárez Sandí

#include "HttpResponse.hpp"

#include <iostream>

// { Code, ReasonPhrase }
const HttpResponse::ReasonPhrases HttpResponse::REASON_PHRASES = {
    {100, "Continue"},
    {101, "Switching Protocols"},
    {200, "OK"},
    {201, "Created"},
    {202, "Accepted"},
    {203, "Non-Authoritative Information"},
    {204, "No Content"},
    {205, "Reset Content"},
    {206, "Partial Content"},
    {300, "Multiple Choices"},
    {301, "Moved Permanently"},
    {302, "Found"},
    {303, "See Other"},
    {304, "Not Modified"},
    {305, "Use Proxy"},
    {307, "Temporary Redirect"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {402, "Payment Required"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {406, "Not Acceptable"},
    {407, "Proxy Authentication Required"},
    {408, "Request Timeout"},
    {409, "Conflict"},
    {410, "Gone"},
    {411, "Length Required"},
    {412, "Precondition Failed"},
    {413, "Payload Too Large"},
    {414, "URI Too Long"},
    {415, "Unsupported Media Type"},
    {416, "Range Not Satisfiable"},
    {417, "Expectation Failed"},
    {426, "Upgrade Required"},
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"},
    {504, "Gateway Timeout"},
    {505, "HTTP Version Not Supported"},
};

HttpResponse::HttpResponse() : body(std::make_shared<std::stringstream>()) {
}

HttpResponse::HttpResponse(const std::string& input)
    : input(input), body(std::make_shared<std::stringstream>()) {
  std::string copy = input;

  this->parse(copy);
}

HttpResponse::~HttpResponse() {
}

void HttpResponse::setStatusCode(size_t status_code) {
  auto iterator = HttpResponse::REASON_PHRASES.find(status_code);

  if (iterator == HttpResponse::REASON_PHRASES.end()) {
    // throw an exception
    return;
  }

  this->status_code = status_code;
  this->reason_phrase = HttpResponse::REASON_PHRASES.at(status_code);
}

void HttpResponse::setHeader(const std::string& key, const std::string& value) {
  this->headers[key] = value;
}

size_t HttpResponse::getStatusCode() const {
  return this->status_code;
}

const std::string& HttpResponse::getReasonPhrase() const {
  return this->reason_phrase;
}

const std::stringstream& HttpResponse::getBody() const {
  return *this->body;
}

std::stringstream& HttpResponse::getBody() {
  return *this->body;
}

size_t HttpResponse::getBodyLength() const {
  return this->getBody().str().length();
}

bool HttpResponse::hasHeader(const std::string& key) const {
  return this->headers.count(key) > 0;
}

const std::string& HttpResponse::getHeader(const std::string& key) const {
  return this->headers.at(key);
}

std::string HttpResponse::toString() const {
  std::stringstream ss;

  ss << "HTTP/1.1 " << this->status_code << " " << this->reason_phrase << "\n";

  for (auto& [key, value] : this->headers) {
    ss << key << ": " << value << "\n";
  }

  ss << "\n";

  ss << this->body->str();

  return ss.str();
}

void HttpResponse::parse(std::string& input) {
  this->parseLine(input);

  this->parseHeaders(input);

  this->getBody() << input;
}

void HttpResponse::parseLine(std::string& input) {
  size_t pos = std::string::npos;

  pos = input.find(" ");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  // Get the version
  std::string version = input.substr(0, pos);

  input = input.substr(pos + 1);

  if (version != "HTTP/1.1") {
    // throw an exception
    return;
  }

  pos = input.find(" ");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  // Get the status code
  this->status_code = std::stoi(input.substr(0, pos));

  input = input.substr(pos + 1);

  // Check if the status code is in the map
  auto iterator = HttpResponse::REASON_PHRASES.find(this->status_code);

  if (iterator == HttpResponse::REASON_PHRASES.end()) {
    // throw an exception
    return;
  }

  pos = input.find("\n");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  // Get the reason phrase
  this->reason_phrase = input.substr(0, pos);

  input = input.substr(pos + 1);

  // Check if the reason phrase of the map is the same
  if (this->reason_phrase !=
      HttpResponse::REASON_PHRASES.at(this->status_code)) {
    // throw an exception
    return;
  }
}

void HttpResponse::parseHeaders(std::string& input) {
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

void HttpResponse::parseHeader(std::string& input) {
  size_t pos = input.find(":");

  if (pos == std::string::npos) {
    // throw an exception
    return;
  }

  std::string key = input.substr(0, pos);

  std::string value = input.substr(pos + 2);

  this->headers.insert({key, value});
}

bool HttpResponse::buildResponse() {
  this->setHeader("Content-Length", std::to_string(this->getBodyLength()));

  this->output = this->toString();

  return true;
}

void HttpResponse::parseHttpResponse(std::string& input) {
  this->input = input;

  this->parse(input);
}

const std::string& HttpResponse::getOutput() {
  this->output = this->toString();

  return this->output;
}
