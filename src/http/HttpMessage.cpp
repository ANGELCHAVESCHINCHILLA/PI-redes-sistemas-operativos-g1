// Copyright © 2023 Ángel Chaves Chinchilla

#include "HttpMessage.hpp"

const char* const HttpMessage::lineSeparator = "\r\n";

const std::string& HttpMessage::getHttpVersion() const {
  return this->httpVersion;
}
