#pragma once
#include <string>
#include <vector>

namespace ecmxs {

// One parsed shell command and its arguments.
struct Command {
    std::string name;
    std::vector<std::string> args;
};

// Parse shell-like command syntax, splitting commands on unquoted semicolons.
// Throws std::invalid_argument when quotes are unmatched.
[[nodiscard]] std::vector<Command> parse_syntax(const std::string& source);

} // namespace ecmxs
