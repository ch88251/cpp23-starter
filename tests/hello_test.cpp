#include "hello/hello.hpp"
#include <gtest/gtest.h>

TEST(Hello, MakesGreeting) {
  auto g = hello::make_greeting("World");
  ASSERT_TRUE(g.has_value());
  EXPECT_NE(g->find("World"), std::string::npos);
}

TEST(Hello, RejectsEmpty) {
  auto g = hello::make_greeting("");
  ASSERT_FALSE(g.has_value());
  EXPECT_FALSE(g.error().empty());
}

