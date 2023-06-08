// Copyright © 2023 Camilo Suárez Sandí, Ángel Chaves Chinchilla

#ifndef HTTP_RESPONSE_HPP_
#define HTTP_RESPONSE_HPP_

#include <map>
#include <memory>
#include <sstream>

#include "../net/Socket.hpp"
#include "HttpMessage.hpp"

class HttpResponse : public HttpMessage {
 public:
  /// Standard status codes and their reason phrases according to RFC 7231
  typedef std::map<int, std::string> ReasonPhrases;
  static const ReasonPhrases REASON_PHRASES;

 protected:
  /**
   * @brief The input.
   *
   */
  std::string input;

  // TODO: Remove
  std::string output;

  /**
   * @brief The status code of the response, for example 200.
   *
   */
  size_t status_code = 200;

  /**
   * @brief The phrase of the status code, for example OK if the status code is
   * 200.
   *
   */
  std::string reason_phrase = "OK";

  /**
   * @brief The headers of the http response represented as a map. The key is
   * the name of the header and value will be the value of the header.
   *
   */
  typedef std::map<std::string, std::string> Headers;
  Headers headers;

  /**
   * @brief The body of the response.
   *
   */
  std::shared_ptr<std::stringstream> body;

 public:
  /**
   * @brief Default constructor.
   *
   */
  HttpResponse();

  /**
   * @brief Constructor with the input.
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
  HttpResponse(HttpResponse&& other) = default;

  // Move Assignment Operator
  HttpResponse& operator=(HttpResponse&& other) = default;

 public:
  /**
   * @brief Sets the status code and the reason phrase. Throws an error if it
   * gets an unknown status code.
   *
   * @param status_code
   */
  void setStatusCode(size_t status_code);

  void setHeader(const std::string& key, const std::string& value);

  size_t getStatusCode() const;

  const std::string& getReasonPhrase() const;

  const std::stringstream& getBody() const;

  std::stringstream& getBody();

  size_t getBodyLength() const;

  bool hasHeader(const std::string& key) const;

  const std::string& getHeader(const std::string& key) const;

  std::string toString() const;

 private:
  void parse(std::string& input);

  void parseLine(std::string& input);

  void parseHeaders(std::string& input);

  void parseHeader(std::string& input);

 public:
  // deprecated("Use HttpResponse::toString().")
  bool buildResponse();

  // deprecated("Use the constructor HttpResponse(const std::string&).")
  void parseHttpResponse(std::string& input);

  // deprecated("Use HttpResponse::toString().")
  const std::string& getOutput();
};

#endif  // HTTP_RESPONSE_HPP_
