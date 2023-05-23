// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

/**
 * @mainpage
 * Concurrent web server with a web application in charge of looking up
 * goldbach sums
 *
 * Important files:
 * 
 * - @a HttpServer.hpp: web server controller class
 * - @a HttpConnHandler.hpp: class that helps concurrency by serving requests from different sockets
 * - @a SumGoldbachWebApp.hpp: web application in charge of goldbach sums
 */

#ifdef WEBSERVER

#include <csignal>

#include "HttpServer.hpp"
#include "SumGoldbachWebApp.hpp"

/// Start the web server
int main(int argc, char* argv[]) {
  // Register the ctrl + c and kill signals for program termination
  std::signal(SIGTERM, HttpServer::stopServer);
  std::signal(SIGINT, HttpServer::stopServer);

  // Create the sum goldbach web app
  SumGoldbachWebApp sumGoldbachWebApp;

  // Register the web application(s) with the web server
  HttpServer::getInstance().chainWebApp(&sumGoldbachWebApp);

  // Start the web server
  return HttpServer::getInstance().start(argc, argv);
}

#endif  // WEBSERVER
