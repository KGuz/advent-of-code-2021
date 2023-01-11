module;
#include "puzzle.hh"
#include <algorithm>
#include <ranges>
#include <string>

export module day01;
import utilities;

using std::string, std::to_string;
using std::ranges::count_if, std::views::slide;

auto sonar_sweep(const string &input, int windows_size) -> string {
    auto report = utl::map(utl::lines(input), utl::parse<int>);
    return to_string(count_if(report | slide(windows_size), [](const auto &window) {
        return window.front() < window.back();
    }));
}

export struct Day01 : Puzzle {
    auto part_one(string input) -> string override { return sonar_sweep(input, 2); }
    auto part_two(string input) -> string override { return sonar_sweep(input, 4); }
};