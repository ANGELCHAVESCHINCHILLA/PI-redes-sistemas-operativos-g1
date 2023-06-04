// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef HTTP_REQUEST_HANDLER
#define HTTP_REQUEST_HANDLER

#include "../../http/HttpRequest.hpp"
#include "../../http/HttpResponse.hpp"
#include "../../common/common.hpp"
#include "../FileSystemAPI.hpp"

/**
 * @brief The interface for each handler of the chain
 * 
 */
class FileSystemRequestHandler {
  /// Don't allow copies of this object
  DISABLE_COPY(FileSystemRequestHandler);

 public:
  FileSystemAPI* fileSystemApi;
  /// Constructor
  explicit FileSystemRequestHandler(FileSystemAPI* api) : fileSystemApi(api){};
  /// Destructor
  virtual ~FileSystemRequestHandler() = default;

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

#endif  // HTTP_REQUEST_HANDLER
