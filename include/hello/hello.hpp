#pragma once
#include <string>
#include <string_view>
#include <expected>

namespace hello {

// Returns a greeting or an error (demonstrates C++23 std::expected)
[[nodiscard]] std::expected<std::string, std::string>
make_greeting(std::string_view name);

}

