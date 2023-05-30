//

#include <signal.h>

#include "app/App.hpp"
#include "error.hpp"
#include "http/HttpServer.hpp"

int main(int argc, char** argv) {
  int error = Error::OK;

  ::signal(SIGINT, HttpServer::onSignal);

  HttpServer* server = HttpServer::getInstance();

  App* app = new App();

  server->addApp(app);

  std::string address = "127.0.0.1";
  int port = 8000;

  error = server->start(address, port);

  if (!error) {
    error = server->run();
  }

  return error;
}
