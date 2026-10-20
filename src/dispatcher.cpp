#include "dispatcher.hpp"

#include "frt.hpp"

#include <filesystem>
#include <system_error>

namespace ecmxs {
namespace {
Result path_error(const std::string& command, const std::error_code& error) {
    return Result::fail(command, error.message(), error.value());
}
} // namespace
Result dispatch(const Command& command) {
    if (command.name == "frt") {
        const auto fart = run_fart(command.args);
        return fart.success ? Result::ok(command.name, fart.message)
                            : Result::fail(command.name, fart.message);
    }
    if (command.name == "con") {
        const auto directory = command.args.empty() ? std::filesystem::path(".")
                                                     : std::filesystem::path(command.args.front());
        std::error_code error;
        std::filesystem::directory_iterator it(directory, error), end;
        if (error) return path_error(command.name, error);
        std::string listing;
        for (; it != end; it.increment(error)) {
            if (error) return path_error(command.name, error);
            if (!listing.empty()) listing += '\n';
            listing += it->path().filename().string();
        }
        return Result::ok(command.name, listing);
    }
    return Result::fail(command.name, "Unknown command: " + command.name, 127);
}

std::vector<Result> dispatch_line(const std::string& line) {
    std::vector<Result> results;
    for (const auto& command : parse_syntax(line)) results.push_back(dispatch(command));
    return results;
}

} // namespace ecmxs
