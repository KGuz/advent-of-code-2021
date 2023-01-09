#include "day01.hh"
#include "utils.hh"

namespace {
auto puzzle01(const string& input, int windows_size) -> string {
    auto lines = utils::lines(input);
    auto report = utils::map(lines, utils::parse<int>);

    auto larger = ranges::count_if(report | views::slide(windows_size), [](const auto &window) {
        return window.front() < window.back();
    });

    return std::to_string(larger);
}
} // namespace

auto Day01::part_one(string input) -> string { return puzzle01(input, 2); }
auto Day01::part_two(string input) -> string { return puzzle01(input, 4); }
