#pragma once
#include "parser.hpp"
#include "results.hpp"

#include <vector>

namespace ecmxs {

// Execute a parsed ECMXS command and return its structured outcome.
[[nodiscard]] Result dispatch(const Command& command);

// Dispatch all commands from a single input line in order.
[[nodiscard]] std::vector<Result> dispatch_line(const std::string& line);

} // namespace ecmxs
