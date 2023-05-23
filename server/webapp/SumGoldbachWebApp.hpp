// Copyright 2022 Camilo Suarez Sandí, Ángel Chaves Chinchilla

#ifndef SUM_GOLDBACH_WEB_APP_HPP_
#define SUM_GOLDBACH_WEB_APP_HPP_

#include <mutex>
#include <string>
#include <vector>

#include "DispatcherGoldbach.hpp"
#include "HttpApp.hpp"
#include "Packer.hpp"
#include "SumGoldbachCalculator.hpp"
#include "common.hpp"

/**
 * @brief An HTTP web app that calculates Goldbach sums.
 *
 */
class SumGoldbachWebApp : public HttpApp {
 private:
  /**
   * @brief A mutex to control the access to the regex.
   *
   */
  std::mutex can_use_regex;

  /**
   * @brief The amount of calculators, it's always equal to the amount of cores.
   *
   */
  size_t calculatorsCount;

  /**
   * @brief An array that stores the calculators.
   *
   */
  std::vector<SumGoldbachCalculator*> calculators;

  /**
   * @brief Consuming queue of the calculators.
   *
   */
  Queue<NumInfo> numsInfo;

  /**
   * @brief A packer that waits to send the calculator results until all of the
   * numbers requested by the client have been calculated.
   *
   */
  Packer* packer;

  /**
   * @brief Sends the calculators results to the client in HTML text.
   *
   */
  DispatcherGoldbach* dispatcher;

 public:
  /**
   * @brief Default constructor.
   *
   */
  SumGoldbachWebApp();

  /**
   * @brief Destructor.
   *
   */
  ~SumGoldbachWebApp() = default;

  DISABLE_COPY(SumGoldbachWebApp);

  /**
   * @brief Override from HtppApp, starts the app creating calculators,
   * assemblers, ...
   *
   */
  void start() override;

  /**
   * @brief Creates the dispatcher attribute.
   *
   */
  void createDispatcher();

  /**
   * @brief Creates the packer attribute.
   *
   * @param producingQueue The consuming queue of the dispatcher.
   */
  void createPacker(Queue<GoldbachResults*>* producingQueue);

  /**
   * @brief Creates the array of calculators.
   *
   * @param consumingQueue The queue of the calculators with the information
   * about the numbers.
   * @param producingQueue The consuming queue of the packer.
   */
  void createCalculators(Queue<NumInfo>* consumingQueue,
                         Queue<NumInfo>* producingQueue);

  /**
   * @brief Destroys the array of calculators.
   *
   */
  void destroyCalculators();

  /**
   * @brief Destroys the packer attribute.
   *
   */
  void destroyPacker();

  /**
   * @brief Destroys the dispatcher attribute.
   *
   */
  void destroyDispatcher();

  /**
   * @brief Wait for all the threads of the producing chain.
   *
   */
  void stop() override;

  /**
   * @brief Entry point for HTTP requests.
   *
   * @param httpRequest An HTTP request.
   * @param httpResponse An HTTP response.
   * @return true If the request was successfully handled by this app.
   */
  bool handleHttpRequest(HttpRequest& httpRequest,
                         HttpResponse& httpResponse) override;

 private:
  /**
   * @brief Sends the HTML text based on the request of the client, either it
   * sends a form to input the numbers or send the calculated sums of the
   * numbers.
   *
   * @param httpRequest An HTTP request.
   * @param httpResponse An HTTP response
   * @return true If the request was successfully handled by this app.
   */
  bool serveSumGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Reads the numbers from the URL. Returns an empty array if it can't
   * read the numbers
   *
   * @param url The URL.
   * @param can_use_regex A mutex to control the access to the regex.
   * @return An integer array with the numbers.
   */
  static std::vector<int_t> readNumbers(std::string url,
                                        std::mutex& can_use_regex);

  /**
   * @brief Reads a file and writes the text of the file to an output stream.
   *
   * @param output The output stream.
   * @param path The path of the file, relative to the project directory.
   */
  static void readFile(std::ostream& output, const std::string& path);

  /**
   * @brief Reads a file with static text and sends the text.
   *
   * @param httpRequest An HTTP request.
   * @param httpResponse An HTTP response.
   * @param path The path of the file, relative to the project directory.
   * @param contentType The content type of the file.
   * @return true If the request was successfully handled by this app.
   */
  static bool serveStatic(HttpRequest& httpRequest, HttpResponse& httpResponse,
                          const std::string& path,
                          const std::string& contentType);
};

#endif  // SUM_GOLDBACH_WEB_APP_HPP_
