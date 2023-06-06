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

bool HttpRequestHandler::serveStatic(const HttpRequest& request
    , HttpResponse& response) {

  bool couldServe = false;
    
  std::string path = request.getTarget().getPath();

  std::cout << "Path generada: "<< path << std::endl;

  bool fileOpen = HttpRequestHandler::readFile(response.getBody()
                  , "public/" + path);

  if (fileOpen) {
    response.setStatusCode(200);
    response.setHeader(
        "Content-Type", HttpRequestHandler::getContentType(request, path)
        + "; charset=utf8");
    response.setHeader("Server", "AttoServer v1.0");
    couldServe = response.buildResponse();
  } else {
    std::cout << "no logr[e abrir el archiv]" << std::endl;
    couldServe = false;
  }

  return couldServe;
}

bool HttpRequestHandler::serveAny(HttpResponse& response, int statusCode
  , std::string contentType, const std::string& body) {
  response.setStatusCode(statusCode);
  response.setHeader("Content-Type", contentType);
  response.setHeader("Server", "AttoServer v1.0");
  response.getBody().str(body);
  return response.buildResponse();
}
bool HttpRequestHandler::servePage(const HttpRequest& request, HttpResponse& response,
    const std::string& path) {
  bool fileOpen = HttpRequestHandler::readFile(response.getBody()
                  , "pages/" + path);

  response.setStatusCode(200);
  response.setHeader("Content-Type", "text/html; charset=utf8");
  response.setHeader("Server", "AttoServer v1.0");

  return response.buildResponse();
}


bool HttpRequestHandler::readFile(std::ostream& output
    , const std::string& relative_path) {
  std::filesystem::path path = std::filesystem::current_path();

  if (path.stem() == "build") {
    path = path.parent_path();
  }

  path /= relative_path;

  std::cout << path << std::endl;

  std::ifstream file(path);

  if (!file) {
    std::cout << "No encontr[e el archivo]";
    return false;
  }

  // Read every character and write it to the output stream.
  char c = '\0';

  while (file.get(c)) {
    output << c;
  }

  file.close();

  return true;
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