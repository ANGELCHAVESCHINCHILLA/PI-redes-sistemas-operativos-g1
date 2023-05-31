// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef HTTP_REQUEST_HANDLER
#define HTTP_REQUEST_HANDLER

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
  ~HttpRequestHandler() = default;

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
   * @param path The path of the file, relative to the project directory.
   * @param contentType The content type of the file.
   * @return true If the request was successfully handled by this app.
   */
  static bool serveStatic(HttpRequest& httpRequest,
                          HttpResponse& httpResponse,
                          const std::string& path,
                          const std::string& contentType,
                          const std::string& charset = "; charset=utf-8");

  // Read the file and write the text in the HTTP response
  static void readFile(std::ostream& output, const std::string& path);
};

#endif  // HTTP_REQUEST_HANDLER
