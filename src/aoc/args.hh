#pragma once
#include "cxxopts.hh"
#include <format>
#include <iostream>

namespace args {
inline auto parse(int argc, char** argv) -> std::pair<int, bool> {
    auto options = cxxopts::Options("aoc", "Solver of 2021 Advent of Code Puzzles");

    // clang-format off
    options.add_options()
        ("d,day", "Advent day number (1-25)", cxxopts::value<int>())
        ("e,example", "Use example input", cxxopts::value<bool>()->default_value("false"))
        ("h,help", "Print usage");
    options.parse_positional({"day"});
    // clang-format on

    auto result = options.parse(argc, argv);
    if (result.count("help") or result.count("day") == 0) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    return std::make_pair(result["day"].as<int>(), result["example"].as<bool>());
}
} // namespace args