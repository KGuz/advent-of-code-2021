#include "advent.hh"
#include "utl.hh"
#include <iostream>
#include <utility>

namespace {
auto is_open(char bracket) -> bool {
    return (bracket == '(' or bracket == '[' or bracket == '{' or bracket == '<');
}

auto corresponding_bracket(char bracket) -> char {
    switch (bracket) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: return '?';
    }
}

auto error_penalty(char bracket) -> int {
    switch (bracket) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
        default: return 0;
    }
}

auto incomplete_penalty(char bracket) -> int {
    switch (bracket) {
        case ')': return 1;
        case ']': return 2;
        case '}': return 3;
        case '>': return 4;
        default: return 0;
    }
}

auto syntax_errors(const std::string& line) -> std::pair<std::vector<char>, std::vector<char>> {
    auto errors = std::vector<char>();
    auto stack = std::vector<char>();
    for (auto& c : line) {
        if (is_open(c)) {
            stack.emplace_back(c);
        } else {
            if (c != corresponding_bracket(stack.back())) errors.emplace_back(c);
            stack.pop_back();
        }
    }
    return {errors, stack};
}
} // namespace

auto advent::Day10::part_one(const std::string& input) -> std::string {
    auto score = 0;
    for (auto& line : utl::lines(input)) {
        for (auto& error : syntax_errors(line).first) {
            score += error_penalty(error);
        }
    }
    return std::to_string(score);
}
auto advent::Day10::part_two(const std::string& input) -> std::string {
    auto scores = std::vector<uint64_t>();
    for (auto& line : utl::lines(input)) {
        auto [errors, stack] = syntax_errors(line);
        if (errors.empty()) {
            auto score = uint64_t{0};
            for (auto& opened : std::views::reverse(stack)) {
                score = (score * 5) + incomplete_penalty(corresponding_bracket(opened));
            }
            scores.emplace_back(score);
        }
    }
    ranges::sort(scores);
    return std::to_string(scores[scores.size() / 2]);
}
