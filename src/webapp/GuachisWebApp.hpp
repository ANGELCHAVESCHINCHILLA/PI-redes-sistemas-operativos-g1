// Copyright © 2023 Ángel Chaves Chinchilla

#ifndef GUACHIS_WEB_APP
#define GUACHIS_WEB_APP

#include "../http/HttpApp.hpp"
#include "../url/URL.hpp"
// #include "../fs.hpp"
#include "../http/HttpResponse.hpp"
#include "../http/HttpRequest.hpp"

class GuachisWebApp : public HttpApp {
  DISABLE_COPY(GuachisWebApp);

 protected:

 public:
  GuachisWebApp();

  ~GuachisWebApp();

  bool start() override;

  bool run(HttpRequest& request, HttpResponse& response) override;

  bool serveLogin(HttpRequest& httpRequest, HttpResponse& httpResponse);

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

  static void readFile(std::ostream& output, const std::string& path);
};

#endif  // GUACHIS_WEB_APP