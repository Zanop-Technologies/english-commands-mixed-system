#include "parser.hpp"

#include <cctype>
#include <stdexcept>

namespace ecmxs {
namespace {

std::vector<std::string> split_commands(const std::string& source) {
    std::vector<std::string> segments;
    std::string current;
    char quote = '\0';
    bool escaped = false;

    for (char ch : source) {
        if (escaped) {
            current += ch;
            escaped = false;
        } else if (ch == '\\' && quote != '\'') {
            current += ch;
            escaped = true;
        } else if (quote != '\0') {
            current += ch;
            if (ch == quote) quote = '\0';
        } else if (ch == '\'' || ch == '"') {
            quote = ch;
            current += ch;
        } else if (ch == ';') {
            segments.push_back(std::move(current));
            current.clear();
        } else {
            current += ch;
        }
    }
    if (escaped || quote != '\0') throw std::invalid_argument("Unterminated escape or quote");
    segments.push_back(std::move(current));
    return segments;
}

std::vector<std::string> tokenize(const std::string& segment) {
    std::vector<std::string> tokens;
    std::string token;
    char quote = '\0';
    bool escaped = false;
    bool started = false;

    for (char ch : segment) {
        if (escaped) {
            token += ch;
            escaped = false;
            started = true;
        } else if (ch == '\\' && quote != '\'') {
            escaped = true;
            started = true;
        } else if (quote != '\0') {
            if (ch == quote) quote = '\0';
            else token += ch;
            started = true;
        } else if (ch == '\'' || ch == '"') {
            quote = ch;
            started = true;
        } else if (std::isspace(static_cast<unsigned char>(ch))) {
            if (started) {
                tokens.push_back(std::move(token));
                token.clear();
                started = false;
            }
        } else {
            token += ch;
            started = true;
        }
    }
    if (escaped || quote != '\0') throw std::invalid_argument("Unterminated escape or quote");
    if (started) tokens.push_back(std::move(token));
    return tokens;
}

} // namespace
std::vector<Command> parse_syntax(const std::string& source) {
    std::vector<Command> commands;
    for (const auto& segment : split_commands(source)) {
        auto tokens = tokenize(segment);
        if (tokens.empty()) continue;
        Command command;
        command.name = std::move(tokens.front());
        command.args.assign(std::make_move_iterator(tokens.begin() + 1),
                            std::make_move_iterator(tokens.end()));
        commands.push_back(std::move(command));
    }
    return commands;
}

} // namespace ecmxs
