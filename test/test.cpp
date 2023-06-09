//

#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>

#include <iostream>

#include "configuration.hpp"
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
#include "http/HttpServer.hpp"
#include "url/URL.hpp"

TEST(URLTest, URLParseTest) {
  URL url(
      "https://localhost:3000/path/to/"
      "resource?param1=value1&param2=value2#section1");

  ASSERT_EQ(url.getScheme(), std::string("https"));
  ASSERT_EQ(url.getHost(), std::string("localhost"));
  ASSERT_EQ(url.getPort(), 3000);
  ASSERT_EQ(url.getPath(), std::string("/path/to/resource"));
  ASSERT_EQ(url.getQuery().size(), 2);
  ASSERT_EQ(url.getQuery().at("param1"), std::string("value1"));
  ASSERT_EQ(url.getQuery().at("param2"), std::string("value2"));
  ASSERT_EQ(url.getFragment(), std::string("section1"));

  ASSERT_EQ(url.toString(),
      std::string("https://localhost:3000/path/to/"
                  "resource?param1=value1&param2=value2#section1"));
}

TEST(HttpRequestTest, HttpRequestParseTest) {
  std::string string =
      R"(POST https://localhost:3000/path/to/resource?param1=value1&param2=value2#section1 HTTP/1.1
Host: localhost
Content-Type: application/json

{
  "name": "Martin",
  "email": "martin@gmail.com"
}
)";

  HttpRequest request(string);

  ASSERT_EQ(request.getMethod(), std::string("POST"));

  ASSERT_EQ(request.getHeader("Host"), std::string("localhost"));
  ASSERT_EQ(request.getHeader("Content-Type"), std::string("application/json"));

  URL target = request.getTarget().copy();

  ASSERT_EQ(target.getScheme(), std::string("https"));
  ASSERT_EQ(target.getHost(), std::string("localhost"));
  ASSERT_EQ(target.getPort(), 3000);
  ASSERT_EQ(target.getPath(), std::string("/path/to/resource"));
  ASSERT_EQ(target.getQuery().size(), 2);
  ASSERT_EQ(target.getQuery().at("param1"), std::string("value1"));
  ASSERT_EQ(target.getQuery().at("param2"), std::string("value2"));
  ASSERT_EQ(target.getFragment(), std::string("section1"));

  ASSERT_EQ(target.toString(),
      std::string("https://localhost:3000/path/to/"
                  "resource?param1=value1&param2=value2#section1"));

  Json::Reader reader;
  Json::Value root;

  reader.parse(request.getBody(), root);

  std::string name = root["name"].asString();
  std::string email = root["email"].asString();

  ASSERT_EQ(name, std::string("Martin"));
  ASSERT_EQ(email, std::string("martin@gmail.com"));
}

TEST(HttpResponseTest, HttpResponseParseTest) {
  std::string string = R"(HTTP/1.1 200 OK
Content-Type: application/json

{
  "message": "Hello, World!",
  "status": "Success"
}
)";

  HttpResponse response(string);

  ASSERT_EQ(response.getStatusCode(), 200);
  ASSERT_EQ(response.getReasonPhrase(), std::string("OK"));
  ASSERT_EQ(
      response.getHeader("Content-Type"), std::string("application/json"));

  Json::Reader reader;
  Json::Value root;

  reader.parse(response.getBody(), root);

  std::string message = root["message"].asString();
  std::string status = root["status"].asString();

  ASSERT_EQ(message, std::string("Hello, World!"));
  ASSERT_EQ(status, std::string("Success"));
}

TEST(ConfigurationTest, ConfigurationParseTest) {
  Configuration& configuration = Configuration::getInstance();

  std::string configuration_path = "test/configuration.json";

  configuration.configure(configuration_path);

  ASSERT_EQ(configuration.apps.size(), 3);

  ASSERT_TRUE(configuration.hasApp("web"));
  ASSERT_TRUE(configuration.hasApp("fs"));
  ASSERT_TRUE(configuration.hasApp("db"));

  ASSERT_EQ(configuration.port, 8080);

  ASSERT_EQ(configuration.servers.size(), 4);

  const ServerConfiguration& web = configuration.getServer("web");

  ASSERT_EQ(web.address, std::string("127.0.0.1"));
  ASSERT_EQ(web.port, 8001);

  const ServerConfiguration& fs = configuration.getServer("fs");

  ASSERT_EQ(fs.address, std::string("127.0.0.1"));
  ASSERT_EQ(fs.port, 8002);

  const ServerConfiguration& db = configuration.getServer("db");

  ASSERT_EQ(db.address, std::string("127.0.0.1"));
  ASSERT_EQ(db.port, 8003);
}

TEST(HttpServerTest, HttpServerFetchTest) {
  HttpRequest request;

  request.setMethod("GET");
  request.setTarget("http://numbersapi.com:80/42");

  auto future = HttpServer::fetch(request);

  std::cout << "I'm waiting for an http response...\n";

  HttpResponse response = future.get();

  ASSERT_EQ(response.getStatusCode(), 200);
  ASSERT_EQ(response.getReasonPhrase(), std::string("OK"));

  std::cout << response.getBody().str() << "\n";
}

#ifdef TEST

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

#endif  // TEST
