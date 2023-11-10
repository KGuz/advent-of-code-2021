module;
#include "puzzle.hh"
#include <array>
#include <ranges>

export module day06;
import utilities;

auto lanternfish(const string& input, size_t days) -> uint64_t {
    auto fish = utl::split(input, ',') | views::transform(utl::parse<uint64_t>);

    auto groups = std::array<uint64_t, 9>();
    for (auto&& f : fish) {
        groups[f] += 1;
    }

    for (auto d = 0u; d < days; ++d) {
        auto next = std::array<uint64_t, 9>();
        next[6] += groups[0], next[8] += groups[0];

        for (auto n = 1; n < 9; ++n) {
            next[n - 1] += groups[n];
        }
        groups = next;
    }

    return utl::reduce(groups, 0ull, [](auto acc, auto&& size) { return acc + size; });
}

export struct Day06 : Puzzle {
    auto part_one(const string& input) -> string override { return to_string(lanternfish(input, 80)); }
    auto part_two(const string& input) -> string override { return to_string(lanternfish(input, 256)); }
};