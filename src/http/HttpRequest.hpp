// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_REQUEST_HPP_
#define HTTP_REQUEST_HPP_

class HttpRequest {
 private:
 public:
  /**
   * @brief Default constructor.
   *
   */
  HttpRequest();

  /**
   * @brief Destructor.
   *
   */
  ~HttpRequest();

  // Copy Constructor
  HttpRequest(const HttpRequest& other) = delete;

  // Copy Assignment Operator
  HttpRequest& operator=(const HttpRequest& other) = delete;

  // Move Constructor
  HttpRequest(HttpRequest&& other) = delete;

  // Move Assignment Operator
  HttpRequest& operator=(HttpRequest&& other) = delete;
};

#endif  // HTTP_REQUEST_HPP_
