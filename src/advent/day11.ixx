module;
#include "itertools.hh"
#include "puzzle.hh"
#include "point.hh"
#include <array>
#include <ranges>
#include <vector>
#include <set>
#include <unordered_set>

export module day11;
import utilities;

template <typename T, size_t N>
using grid = std::array<std::array<T, N>, N>;

auto make_grid(const vector<string>& lines) -> grid<int, 10> {
    auto data = grid<int, 10>();
    for (auto&& [y, x] : iter::product<2>(views::iota(0, 10))) {
        data[y][x] = lines[y][x] - '0';
    }
    return data;
}

auto simulate(grid<int, 10>& grid, size_t steps) -> int {
    auto flashes = 0;
    for (auto i : std::views::iota(0u, steps)) {
        auto next_grid(grid);
        /* ... */
    }
    return flashes;
}

export struct Day11 : Puzzle {
    auto part_one(const std::string& input) -> string override {
        auto grid = make_grid(utl::lines(input));
        utl::print(grid);
        return std::to_string(simulate(grid, 100));
    }
    auto part_two(const std::string& input) -> std::string override { return ""; }
};