// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#include "PersonalDataHandler.hpp"

bool PersonalDataHandler::canHandle(
    HttpRequest& request, HttpResponse& response) {
  if (request.getTarget().getPath() == "/data/personal_data") {
    if (request.getMethod() == "GET") {
      if (this->getJobData(request, response)) {
        return true;
      }
    }

    if (request.getMethod() == "POST") {
      if (this->addJobData(request, response)) {
        return true;
      }
    }

    if (request.getMethod() == "DELETE") {
      if (this->removeJobData(request, response)) {
        return true;
      }
    }

    if (request.getMethod() == "PUT") {
      if (this->editJobData(request, response)) {
        return true;
      }
    }
  }

  return false;
}

bool PersonalDataHandler::getJobData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool PersonalDataHandler::addJobData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool PersonalDataHandler::removeJobData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}

bool PersonalDataHandler::editJobData(
    HttpRequest& request, HttpResponse& response) {
  Json::Reader reader;
  Json::StreamWriterBuilder writer;

  Json::Value input;
  Json::Value output(Json::objectValue);

  try {
    reader.parse(request.getBody(), input);
  } catch (const std::runtime_error& error) {
    response.setStatusCode(401);
  }

  return true;
}
