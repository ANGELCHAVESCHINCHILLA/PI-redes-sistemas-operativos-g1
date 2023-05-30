// Copyright © 2023 Camilo Suárez Sandí

#include "App.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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
  response.addHeader("Content-Type", "text/html; charset=utf8");

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
  response.addHeader("Content-Type", "text/html; charset=utf8");

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
  response.addHeader(
      "Content-Type", App::getContentType(path) + "; charset=utf8");

  return true;
}

std::string App::getContentType(const std::string& path) const {
  std::string extension = std::filesystem::path(path).extension().string();

  if (extension == ".txt") {
    return "text/plain";
  } else if (extension == ".html") {
    return "text/html";
  } else if (extension == ".css") {
    return "text/css";
  } else if (extension == ".js") {
    return "text/javascript";
  } else if (extension == ".xml") {
    return "application/xml";
  } else if (extension == ".json") {
    return "application/json";
  } else if (extension == ".png") {
    return "image/png";
  }

  return "text/plain";
}
