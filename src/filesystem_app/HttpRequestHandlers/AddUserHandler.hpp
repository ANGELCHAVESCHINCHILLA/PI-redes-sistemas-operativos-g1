//
// Created by David Cerdas Alvarado on 01/06/23.
//

#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_ADDUSERHANDLER_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_ADDUSERHANDLER_H

#include "FileSystemRequestHandler.hpp"

class AddUserHandler : public FileSystemRequestHandler {
 public:
  explicit AddUserHandler(FileSystemAPI* fileSystemApi);

  bool canHandle(HttpRequest& request, HttpResponse& response) override;
};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_ADDUSERHANDLER_H
