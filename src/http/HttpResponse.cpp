// Copyright © 2023 Camilo Suárez Sandí

#include "HttpResponse.hpp"

#include <iostream>
#include <string_view>
HttpResponse::HttpResponse(const std::string& output)
  : output(output)
  , sharedBody{new std::stringstream()} {
  //
}

HttpResponse::~HttpResponse() {
}

bool HttpResponse::buildResponse() {
  this->output += this->buildStatusLine() + HttpMessage::lineSeparator;

   // put message header
  for (HttpResponse::Headers::const_iterator itr = this->headers.begin();
    itr != this->headers.end(); ++itr) {
    // e.g: "Server: My Web Server\r\n"
    this->output += itr->first;
    this->output += ": ";
    this->output += itr->second;
    this->output += HttpMessage::lineSeparator;
  }

  const std::string& contentType = this->getHeader("Content-Type");
  if (contentType.empty()) {
    // No Content-type was set
    std::cout << "Error en Content-type" << std::endl;
    return false;
  }

  // Check Content-length was provided
  const std::string& contentLength = this->getHeader("Content-Length");
  if (contentLength.empty()) {
    // No Content-length was set
    this->output += "Content-Length: " + std::to_string(this->getBodyLength())
                    + HttpMessage::lineSeparator;
  }

  this->output += HttpMessage::lineSeparator;

  this->output += (*this->sharedBody).str();

  // std::cout << "respuesta generada:\n"<< this->output << std::endl << std::endl;

  return true;
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

bool HttpResponse::setStatusCode(int statusCode,
  const std::string& reasonPhrase) {
  // Accept all given reason phrases
  if (reasonPhrase.length() > 0) {
    this->statusCode = statusCode;
    this->reasonPhrase = reasonPhrase;
    return true;
  }

  // No reason phrase was given, use a standard one
  const ReasonPhrases::const_iterator& itr
    = HttpResponse::reasonPhrases.find(statusCode);

  // If status code is standard
  if (itr != HttpResponse::reasonPhrases.end()) {
    // Use the standard reason phrase
    this->statusCode = statusCode;
    this->reasonPhrase = itr->second;
    return true;
  }

  // Status code is not standard and no reason phrase was provided, reject it
  return false;
}

void HttpResponse::parseHttpResponse(const std::string& response) {
    std::istringstream responseStream(response);

    std::string statusLine;

    // Leer la línea de estado
    std::getline(responseStream, statusLine);

    // Extraer el código de estado
    std::istringstream statusLineStream(statusLine);
    statusLineStream >> this->httpVersion;
    statusLineStream >> this->statusCode;
    statusLineStream >> this->reasonPhrase;

    // Leer los encabezados
    std::string line;
    while (std::getline(responseStream, line) && line != "\r") {
      size_t colonPos = line.find(':');
      if (colonPos != std::string::npos) {
        std::string_view keyView(line.data(), colonPos);
        std::string_view valueView(line.data() + colonPos + 1
          , line.size() - colonPos - 1);
        this->headers.emplace(std::string(keyView), std::string(valueView));
      }
    }

    // Leer el cuerpo de la respuesta
    *this->sharedBody << responseStream.str();
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
