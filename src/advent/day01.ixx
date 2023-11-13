module;
#include "puzzle.hh"
#include <algorithm>
#include <ranges>

export module day01;
import utilities;

auto sonar_sweep(const string& input, int windows_size) -> string {
    auto report = utl::lines(input) | views::transform(utl::parse<int>) | ranges::to<vector>();
    auto windows = report | views::slide(windows_size);
    return std::to_string(ranges::count_if(windows, [](auto&& w) { return w.front() < w.back(); }));
}

export struct Day01 : Puzzle {
    auto part_one(const std::string& input) -> string override { return sonar_sweep(input, 2); }
    auto part_two(const std::string& input) -> string override { return sonar_sweep(input, 4); }
};