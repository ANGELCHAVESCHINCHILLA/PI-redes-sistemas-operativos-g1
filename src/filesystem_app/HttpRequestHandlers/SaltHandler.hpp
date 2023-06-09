// Copyright © 2023 Camilo Suárez Sandí

#ifndef SALT_HANDLER_HPP_
#define SALT_HANDLER_HPP_

#include "FileSystemRequestHandler.hpp"

class SaltHandler : public FileSystemRequestHandler {
 public:
  // Constructor
  explicit SaltHandler(FileSystemAPI* api);

  // Destructor
  ~SaltHandler();

 private:
  // Copy Constructor
  SaltHandler(const SaltHandler&) = delete;

  // Copy Assignment
  SaltHandler& operator=(const SaltHandler&) = delete;

  // Move Constructor
  SaltHandler(SaltHandler&& other) = delete;

  // Move Assignment
  SaltHandler& operator=(SaltHandler&& other) = delete;

 public:
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

 private:
};

#endif  // SALT_HANDLER_HPP_
