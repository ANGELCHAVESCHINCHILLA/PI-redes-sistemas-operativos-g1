// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_RESPONSE_HPP_
#define HTTP_RESPONSE_HPP_

class HttpResponse {
 private:
 public:
  /**
   * @brief Default constructor.
   *
   */
  HttpResponse();

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
