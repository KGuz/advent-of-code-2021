#pragma once

#include <string>
using std::string;

struct Puzzle {
    virtual auto solve(string input) -> std::pair<string, string> { return {part_one(input), part_two(input)}; }

    virtual auto part_one(string) -> string { return ""; };

    virtual auto part_two(string) -> string { return ""; };
};
