// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suarez Sandí

#include "GuachisWebApp.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

GuachisWebApp::GuachisWebApp() {}

GuachisWebApp::~GuachisWebApp() {}


bool GuachisWebApp::start() {
  //

  return true;
}

bool GuachisWebApp::run(HttpRequest& request, HttpResponse& response) {
  // Serve the home page of this app
  if (request.getMethod() == "GET" && request.getTarget().getPath() == "/") {
    return this->serveStatic(request, response, "/web/pages/index.html",
                             "text/html");
  }

  return false;
}

bool GuachisWebApp::serveStatic(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse,
                                    const std::string& path,
                                    const std::string& contentType) {
  (void)httpRequest;

  // Set the content type and the character encoding
  httpResponse.setStatusCode(200);
  httpResponse.setHeader("Content-Type", contentType + "; charset=ascii");
  httpResponse.setHeader("Server", "AttoServer v1.0");

  // Read the file and write the text in the HTTP response
  GuachisWebApp::readFile(httpResponse.getBody(), path);

  return httpResponse.buildResponse();
}

void GuachisWebApp::readFile(std::ostream& output,
                                 const std::string& path) {
  // Get the path of the project directory
  std::filesystem::path current_path = std::filesystem::current_path();

  // Add the file path to the path of the project directory
  current_path += path;

  // Read the file in the path
  std::ifstream file;

  file.open(current_path);

  if (file.is_open()) {
    // Read every character and write it to the output stream.
    char c = '\0';

    while (file.get(c)) {
      output << c;
    }
  }

  file.close();
}