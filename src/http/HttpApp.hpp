// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_APP_HPP_
#define HTTP_APP_HPP_

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../common/common.hpp"

class HttpApp {
 public:
  /**
   * @brief Default constructor.
   *
   */
  HttpApp();

  /**
   * @brief Destructor.
   *
   */
  ~HttpApp();

  // Copy Constructor
  HttpApp(const HttpApp& other) = delete;

  // Copy Assignment Operator
  HttpApp& operator=(const HttpApp& other) = delete;

  // Move Constructor
  HttpApp(HttpApp&& other) = delete;

  // Move Assignment Operator
  HttpApp& operator=(HttpApp&& other) = delete;

  virtual bool start() = 0;

  virtual bool run(HttpRequest& request, HttpResponse& response) = 0;
};

#endif  // HTTP_APP_HPP_
