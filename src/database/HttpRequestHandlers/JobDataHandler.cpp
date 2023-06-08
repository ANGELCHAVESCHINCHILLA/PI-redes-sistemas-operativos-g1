// Copyright © 2023 Ignacio Robles Mayorga, Camilo Suárez Sandí

#include "JobDataHandler.hpp"

bool JobDataHandler::canHandle(HttpRequest& request, HttpResponse& response) {
  if (request.getTarget().getPath() == "/data/job_data") {
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

bool JobDataHandler::getJobData(HttpRequest& request, HttpResponse& response) {
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

bool JobDataHandler::addJobData(HttpRequest& request, HttpResponse& response) {
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

bool JobDataHandler::removeJobData(
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

bool JobDataHandler::editJobData(HttpRequest& request, HttpResponse& response) {
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
