#pragma once
#include <string>

struct Puzzle {
    auto solve(std::string input) -> std::pair<std::string, std::string> { return {part_one(input), part_two(input)}; }
    virtual auto part_one(std::string input) -> std::string { return ""; };
    virtual auto part_two(std::string input) -> std::string { return ""; };
};
