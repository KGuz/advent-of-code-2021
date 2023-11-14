#include "advent.hh"
#include "utl.hh"

namespace {
auto sonar_sweep(const std::string& input, int windows_size) -> std::string {
    auto report = utl::lines(input) | views::transform(utl::parse<int>);
    auto windows = utl::to_vector(report) | views::slide(windows_size);
    return std::to_string(ranges::count_if(windows, [](auto&& w) { return w.front() < w.back(); }));
}
} // namespace

auto advent::Day01::part_one(const std::string& input) -> std::string {
    return sonar_sweep(input, 2);
}
auto advent::Day01::part_two(const std::string& input) -> std::string {
    return sonar_sweep(input, 4);
}
