// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suárez Sandí

#include "./HttpRequestHandler.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#define DEFAULT_CONTENT_TYPE "application/octet-stream"

std::map<std::string, std::string> HttpRequestHandler::CONTENT_TYPE_MAP = {
    { ".txt",       "text/plain"},
    {".html",        "text/html"},
    { ".css",         "text/css"},
    {  ".js",  "text/javascript"},
    { ".xml",  "application/xml"},
    {".json", "application/json"},
    { ".png",        "image/png"},
};

bool HttpRequestHandler::serveStatic(HttpRequest& httpRequest,
                                HttpResponse& httpResponse,
                                const std::string& path,
                                const std::string& contentType,
                                const std::string& charset) {
  (void)httpRequest;

  // Set the content type and the character encoding
  httpResponse.setStatusCode(200);
  httpResponse.setHeader("Content-Type", contentType + "; charset=" + charset);
  httpResponse.setHeader("Server", "AttoServer v1.0");

  // Read the file and write the text in the HTTP response
  HttpRequestHandler::readFile(httpResponse.getBody(), path);

  return httpResponse.buildResponse();
}

bool HttpRequestHandler::serveStatic(const HttpRequest& request
    , HttpResponse& response) {
  std::string path = request.getTarget().getPath();

  HttpRequestHandler::readFile(response.getBody(), "public/" + path);

  response.setStatusCode(200);
  response.setHeader(
      "Content-Type", HttpRequestHandler::getContentType(request, path)
      + "; charset=utf8");
  response.setHeader("Server", "AttoServer v1.0");

  return response.buildResponse();
}

bool HttpRequestHandler::servePage(const HttpRequest& request, HttpResponse& response,
    const std::string& path) {
  HttpRequestHandler::readFile(response.getBody(), "pages/" + path);

  response.setStatusCode(200);
  response.setHeader("Content-Type", "text/html; charset=utf8");
  response.setHeader("Server", "AttoServer v1.0");

  return response.buildResponse();
}

void HttpRequestHandler::readFile(std::ostream& output
    , const std::string& relative_path) {
  std::filesystem::path path = std::filesystem::current_path();

  if (path.stem() == "build") {
    path = path.parent_path();
  }

  path /= relative_path;

  std::ifstream file(path);

  if (!file) {
    std::string errorMessage = "Error reading a file: " + path.string() + "\n";
    throw std::runtime_error(errorMessage);
  }

  // Read every character and write it to the output stream.
  char c = '\0';

  while (file.get(c)) {
    output << c;
  }

  file.close();
}

std::string HttpRequestHandler::getContentType(
    const HttpRequest& request, const std::string& path) {
  if (request.hasHeader("Content-Type")) {
    return request.getHeader("Content-Type");
  }

  std::string extension = std::filesystem::path(path).extension().string();

  if (HttpRequestHandler::CONTENT_TYPE_MAP.count(extension) > 0) {
    return HttpRequestHandler::CONTENT_TYPE_MAP[extension];
  }

  return DEFAULT_CONTENT_TYPE;
}