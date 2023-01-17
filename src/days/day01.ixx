module;
#include "puzzle.hh"
#include <algorithm>
#include <ranges>

export module day01;
import utilities;

using std::ranges::count_if, std::views::slide;

auto sonar_sweep(const std::string& input, int windows_size) -> std::string {
    auto report = utl::map(utl::lines(input), utl::parse<int>);
    return std::to_string(
        count_if(report | slide(windows_size), [](const auto& window) { return window.front() < window.back(); }));
}

export struct Day01 : Puzzle {
    auto part_one(std::string input) -> std::string override { return sonar_sweep(input, 2); }
    auto part_two(std::string input) -> std::string override { return sonar_sweep(input, 4); }
};