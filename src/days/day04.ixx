module;
#include "itertools.hh"
#include "puzzle.hh"
#include <map>
#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

export module day04;
import utilities;

class Bingo {
    std::map<int, std::pair<size_t, size_t>> lut;
    size_t size;

public:
    Bingo(const vector<vector<int>>& v) : size{v.size()} {
        for (auto&& [y, x] : iter::product<2>(views::iota(0u, size))) {
            lut.emplace(v[y][x], std::make_pair(y, x));
        }
    }

    auto simulate(const vector<int>& nums) const -> int {
        auto card = vector<vector<bool>>(size, vector<bool>(size, false));
        for (const auto& [i, num] : iter::enumerate(nums)) {
            if (not lut.contains(num)) {
                continue;
            }
            auto [y, x] = lut.at(num);
            card[y][x] = true;

            if (bingo(card)) {
                return static_cast<int>(i);
            }
        }
        return size * size;
    }

    auto bingo(const vector<vector<bool>>& card) const -> bool {
        for (auto i : std::views::iota(0u, size)) {
            auto in_row = 0, in_col = 0;

            for (auto j : std::views::iota(0u, size)) {
                in_row += static_cast<int>(card[i][j]);
                in_col += static_cast<int>(card[j][i]);
            }

            if (in_row == size | in_col == size) {
                return true;
            }
        }
        return false;
    }

    auto numbers() const { return std::views::keys(lut); }

    static auto generate(const vector<string>& lines) -> vector<Bingo> {
        auto boards = vector<vector<vector<int>>>();
        for (auto i = 2, n = 0; i < lines.size(); ++i, ++n) {
            boards.emplace_back();
            for (; i < lines.size() and !lines[i].empty(); ++i) {
                auto numbers = utl::split(lines[i], ' ') | views::transform(utl::parse<int>);
                boards[n].push_back(numbers | ranges::to<vector>());
            }
        }
        return boards | views::transform([](const auto& v) { return Bingo(v); }) | ranges::to<vector>();
    }
};

enum Strategy { Win, Lose };

auto giant_squid(const string& input, Strategy strategy) -> string {
    auto lines = utl::lines(input);

    auto nums = utl::split(lines[0], ',') | views::transform(utl::parse<int>) | ranges::to<vector>();
    auto bingo_cards = Bingo::generate(lines);

    auto fun = [&](const auto& b) { return b.simulate(nums); };
    auto [steps, bingo] = (strategy == Strategy::Win ? utl::min(bingo_cards, fun) : utl::max(bingo_cards, fun));

    auto acc = utl::reduce(bingo.numbers(), 0, [&](int acc, int key) {
        return acc + (utl::contains(nums | iter::slice(0, steps + 1), key) ? 0 : key);
    });

    return std::to_string(acc * nums[steps]);
}

export struct Day04 : Puzzle {
    auto part_one(const std::string& input) -> string override { return giant_squid(input, Strategy::Win); }
    auto part_two(const std::string& input) -> string override { return giant_squid(input, Strategy::Lose); }
};