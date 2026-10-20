#include "dispatcher.hpp"

#include <iostream>
#include <string>

int main() {
    std::string line;
    while (std::cout << "ecmxs> " && std::getline(std::cin, line)) {
        try {
            const auto results = ecmxs::dispatch_line(line);
            for (const auto& result : results) {
                if (!result.output.empty()) std::cout << result.output << '\n';
                if (!result.success) {
                    std::cerr << (result.error ? *result.error : "Command failed") << '\n';
                }
            }
        } catch (const std::exception& error) {
            std::cerr << "Syntax error: " << error.what() << '\n';
        }
    }
    return 0;
}
