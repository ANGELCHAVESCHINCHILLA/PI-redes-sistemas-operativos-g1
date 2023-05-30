// Copyright © 2023 Camilo Suárez Sandí

#ifndef HTTP_REQUEST_HPP_
#define HTTP_REQUEST_HPP_

#include <map>

#include "../url/URL.hpp"
#include "HttpMessage.hpp"

class HttpRequest : public HttpMessage {
 private:
  std::string input;

  std::string method;

  URL target;

  std::map<std::string, std::string> headers;

  std::string body;

 public:
  /**
   * @brief Default constructor.
   *
   */
  explicit HttpRequest(const std::string& input);

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

  const std::string& getMethod() const;

  const URL& getTarget() const;

  const std::string& getBody() const;

  std::string toString() override;

 private:
  void parse(std::string& input);

  void parseLine(std::string& input);

  void parseHeaders(std::string& input);

  void parseHeader(std::string& input);
};

#endif  // HTTP_REQUEST_HPP_
