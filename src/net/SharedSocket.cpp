// Copyright © 2023 Camilo Suárez Sandí

#include "SharedSocket.hpp"

#include <string.h>
#include <unistd.h>

SharedSocket::SharedSocket() {
  ::memset(&this->addr, 0, sizeof(this->addr));
}

SharedSocket::~SharedSocket() {
  this->close();
}

void SharedSocket::close() {
  if (this->fd != -1) {
    ::close(this->fd);

    ::memset(&this->addr, 0, sizeof(this->addr));

    this->fd = -1;
  }
}
