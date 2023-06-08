//

#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>

#include <iostream>

#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
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
  std::string request =
      R"(POST https://localhost:3000/path/to/resource?param1=value1&param2=value2#section1 HTTP/1.1
Host: localhost
Content-Type: application/json

{
  "name": "Martin",
  "email": "martin@gmail.com"
}
)";

  HttpRequest http_request(request);

  ASSERT_EQ(http_request.getMethod(), std::string("POST"));

  ASSERT_EQ(http_request.getHeader("Host"), std::string("localhost"));
  ASSERT_EQ(
      http_request.getHeader("Content-Type"), std::string("application/json"));

  URL target = http_request.getTarget().copy();

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

  reader.parse(http_request.getBody(), root);

  std::string name = root["name"].asString();
  std::string email = root["email"].asString();

  ASSERT_EQ(name, std::string("Martin"));
  ASSERT_EQ(email, std::string("martin@gmail.com"));
}

TEST(HttpResponseTest, HttpResponseParseTest) {
  std::string response = R"(HTTP/1.1 200 OK
Content-Type: application/json

{
  "message": "Hello, World!",
  "status": "Success"
}
)";

  HttpResponse http_response(response);

  ASSERT_EQ(http_response.getStatusCode(), 200);
  ASSERT_EQ(http_response.getReasonPhrase(), std::string("OK"));
  ASSERT_EQ(
      http_response.getHeader("Content-Type"), std::string("application/json"));

  Json::Reader reader;
  Json::Value root;

  reader.parse(http_response.getBody(), root);

  std::string message = root["message"].asString();
  std::string status = root["status"].asString();

  ASSERT_EQ(message, std::string("Hello, World!"));
  ASSERT_EQ(status, std::string("Success"));
}

#ifdef TEST

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

#endif  // TEST
