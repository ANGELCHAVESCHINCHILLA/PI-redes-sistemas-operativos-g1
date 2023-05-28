// Copyright © 2023 Ángel Chaves Chinchilla

#include "HttpMessage.hpp"

const std::string& HttpMessage::getHttpVersion() const {
  return this->httpVersion;
}
