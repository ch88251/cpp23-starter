#include "hello/hello.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::string who = (argc > 1) ? argv[1] : "C++23";
  if (auto g = hello::make_greeting(who)) {
    std::cout << *g << '\n';
    return 0;
  } else {
    std::cerr << "Error: " << g.error() << '\n';
    return 1;
  }
}

