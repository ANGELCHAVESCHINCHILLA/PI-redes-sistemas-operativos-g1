// Copyright © 2023 Ángel Chaves Chinchilla
#ifndef HTTP_MESSAGE_HPP_
#define HTTP_MESSAGE_HPP_

#include <string>

class HttpMessage {
 public:
  /// Line separators for HTTP messages is "\r\n"
  static const char* const lineSeparator;

 protected:
  std::string httpVersion = "HTTP/1.0";

 public:
  HttpMessage() = default;

 public:
  const std::string& getHttpVersion() const;
};

#endif  // HTTP_MESSAGE_HPP_
