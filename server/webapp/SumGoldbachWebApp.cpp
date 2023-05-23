// Copyright 2022 Camilo Suarez Sandí, Ángel Chaves Chinchilla

#include "SumGoldbachWebApp.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

SumGoldbachWebApp::SumGoldbachWebApp()
    : calculatorsCount(std::thread::hardware_concurrency()),
      calculators(this->calculatorsCount) {}

void SumGoldbachWebApp::start() {
  // Create the goldbach dispacther with its own queue
  this->createDispatcher();

  // Create the pakcer (an assembler) with its own consuming queue
  this->createPacker(this->dispatcher->getConsumingQueue());

  // Create the calculators team (assemblers) with numsInfo queue as its
  // consuming queue
  this->createCalculators(&this->numsInfo, this->packer->getConsumingQueue());

  // Asserts to know if all the queues are corrects
  assert(this->dispatcher->getConsumingQueue() ==
         this->packer->getProducingQueue());

  for (size_t index = 0; index < this->calculatorsCount; index++) {
    assert(this->packer->getConsumingQueue() ==
           this->calculators[index]->getProducingQueue());
    assert(&this->numsInfo == this->calculators[index]->getConsumingQueue());
  }
}

void SumGoldbachWebApp::createDispatcher() {
  this->dispatcher = new DispatcherGoldbach();
  // Create own consuming queue
  this->dispatcher->createOwnQueue();
  this->dispatcher->startThread();
}

void SumGoldbachWebApp::createPacker(Queue<GoldbachResults*>* producingQueue) {
  this->packer = new Packer();
  // Create own consuming queue
  this->packer->createOwnQueue();
  this->packer->setProducingQueue(producingQueue);
  this->packer->startThread();
}

void SumGoldbachWebApp::createCalculators(Queue<NumInfo>* consumingQueue,
                                          Queue<NumInfo>* producingQueue) {
  assert(consumingQueue);
  assert(producingQueue);

  for (size_t index = 0; index < this->calculatorsCount; index++) {
    this->calculators[index] = new SumGoldbachCalculator();
    this->calculators[index]->setConsumingQueue(consumingQueue);
    this->calculators[index]->setProducingQueue(producingQueue);
    this->calculators[index]->startThread();
  }
}

void SumGoldbachWebApp::stop() {
  this->destroyCalculators();

  this->destroyPacker();

  this->destroyDispatcher();
}

void SumGoldbachWebApp::destroyCalculators() {
  // Push a stop condition to each of the calculator' queues
  for (size_t index = 0; index < this->calculatorsCount; index++) {
    this->calculators[index]->pushStopCondition();
  }

  // Wait for each calculator thread to finish
  for (size_t index = 0; index < this->calculatorsCount; index++) {
    this->calculators[index]->waitToFinish();

    delete this->calculators[index];
  }
}

void SumGoldbachWebApp::destroyPacker() {
  // Push a stop condition to the packer' queue
  this->packer->pushStopCondition();
  // Wait packer thread to finish
  this->packer->waitToFinish();

  delete this->packer;
}

void SumGoldbachWebApp::destroyDispatcher() {
  // Push a stop condition to the packer' queue
  this->dispatcher->pushStopCondition();
  // Wait dispatcher thread to finish
  this->dispatcher->waitToFinish();

  delete this->dispatcher;
}

bool SumGoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
                                          HttpResponse& httpResponse) {
  // Serve the home page of this app
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveStatic(httpRequest, httpResponse, "/public/index.html",
                             "text/html");
  }

  // Serve the page to calculate the Goldbach sums
  if (httpRequest.getURI().rfind("/sum_goldbach") == 0) {
    return this->serveSumGoldbach(httpRequest, httpResponse);
  }

  return false;
}

bool SumGoldbachWebApp::serveSumGoldbach(HttpRequest& httpRequest,
                                         HttpResponse& httpResponse) {
  httpResponse.setHeader("Content-Type", "text/html; charset=utf8");

  // Read the numbers from URL
  std::vector<int_t> numbers =
      SumGoldbachWebApp::readNumbers(httpRequest.getURI(), this->can_use_regex);

  if (numbers.empty()) {
    // If there are no numbers then send an HTML form to read the numbers
    SumGoldbachWebApp::readFile(httpResponse.body(),
                                "/public/sum_goldbach.html");

    return httpResponse.send();
  } else {
    // the shared data for this request
    GoldbachResults* goldbachResults =
        new GoldbachResults(numbers, httpResponse);

    for (size_t index = 0; index < numbers.size(); ++index) {
      NumInfo currentNumInfo(index, goldbachResults);

      this->numsInfo.push(currentNumInfo);
    }

    return true;
  }
}

std::vector<int_t> SumGoldbachWebApp::readNumbers(std::string url,
                                                  std::mutex& can_use_regex) {
  // Find the key "numbers"
  std::string key = "numbers=";

  size_t pos = url.find(key);

  // Return an empty array if it can't find the key "numbers"
  if (pos == std::string::npos) {
    return {};
  }

  pos += key.size();

  url = url.substr(pos);

  std::smatch matches;

  can_use_regex.lock();
  // Regex to find numbers
  std::regex regex("\\-?\\d+");
  can_use_regex.unlock();

  std::vector<int_t> numbers;

  // Search the numbers
  while (std::regex_search(url, matches, regex)) {
    // Add the numbers
    for (std::string match : matches) {
      int_t number = std::stoi(match);

      numbers.push_back(number);
    }

    url = matches.suffix().str();
  }

  return numbers;
}

void SumGoldbachWebApp::readFile(std::ostream& output,
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

bool SumGoldbachWebApp::serveStatic(HttpRequest& httpRequest,
                                    HttpResponse& httpResponse,
                                    const std::string& path,
                                    const std::string& contentType) {
  (void)httpRequest;

  // Set the content type and the character encoding
  httpResponse.setHeader("Content-Type", contentType + "; charset=utf8");

  // Read the file and write the text in the HTTP response
  SumGoldbachWebApp::readFile(httpResponse.body(), path);

  return httpResponse.send();
}
