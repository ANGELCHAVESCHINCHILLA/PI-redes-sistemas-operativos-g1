//

// #ifdef TEST

#include <gtest/gtest.h>

#include <iostream>

#include "http/HttpRequest.hpp"
#include "url/URL.hpp"

TEST(URLTest, URLTest) {
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

  ASSERT_EQ(target.toString(), std::string("https://localhost:3000/path/to/resource?param1=value1&param2=value2#section1"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

// #endif  // TEST
