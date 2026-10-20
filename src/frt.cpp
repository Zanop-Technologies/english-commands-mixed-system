#include "frt.hpp"

#include <charconv>
#include <cstddef>
#include <string_view>

namespace ecmxs {
FartResult run_fart(const std::vector<std::string>& args) {
    if (args.size() != 4 || args[0] != "-i" || args[1] != "-p") {
        return {false, "Usage: frt -i -p <packets> <ip>"};
    }

    std::size_t packets = 0;
    const std::string_view count(args[2]);
    const auto [end, error] = std::from_chars(count.data(), count.data() + count.size(), packets);
    if (error != std::errc{} || end != count.data() + count.size() || packets == 0) {
        return {false, "Packet count must be a positive integer"};
    }
    if (args[3].empty()) return {false, "An IP address is required"};

    // Networking behavior is intentionally left to the shell's platform layer.
    return {true, "Fart request: " + std::to_string(packets) + " packets to " + args[3]};
}
} // namespace ecmxs
