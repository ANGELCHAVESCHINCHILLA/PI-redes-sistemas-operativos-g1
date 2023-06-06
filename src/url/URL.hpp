// Copyright © 2023 Camilo Suárez Sandí

#ifndef URL_HPP_
#define URL_HPP_

#include <map>
#include <string>

/**
 * @brief Parses and stores the data of a url.
 *
 */
class URL {
 private:
  /**
   * @brief All of the url.
   *
   */
  std::string input;

  /**
   * @brief The scheme of the url. Like http or ftp.
   *
   */
  std::string scheme;

  /**
   * @brief The host of the url. Like 127.0.0.1 or www.google.com.
   *
   */
  std::string host;

  /**
   * @brief The port of the url. -1 if the port is null.
   *
   */
  int port;

  /**
   * @brief The path of the url.
   *
   */
  std::string path;

  std::string fullPath;

  /**
   * @brief The query of the url, the input after the '?'.
   *
   */
  std::map<std::string, std::string> query;

  /**
   * @brief The fragment of the url, the input after the '#'.
   *
   */
  std::string fragment;

 public:
  /**
   * @brief Default constructor.
   *
   */
  explicit URL();

  /**
   * @brief Constructor.
   *
   */
  explicit URL(const std::string& input);

  /**
   * @brief Destructor.
   *
   */
  ~URL();

  // Copy Constructor
  URL(const URL& other) = delete;

  // Copy Assignment Operator
  URL& operator=(const URL& other) = delete;

  // Move Constructor
  URL(URL&& other) = delete;

  // Move Assignment Operator
  URL& operator=(URL&& other);

  /**
   * @brief Returns all of the url.
   *
   * @return const std::string& All of the url.
   */
  const std::string& getInput() const;

  /**
   * @brief Returns the scheme of the url.
   *
   * @return const std::string& The scheme of the url.
   */
  const std::string& getScheme() const;

  /**
   * @brief Returns the host of the url.
   *
   * @return const std::string& The host of the url.
   */
  const std::string& getHost() const;

  /**
   * @brief Returns the port of the url.
   *
   * @return int The port of the url. -1 if the port is null.
   */
  int getPort() const;

  /**
   * @brief Returns the path of the url.
   *
   * @return const std::string& The path of the url.
   */
  const std::string& getPath() const;

  const std::string& getFullPath() const;

  /**
   * @brief Returns a map of the query keys and values.
   *
   * @return const std::map<std::string, std::string>& A map of the query keys
   * and values.
   */
  const std::map<std::string, std::string>& getQuery() const;

  /**
   * @brief Returns the fragment of the url.
   *
   * @return const std::string& The fragment of the url.
   */
  const std::string& getFragment() const;

 private:
  URL& move(URL&& other);

  /**
   * @brief Parses all of the input.
   *
   * @param input Input for all of the url.
   */
  void parse(std::string& input);

  /**
   * @brief Parses the fragment of the url, the input after the '#'.
   *
   * @param input Input for the fragment of the url.
   */
  void parseFragment(std::string& input);

  /**
   * @brief Parses the query of the url, the input after the '?'.
   *
   * @param input Input for the query of the url.
   */
  void parseQuery(std::string& input);

  /**
   * @brief Parses all of the query parameters.
   *
   * @param input Input for all of the query parameters.
   */
  void parseQueryParameters(std::string& input);

  /**
   * @brief Parses one query parameter.
   *
   * @param input Input for one query parameter.
   */
  void parseQueryParameter(const std::string& input);

  /**
   * @brief Parses the path of the url.
   *
   * @param input Input for the path of the url.
   */
  void parsePath(std::string& input);

  /**
   * @brief Parses the scheme of the url.
   *
   * @param input Input for the scheme of the url.
   */
  void parseScheme(std::string& input);

  /**
   * @brief Parses the port of the url.
   *
   * @param input Input for the port of the url.
   */
  void parsePort(std::string& input);

  /**
   * @brief Parses the host of the url.
   *
   * @param input Input for the host of the url.
   */
  void parseHost(std::string& input);
};

#endif  // URL_HPP_
