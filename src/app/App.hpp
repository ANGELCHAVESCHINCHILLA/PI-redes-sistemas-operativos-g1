// Copyright © 2023 Camilo Suárez Sandí

#ifndef APP_HPP_
#define APP_HPP_

#include <map>

#include "../http/HttpApp.hpp"

class App : public HttpApp {
 private:
  static std::map<std::string, std::string> CONTENT_TYPE_MAP;

 public:
  /**
   * @brief Default constructor.
   *
   */
  App();

  /**
   * @brief Destructor.
   *
   */
  ~App();

  // Copy Constructor
  App(const App& other) = delete;

  // Copy Assignment Operator
  App& operator=(const App& other) = delete;

  // Move Constructor
  App(App&& other) = delete;

  // Move Assignment Operator
  App& operator=(App&& other) = delete;

  bool run(const HttpRequest& request, HttpResponse& response) override;

 private:
  std::string readFileToString(const std::string& relative_path) const;

  bool servePage(const HttpRequest& request, HttpResponse& response,
      const std::string& path) const;

  bool serveNotFoundPage(
      const HttpRequest& request, HttpResponse& response) const;

  bool serveStatic(const HttpRequest& request, HttpResponse& response) const;

  std::string getContentType(
      const HttpRequest& request, const std::string& path) const;
};

#endif  // APP_HPP_
