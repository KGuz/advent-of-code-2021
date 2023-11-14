#include "advent.hh"
#include "point.hh"
#include "utl.hh"
#include <array>

namespace {
template <typename T, size_t N>
using grid = std::array<std::array<T, N>, N>;

auto make_grid(const std::vector<std::string>& lines) -> grid<int, 10> {
    auto data = grid<int, 10>();
    for (auto&& [y, x] : iter::product<2>(views::iota(0, 10))) {
        data[y][x] = lines[y][x] - '0';
    }
    return data;
}

auto simulate(grid<int, 10>& grid, size_t steps) -> int {
    auto flashes = 0;
    for (auto i : views::iota(0u, steps)) {
        auto next_grid(grid);
        /* ... */
    }
    return flashes;
}
} // namespace

auto advent::Day11::part_one(const std::string& input) -> std::string {
    auto grid = make_grid(utl::lines(input));
    return std::to_string(simulate(grid, 100));
}
auto advent::Day11::part_two(const std::string& input) -> std::string { return ""; }
