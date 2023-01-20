module;
#include "puzzle.hh"
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
export module day07;
import utilities;

template <class CostFunction>
auto treachery_of_whales(const std::string& input, CostFunction fn) -> int {
    auto positions = utl::map(utl::split(input, ','), utl::parse<int>);
    auto begin = *std::min_element(positions.begin(), positions.end());
    auto end = *std::max_element(positions.begin(), positions.end());

    auto fuel = INT_MAX;
    for (auto dest = begin; dest <= end; ++dest) {
        fuel = std::min(fuel, utl::reduce(positions, 0, [&dest, &fn](auto acc, const auto& src) {
            return acc + fn(dest, src);
        }));
    }
    return fuel;
}

export struct Day07 : Puzzle {
    auto part_one(std::string input) -> std::string override {
        return std::to_string(treachery_of_whales(input, [](auto dest, auto src) { return std::abs(dest - src); }));
    }
    auto part_two(std::string input) -> std::string override {
        return std::to_string(treachery_of_whales(input, [](auto dest, auto src) {
            auto delta = std::abs(dest - src) + 1;
            return (delta * (delta - 1)) / 2;
        }));
    }
};