//

#include "Log.hpp"

#include <cassert>
#include <stdexcept>

#include "Util.hpp"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

/// The respective texts for the message types
const char* const Log::MESSAGE_TYPE_TEXT[] = {
    "Debug",
    "Info",
    "Warning",
    "Error",
};

const char* const Log::MESSAGE_TYPE_COLOR[] = {
    BLUE,
    GREEN,
    YELLOW,
    RED,
};

Log& Log::getInstance() {
  static Log log;
  return log;
}

Log::Log() : output{std::cout.rdbuf()} {
}

void Log::start(const std::string& logFilename) {
  // If filename is empty, use stdout
  if (logFilename.empty()) {
    // Adapted from https://stackoverflow.com/a/366969
    this->output.rdbuf(std::cout.rdbuf());
    this->filename = "(stdout)";
  } else {
    assert(this->file.is_open() == false);
    this->file.open(logFilename, std::ios::app);
    if (!this->file) {
      throw std::runtime_error(
          "could not open log file for appending: " + logFilename);
    }
    this->filename = logFilename;
    this->output.rdbuf(std::cout.rdbuf());
  }
}

void Log::stop() {
  this->file.close();
}

void Log::write(Log::MessageType type, const std::string& category,
    const std::string& text) {
  this->mutex.lock();

  std::string time = getActualTime();

  std::string console_log = "[" + time + "] " + MESSAGE_TYPE_COLOR[type] +
    "[" + MESSAGE_TYPE_TEXT[type] + "]" + RESET + "\t" + category + "\t\t" + text;
  std::string file_log = "[" + time + "] [" + MESSAGE_TYPE_TEXT[type] +
    "]\t" + category + "\t\t" + text;

  this->output << console_log << std::endl;

  if(this->file.is_open()) {
    this->file << file_log << std::endl;
  }

  bool error = !this->output;

  this->mutex.unlock();

  if (error) {
    throw std::runtime_error("could not write log file: " + this->filename);
  }
}

std::string Log::getActualTime() {
  time_t actualTime = time(0);

  struct tm* localTime = localtime(&actualTime);

  int hour = localTime->tm_hour;
  int mins = localTime->tm_min;
  int secs = localTime->tm_sec;

  std::string formatHour = std::to_string(hour);
  std::string formatMins = std::to_string(mins);
  std::string formatSecs = std::to_string(secs);

  Util::padLeft(formatHour, 2, '0');
  Util::padLeft(formatMins, 2, '0');
  Util::padLeft(formatSecs, 2, '0');

  return formatHour + ":" + formatMins + ":" + formatSecs;
}
