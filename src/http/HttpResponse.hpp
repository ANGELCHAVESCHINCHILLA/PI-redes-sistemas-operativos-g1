// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_RESPONSE_HPP_
#define HTTP_RESPONSE_HPP_

#include <string>
#include "HttpMessage.hpp"

class HttpResponse : public HttpMessage{
 private:
  std::string input;

 public:
  /**
   * @brief Default constructor.
   *
   */
  explicit HttpResponse(const std::string& input);

  /**
   * @brief Destructor.
   *
   */
  ~HttpResponse();

  // Copy Constructor
  HttpResponse(const HttpResponse& other) = delete;

  // Copy Assignment Operator
  HttpResponse& operator=(const HttpResponse& other) = delete;

  // Move Constructor
  HttpResponse(HttpResponse&& other) = delete;

  // Move Assignment Operator
  HttpResponse& operator=(HttpResponse&& other) = delete;
};

#endif  // HTTP_RESPONSE_HPP_
