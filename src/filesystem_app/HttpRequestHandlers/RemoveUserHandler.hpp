// Copyright © 2023 Camilo Suárez Sandí

#ifndef REMOVE_USER_HANDLER_HPP_
#define REMOVE_USER_HANDLER_HPP_

#include "FileSystemRequestHandler.hpp"

class RemoveUserHandler : public FileSystemRequestHandler {
 public:
  // Constructor
  explicit RemoveUserHandler(FileSystemAPI* api);

  // Destructor
  ~RemoveUserHandler();

 private:
  // Copy Constructor
  RemoveUserHandler(const RemoveUserHandler&) = delete;

  // Copy Assignment
  RemoveUserHandler& operator=(const RemoveUserHandler&) = delete;

  // Move Constructor
  RemoveUserHandler(RemoveUserHandler&& other) = delete;

  // Move Assignment
  RemoveUserHandler& operator=(RemoveUserHandler&& other) = delete;

 public:
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

 private:
};

#endif  // REMOVE_USER_HANDLER_HPP_
