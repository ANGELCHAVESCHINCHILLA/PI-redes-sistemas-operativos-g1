// Copyright © 2023 Camilo Suárez Sandí

#include "HttpResponse.hpp"

HttpResponse::HttpResponse(const std::string& input) : input(input) {
  //
}

HttpResponse::~HttpResponse() {
}

std::string HttpResponse::buildResponse() {
  this->input += this->buildStatusLine();

   // Send message header
  for (HttpResponse::Headers::const_iterator itr = this->headers.begin();
    itr != this->headers.end(); ++itr) {
    // e.g: "Server: My Web Server"
    this->input += itr->first;
    this->input += ": ";
    this->input += HttpMessage::lineSeparator;
  }

  const std::string& contentType = this->getHeader("Content-Type");

  // Check Content-length was provided
  const std::string& contentLength = this->getHeader("Content-Length");
  if (contentLength.empty()) {
    // No Content-length was set, send the body length
    if (!(this->socket << "Content-Length: " << this->getBodyLength() << sep)) {
      // return false;
    }
  }
}

std::string HttpResponse::buildStatusLine() const {
  return this->httpVersion + ' ' + std::to_string(this->statusCode) + ' '
    + this->reasonPhrase;
}

std::string HttpResponse::getHeader(const std::string& key
  , const std::string& defaultvalue) {
  const Headers::const_iterator& itr = this->headers.find(key);
  return itr != this->headers.end() ? itr->second : defaultvalue;
}

// {Code, "Reason-Phrase"}
const HttpResponse::ReasonPhrases HttpResponse::reasonPhrases = {
  {100, "Continue"},
  {101, "Switching Protocols"},
  {200, "OK"},
  {201, "Created"},
  {202, "Accepted"},
  {203, "Non-Authoritative Information"},
  {204, "No Content"},
  {205, "Reset Content"},
  {206, "Partial Content"},
  {300, "Multiple Choices"},
  {301, "Moved Permanently"},
  {302, "Found"},
  {303, "See Other"},
  {304, "Not Modified"},
  {305, "Use Proxy"},
  {307, "Temporary Redirect"},
  {400, "Bad Request"},
  {401, "Unauthorized"},
  {402, "Payment Required"},
  {403, "Forbidden"},
  {404, "Not Found"},
  {405, "Method Not Allowed"},
  {406, "Not Acceptable"},
  {407, "Proxy Authentication Required"},
  {408, "Request Timeout"},
  {409, "Conflict"},
  {410, "Gone"},
  {411, "Length Required"},
  {412, "Precondition Failed"},
  {413, "Payload Too Large"},
  {414, "URI Too Long"},
  {415, "Unsupported Media Type"},
  {416, "Range Not Satisfiable"},
  {417, "Expectation Failed"},
  {426, "Upgrade Required"},
  {500, "Internal Server Error"},
  {501, "Not Implemented"},
  {502, "Bad Gateway"},
  {503, "Service Unavailable"},
  {504, "Gateway Timeout"},
  {505, "HTTP Version Not Supported"},
};
