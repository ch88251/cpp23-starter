#include "hello/hello.hpp"
#include <algorithm>
#include <cctype>

namespace {

bool has_only_spaces(std::string_view s) {
  return std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::isspace(c); });
}

}

namespace hello {

std::expected<std::string, std::string>
make_greeting(std::string_view name) {
  if (name.empty() || has_only_spaces(name)) {
    return std::unexpected{"name must be non-empty"};
  }
  std::string result = "Hello, ";
  result.append(name);
  result.append(" 👋");
  return result;
}

} // namespace hello

