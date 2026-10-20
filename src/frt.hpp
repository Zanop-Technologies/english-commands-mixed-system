#pragma once
#include <string>
#include <vector>

namespace ecmxs {

// FRT means Fart in ECMXS (not Fast Route Test).
struct FartResult {
    bool success{false};
    std::string message;
};

// Run the FRT (Fart) command. Options follow COMMANDLIST.md: -i -p <packets> <ip>.
[[nodiscard]] FartResult run_fart(const std::vector<std::string>& args);

} // namespace ecmxs
