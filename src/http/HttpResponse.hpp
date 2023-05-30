// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_RESPONSE_HPP_
#define HTTP_RESPONSE_HPP_

#include <map>

#include "HttpMessage.hpp"

class HttpResponse : public HttpMessage {
 private:
  std::string input;

  size_t status_code = 200;

  std::string status_text = std::string("OK");

  std::map<std::string, std::string> headers;

  std::string body;

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

  void setStatusCode(size_t status_code);

  void setStatusText(const std::string& status_text);

  void setBody(const std::string& body);

  std::string toString() override;

  void setHeader(const std::string& key, const std::string& value);

  void addBody(const std::string body);
};

#endif  // HTTP_RESPONSE_HPP_
