// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_REQUEST_HPP_
#define HTTP_REQUEST_HPP_

#include <map>

#include "../common/common.hpp"
#include "../url/URL.hpp"
#include "HttpMessage.hpp"

typedef std::map<std::string, std::string> Headers;

class HttpRequest : public HttpMessage {
 protected:
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

  std::string toString();

  // used for send a http request
  std::string buildString();

 public:
  // Getters and Setters

  void setMethod(const std::string& method);

  void setTarget(const std::string& target);

  void setTarget(const URL& target);

  void addHeader(const std::string& key, const std::string& value);

  void setBody(const std::string& body);

  const std::string& getMethod() const;

  const URL& getTarget() const;

  const std::string& getBody() const;

  bool hasHeader(const std::string& key) const;

  std::string getHeader(const std::string& key) const;

 private:
  void parse(std::string& input);

  void parseLine(std::string& input);

  void parseHeaders(std::string& input);

  void parseHeader(std::string& input);
};

#endif  // HTTP_REQUEST_HPP_
