// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "HttpServer.hpp"

#include <cassert>
#include <csignal>
#include <stdexcept>
#include <string>

#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
    "Usage: webserv [port] [handlers]\n"
    "\n"
    "  port        Network port to listen incoming HTTP requests, "
    "default " DEFAULT_PORT
    "\n"
    "  handlers     Number of connection handler theads\n";

HttpServer::HttpServer() {}

HttpServer::~HttpServer() {}

HttpServer& HttpServer::getInstance() {
    static HttpServer server;
    return server;
  }

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  this->clients.push(client);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}

void HttpServer::createHttpConnHandlers() {
  this->handlers.resize(this->handlersCount);
  for (size_t index = 0; index < this->handlersCount; index++) {
    this->handlers[index] = new HttpConnHandler(this->applications);
    this->handlers[index]->setConsumingQueue(&this->clients);
    this->handlers[index]->startThread();
  }
}

void HttpServer::destroyHttpConnHandlers() {
  // Push a stop condition to each of the handlers' queues
  for (size_t index = 0; index < this->handlersCount; index++) {
    this->handlers[index]->pushStopCondition();
  }

  // Wait for each handler thread to finish
  for (size_t index = 0; index < this->handlersCount; index++) {
    this->handlers[index]->waitToFinish();
    delete this->handlers[index];
  }
}

int HttpServer::start(int argc, char* argv[]) {
  bool stopApps = false;
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      Log::getInstance().start();

      this->handlersCount = std::thread::hardware_concurrency();

      this->createHttpConnHandlers();

      // Start all web applications
      for (size_t index = 0; index < this->applications.size(); ++index) {
        this->applications[index]->start();
      }
      stopApps = true;

      // Start waiting for connections
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver",
                  "Listening on " + address.getIP() + " port " +
                      std::to_string(address.getPort()));

      // Accept all client connections
      this->acceptAllConnections();
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  // Destroy all HttpConnHandlers
  this->destroyHttpConnHandlers();

  // If applications were started
  if (stopApps) {
    // Stop web applications. Give them an opportunity to clean up
    for (size_t index = 0; index < this->applications.size(); ++index) {
      this->applications[index]->stop();
    }
  }

  // Stop the log service
  Log::getInstance().stop();

  return EXIT_SUCCESS;
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
  }

  return true;
}

void HttpServer::stopServer(int signal) {
  std::cerr << "Signal " << signal << " received" << std::endl;
  HttpServer::getInstance().stop();
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests
  this->stopListening();
}
