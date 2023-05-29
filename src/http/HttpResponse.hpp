// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_RESPONSE_HPP_
#define HTTP_RESPONSE_HPP_

#include <map>
#include <string>
#include <sstream>
#include "HttpMessage.hpp"

class HttpResponse : public HttpMessage{
 public:
  /// Statard status codes and their reason phrases according to RFC 7231
  typedef std::map<int, const char*> ReasonPhrases;
  static const ReasonPhrases reasonPhrases;
 protected:
  std::string input;

  std::map<std::string, std::string> headers;

  std::string reasonPhrase;

  std::stringstream body;

  /**
   * @brief e.g: 200 OK, 500 Internal server error,..
   * 
   */
  int statusCode;

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

 public:  // accesors
  inline const std::stringstream& getBody() const { return this->body; }

  inline std::stringstream& getBody() { return this->body; }

 public:
  inline void setHeader(const std::string& key, const std::string& value) {
    this->headers[key] = value;
  }
};

#endif  // HTTP_RESPONSE_HPP_
