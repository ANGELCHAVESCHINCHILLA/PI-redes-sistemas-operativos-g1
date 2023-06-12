// Copyright © 2023 Camilo Suárez Sandí

#ifndef EDIT_USER_HANDLER_HPP_
#define EDIT_USER_HANDLER_HPP_

#include "FileSystemRequestHandler.hpp"

class EditUserHandler : public FileSystemRequestHandler {
 public:
  // Constructor
  explicit EditUserHandler(FileSystemAPI* api);

  // Destructor
  ~EditUserHandler();

 private:
  // Copy Constructor
  EditUserHandler(const EditUserHandler&) = delete;

  // Copy Assignment
  EditUserHandler& operator=(const EditUserHandler&) = delete;

  // Move Constructor
  EditUserHandler(EditUserHandler&& other) = delete;

  // Move Assignment
  EditUserHandler& operator=(EditUserHandler&& other) = delete;

 public:
  bool canHandle(HttpRequest& request, HttpResponse& response) override;

 private:
};

#endif  // EDIT_USER_HANDLER_HPP_
