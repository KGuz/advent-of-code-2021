#pragma once
#include <string>

struct Puzzle {
    auto solve(const std::string& input) -> std::pair<std::string, std::string> { return {part_one(input), part_two(input)}; }
    virtual auto part_one(const std::string& input) -> std::string { return ""; };
    virtual auto part_two(const std::string& input) -> std::string { return ""; };
};
