// Copyright © 2023 Camilo Suárez Sandí

#include "App.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#define DEFAULT_CONTENT_TYPE "application/octet-stream"

std::map<std::string, std::string> App::CONTENT_TYPE_MAP = {
    { ".txt",       "text/plain"},
    {".html",        "text/html"},
    { ".css",         "text/css"},
    {  ".js",  "text/javascript"},
    { ".xml",  "application/xml"},
    {".json", "application/json"},
    { ".png",        "image/png"},
};

App::App() {
}

App::~App() {
}

bool App::run(const HttpRequest& request, HttpResponse& response) {
  if (request.getMethod() == "GET") {
    if (request.getTarget().getPath() == "/") {
      if (this->servePage(request, response, "index.html")) {
        return true;
      }
    }

    if (this->serveStatic(request, response)) {
      return true;
    }
  }

  if (this->serveNotFoundPage(request, response)) {
    return true;
  }

  return false;
}

std::string App::readFileToString(const std::string& relative_path) const {
  std::filesystem::path path = std::filesystem::current_path();

  if (path.parent_path().stem() == "build") {
    path = path.parent_path();
  }

  path /= relative_path;

  std::ifstream file(path);

  if (!file) {
    std::cerr << "Error reading a file: " << path << ".\n";
    // throw an exception
    return "";
  }

  auto iterator_1 = std::istreambuf_iterator<char>(file);
  auto iterator_2 = std::istreambuf_iterator<char>();

  std::string string(iterator_1, iterator_2);

  file.close();

  return std::move(string);
}

bool App::servePage(const HttpRequest& request, HttpResponse& response,
    const std::string& path) const {
  std::string body = this->readFileToString("pages/" + path);

  if (body.empty()) {
    return false;
  }

  response.setStatusCode(200);
  response.setStatusText("OK");
  response.setBody(body);
  response.setHeader("Content-Type", "text/html; charset=utf8");

  return true;
}

bool App::serveNotFoundPage(
    const HttpRequest& request, HttpResponse& response) const {
  std::string body = this->readFileToString("pages/not_found.html");

  if (body.empty()) {
    return false;
  }

  response.setStatusCode(404);
  response.setStatusText("Not Found");
  response.setBody(body);
  response.setHeader("Content-Type", "text/html; charset=utf8");

  return true;
}

bool App::serveStatic(
    const HttpRequest& request, HttpResponse& response) const {
  std::string path = request.getTarget().getPath();

  std::string body = this->readFileToString("public/" + path);

  if (body.empty()) {
    return false;
  }

  response.setStatusCode(200);
  response.setStatusText("OK");
  response.setBody(body);
  response.setHeader(
      "Content-Type", App::getContentType(request, path) + "; charset=utf8");

  return true;
}

std::string App::getContentType(
    const HttpRequest& request, const std::string& path) const {
  if (request.hasHeader("Content-Type")) {
    return request.getHeader("Content-Type");
  }

  std::string extension = std::filesystem::path(path).extension().string();

  if (App::CONTENT_TYPE_MAP.count(extension) > 0) {
    return App::CONTENT_TYPE_MAP[extension];
  }

  return DEFAULT_CONTENT_TYPE;
}
