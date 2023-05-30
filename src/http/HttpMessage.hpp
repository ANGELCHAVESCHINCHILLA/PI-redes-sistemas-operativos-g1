// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_MESSAGE_HPP_
#define HTTP_MESSAGE_HPP_

#define HTTP_VERSION "HTTP/1.1"

#include <string>

class HttpMessage {
 private:
 public:
  /**
   * @brief Default constructor.
   *
   */
  HttpMessage();

  /**
   * @brief Destructor.
   *
   */
  ~HttpMessage();

  // Copy Constructor
  HttpMessage(const HttpMessage& other) = delete;

  // Copy Assignment Operator
  HttpMessage& operator=(const HttpMessage& other) = delete;

  // Move Constructor
  HttpMessage(HttpMessage&& other) = delete;

  // Move Assignment Operator
  HttpMessage& operator=(HttpMessage&& other) = delete;

  virtual std::string toString() = 0;
};

#endif  // HTTP_MESSAGE_HPP_
