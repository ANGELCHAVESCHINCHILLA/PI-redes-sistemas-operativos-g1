//
// Created by daviddev on 01/06/23.
//

#ifndef PI_REDES_SISTEMAS_OPERATIVOS_G1_GETPERMISSIONSHANDLER_H
#define PI_REDES_SISTEMAS_OPERATIVOS_G1_GETPERMISSIONSHANDLER_H

#include "FileSystemequestHandler.hpp"
#include "iostream"
#include "string"
class PermissionsHandler : public FileSystemRequestHandler{
 public:
  /// Constructor
  PermissionsHandler(FileSystemAPI* fileSystemApi) :
        FileSystemRequestHandler(fileSystemApi) {};
  bool canHandle(HttpRequest& request, HttpResponse& response) override {

    if (request.getMethod() == "GET" && request.getTarget().getPath() == "/permissions") {

      std::string username = request.getTarget().getQuery().find("username")->second;
      std::cout << username << std::endl;
      int type = this->fileSystemApi->getUserType(username);
      response.setHeader("Content-Type", "text/plain");
      response.setStatusCode(200);
      response.getBody() << type;
      response.buildResponse();
      return true;
    }
    return false;
  }

};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_G1_GETPERMISSIONSHANDLER_H