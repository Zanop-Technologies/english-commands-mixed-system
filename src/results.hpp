#pragma once
#include <optional>
#include <string>
#include <utility>

namespace ecmxs {

// Outcome of one command execution.
struct Result {
    std::string command;
    bool success{false};
    std::string output;
    std::optional<std::string> error;
    int exit_code{0};

    [[nodiscard]] static Result ok(std::string command, std::string output = {}) {
        return {std::move(command), true, std::move(output), std::nullopt, 0};
    }

    [[nodiscard]] static Result fail(std::string command, std::string error, int exit_code = 1) {
        return {std::move(command), false, {}, std::move(error), exit_code};
    }
};

} // namespace ecmxs
