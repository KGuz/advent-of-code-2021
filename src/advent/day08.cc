#include "advent.hh"
#include "utl.hh"
#include <map>
#include <optional>

namespace {
auto decode_token(const std::string& token) -> std::optional<int> {
    switch (token.size()) {
        case 2: return 1;
        case 4: return 4;
        case 3: return 7;
        case 7: return 8;
        default: return std::nullopt;
    }
}

auto decode(const std::string& token, std::map<int, std::set<char>>& map) -> int {
    auto set = std::set<char>{token.begin(), token.end()};
    switch (token.size()) {
        case 2: return 1;
        case 4: return 4;
        case 3: return 7;
        case 7: return 8;
        case 6:
            if (utl::intersection(set, map[1]).size() != 2) return 6;
            if (utl::intersection(set, map[4]).size() == 4) return 9;
            return 0;
        case 5:
            if (utl::intersection(set, map[1]).size() == 2) return 3;
            if (utl::intersection(set, utl::difference(map[4], map[1])).size() == 2) return 5;
            return 2;
        default: std::unreachable();
    }
}
} // namespace

auto advent::Day08::part_one(const std::string& input) -> std::string {
    auto unique_count = 0;
    for (auto& line : utl::lines(input)) {
        auto [_, right] = utl::split_once(line, '|');
        unique_count += utl::reduce(utl::split(right, ' '), 0,
            [](auto acc, auto& out) { return acc + (decode_token(out) ? 1 : 0); });
    }
    return std::to_string(unique_count);
}

auto advent::Day08::part_two(const std::string& input) -> std::string {
    auto output_sum = 0;
    for (auto& line : utl::lines(input)) {
        auto [left, right] = utl::split_once(line, '|');
        auto signals = utl::split(left, ' '), outputs = utl::split(right, ' ');

        auto map = std::map<int, std::set<char>>();
        for (const auto& token : utl::concat(signals, outputs)) {
            if (auto digit = decode_token(token); digit) {
                map[*digit] = std::set<char>(token.begin(), token.end());
            }
        }

        for (auto i = 3, p = 1; i >= 0; --i, p *= 10) {
            output_sum += p * decode(outputs[i], map);
        }
    }
    return std::to_string(output_sum);
}
