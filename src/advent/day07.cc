#include "advent.hh"
#include "utl.hh"
#include <cmath>

namespace {
auto treachery_of_whales(const std::string& input, auto cost) -> int {
    auto positions = utl::to_vector(utl::split(input, ',') | views::transform(utl::parse<int>));
    auto begin = *std::min_element(positions.begin(), positions.end());
    auto end = *std::max_element(positions.begin(), positions.end());

    auto fuel = INT_MAX;
    for (auto dest = begin; dest <= end; ++dest) {
        fuel = std::min(fuel, utl::reduce(positions, 0, [&dest, &cost](auto acc, const auto& src) {
            return acc + cost(dest, src);
        }));
    }
    return fuel;
}
} // namespace

auto advent::Day07::part_one(const std::string& input) -> std::string {
    return std::to_string(
        treachery_of_whales(input, [](auto dest, auto src) { return std::abs(dest - src); }));
}
auto advent::Day07::part_two(const std::string& input) -> std::string {
    return std::to_string(treachery_of_whales(input, [](auto dest, auto src) {
        auto delta = std::abs(dest - src) + 1;
        return (delta * (delta - 1)) / 2;
    }));
}
