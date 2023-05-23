// Copyright 2022 Ángel Chaves Chinchilla

#include "DispatcherGoldbach.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

int DispatcherGoldbach::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void DispatcherGoldbach::consume(GoldbachResults* data) {
  this->serveSumGoldbach(data);
  // TODO(EquipoDeDesarrollo): Ver por qué genera condiciones de carrera este
  // delete
  delete data;
}

bool DispatcherGoldbach::serveSumGoldbach(GoldbachResults* goldbachResults) {
  // Set the content type and the character encoding
  // goldbachResults->httpResponse.setHeader("Content-Type"
  //   , "text/html; charset=utf8");

  if (goldbachResults->numbers.empty()) {
    // If there are no numbers then send an HTML form to read the numbers
    DispatcherGoldbach::readFile(goldbachResults->httpResponse.body(),
                                 "/public/sum_goldbach.html");
  } else {
    // Write the numbers and the Goldbach sums of the numbers
    goldbachResults->httpResponse.body()
        << "<!DOCTYPE html>\n"
           "<html>\n"
           "<head>\n"
           "<meta charset=\"utf8\">\n"
           "<title>Sum Goldbach</title>\n"
           "<link rel=\"stylesheet\" "
           "href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.4.1/dist/css/"
           "bootstrap.min.css\" "
           "integrity=\"sha384-HSMxcRTRxnN+Bdg0JdbxYKrThecOKuH5zCYotlSAcp1+"
           "c8xmyTe9GYg1l9a69psu\" crossorigin=\"anonymous\">"
           "</head>\n"
           "<body>\n"
           "<div class=\"container-fluid\">\n"
           "<h1>Sum Goldbach</h1>\n"
           "<div class=\"container-fluid\">\n";

    this->writeGoldbachSums(goldbachResults->httpResponse.body(),
                            goldbachResults);

    goldbachResults->httpResponse.body()
        << "<a class=\"btn btn-default\" href=\"/sum_goldbach\" "
           "role=\"button\">Go back</a>"
           "</div>\n"
           "</div>\n"
           "</body>\n"
           "</html>\n";
  }

  return goldbachResults->httpResponse.send();
}

void DispatcherGoldbach::readFile(std::ostream& os, std::string path) {
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
      os << c;
    }
  }

  file.close();
}

void DispatcherGoldbach::writeGoldbachSums(
    std::ostream& os, const GoldbachResults* goldbachResults) {
  size_t length = goldbachResults->numbers.size();

  int_t allSumsCount = 0;

  for (int_t count : goldbachResults->counts) {
    allSumsCount += count;
  }

  // Write the amount of numbers and the amount of sums
  os << "<h2>";
  os << "Total " << length << " numbers " << allSumsCount << " sums";
  os << "</h2>\n";

  //

  os << "<table class=\"table table-striped table-hover table-bordered\">\n"
        "<tbody>\n";

  // Iterate the numbers
  for (size_t index = 0; index < length; index++) {
    int_t number = goldbachResults->numbers[index];

    // Write the number
    os << "<tr>\n"
          "<td>";
    os << number;
    os << "</td>\n";

    if (number >= -5 && number <= 5 && number != 4 && number != -4) {
      // If the absolute value of the number is less than 5 but it is not 4 then
      // the number has no sums
      os << "<td>";
      os << "NA";
      os << "</td>\n";
    } else {
      int_t count = goldbachResults->counts[index];

      os << "<td>";
      if (count == 1) {
        os << count << " sum";
      } else {
        os << count << " sums";
      }
      os << "</td>\n";

      if (number < 0) {
        os << "<td>\n";
        os << "<div style=\"max-height: 256px; overflow: auto\">\n";

        if (number % 2 == 0) {
          // If the number is even
          this->writeGoldbachSumsEven(os, goldbachResults->sums[index]);
        } else {
          // If the number is odd
          this->writeGoldbachSumsOdd(os, goldbachResults->sums[index]);
        }

        os << "</div>\n";
        os << "</td>\n";
      } else {
        os << "<td>"
              "</td>\n";
      }
    }

    os << "</tr>\n";
  }

  os << "</tbody>\n"
        "</table>\n";
}

void DispatcherGoldbach::writeGoldbachSumsEven(std::ostream& os,
                                               const std::vector<int_t>& sum) {
  size_t length = sum.size();

  // Every even number has two addends so iterate every two numbers
  for (size_t index = 0; index < length; index += 2) {
    os << "<div>";
    os << sum[index] << " + " << sum[index + 1];
    os << "</div>\n";
  }
}

void DispatcherGoldbach::writeGoldbachSumsOdd(std::ostream& os,
                                              const std::vector<int_t>& sum) {
  size_t length = sum.size();

  // Every odd number has three addends so iterate every three numbers
  for (size_t index = 0; index < length; index += 3) {
    os << "<div>";
    os << sum[index] << " + " << sum[index + 1] << " + " << sum[index + 2];
    os << "</div>\n";
  }
}

void DispatcherGoldbach::pushStopCondition() {
  this->consumingQueue->push(nullptr);
}
