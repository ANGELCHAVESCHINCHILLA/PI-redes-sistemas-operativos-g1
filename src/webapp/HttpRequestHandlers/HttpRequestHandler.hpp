// Copyright © 2023 Ángel Chaves Chinchilla, Camilo Suárez Sandí

#ifndef WEBAPP_HTTP_REQUEST_HANDLER
#define WEBAPP_HTTP_REQUEST_HANDLER

#include "../../http/HttpRequest.hpp"
#include "../../http/HttpResponse.hpp"
#include "../../common/common.hpp"

/**
 * @brief The interface for each handler of the chain
 * 
 */
class HttpRequestHandler {
  /// Don't allow copies of this object
  DISABLE_COPY(HttpRequestHandler);

 public:
  /// Constructor
  HttpRequestHandler() = default;
  /// Destructor
  virtual ~HttpRequestHandler() = default;

  static std::map<std::string, std::string> CONTENT_TYPE_MAP;

  public:
  /**
   * @brief Handle a HttpRequest en generate a HttpResponse if could handle.
   * Each handler of the cain must implements this method.
   * 
   * @return true if could
   * @return false anothes case
   */
  virtual bool canHandle(HttpRequest& request, HttpResponse& response) = 0;

  /**
   * @brief Reads a file with static text and sends the text.
   *
   * @param httpRequest An HTTP request.
   * @param httpResponse An HTTP response.
   * @return true If the request was successfully handled by this app.
   */
  static bool serveStatic(const HttpRequest& request, HttpResponse& response);

  static bool servePage(const HttpRequest& request, HttpResponse& response,
    const std::string& path);

  static bool serveAny(HttpResponse& response, int statusCode
    , std::string contentType = "application/json"
    , const std::string& body = "");

  // Read the file and write the text in the HTTP response
  static bool readFile(std::ostream& output, const std::string& relative_path);

  // static std::string readFileToString(const std::string& relative_path);

  static std::string getContentType(const HttpRequest& request
    , const std::string& path);

};

#endif  // WEBAPP_HTTP_REQUEST_HANDLER
