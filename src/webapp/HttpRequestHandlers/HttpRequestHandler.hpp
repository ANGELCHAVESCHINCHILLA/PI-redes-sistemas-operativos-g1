// Copyright © 2023 Ángel Chaves Chinchilla

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
};
