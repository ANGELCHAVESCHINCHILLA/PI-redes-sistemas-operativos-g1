// Copyright © 2023 Camilo Suárez Sandí

#include "HttpResponse.hpp"

#include <sstream>

HttpResponse::HttpResponse(const std::string& input) : input(input) {
}

HttpResponse::~HttpResponse() {
}

void HttpResponse::setStatusCode(size_t status_code) {
  this->status_code = status_code;
}

void HttpResponse::setStatusText(const std::string& status_text) {
  this->status_text = status_text;
}

void HttpResponse::setBody(const std::string& body) {
  size_t length = body.length();

  this->body = body;

  this->addHeader("Content-Length", std::to_string(length));
}

std::string HttpResponse::toString() {
  std::stringstream ss;

  ss << HTTP_VERSION << " " << this->status_code << " " << this->status_text
     << "\n";

  for (auto& [key, value] : this->headers) {
    ss << key << ": " << value << "\n";
  }

  ss << "\n";

  ss << this->body;

  return ss.str();
}

void HttpResponse::addHeader(const std::string& key, const std::string& value) {
  this->headers.insert({key, value});
}

void HttpResponse::addBody(const std::string body) {
  size_t length = this->body.length() + body.length();

  this->body += body;

  this->addHeader("Content-Length", std::to_string(length));
}
