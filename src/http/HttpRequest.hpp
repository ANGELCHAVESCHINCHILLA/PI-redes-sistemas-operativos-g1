// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_REQUEST_HPP_
#define HTTP_REQUEST_HPP_

#include <map>
// #include <sstream>

#include "HttpMessage.hpp"
#include "../url/URL.hpp"
#include "../common/common.hpp"

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

 public:  // accessors

  inline const std::string& getMethod() const { return this->method; }

  inline const URL& getTarget() const { return this->target; }

  inline const std::string& getBody() const { return this->body; }

  inline bool hasHeader(const std::string& key) const {
    return this->headers.count(key) > 0; }

  inline std::string getHeader(const std::string& key) const {
    return this->headers.at(key); }

 private:
  void parse(std::string& input);

  void parseLine(std::string& input);

  void parseHeaders(std::string& input);

  void parseHeader(std::string& input);
};

#endif  // HTTP_REQUEST_HPP_
