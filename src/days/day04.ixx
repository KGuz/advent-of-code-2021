module;
#include "puzzle.hh"
#include <map>
#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <vector>
export module day04;
import utilities;

using std::vector, std::string;

class Bingo {
    std::map<int, std::pair<size_t, size_t>> lut;
    size_t size;

public:
    Bingo(const vector<vector<int>>& v) : size{v.size()} {
        for (auto y : std::views::iota(0u, size)) {
            for (auto x : std::views::iota(0u, size)) {
                lut.emplace(v[y][x], std::make_pair(y, x));
            }
        }
    }

    auto simulate(const vector<int>& nums) const -> int {
        auto card = vector<vector<bool>>(size, vector<bool>(size, false));
        for (const auto& [i, num] : utl::enumerate(nums)) {
            if (not lut.contains(num)) {
                continue;
            }
            auto [y, x] = lut.at(num);
            card[y][x] = true;

            if (bingo(card)) {
                return i;
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
                boards[n].push_back(utl::map(utl::split(lines[i], ' '), utl::parse<int>));
            }
        }
        return utl::map(boards, [](const auto& v) { return Bingo(v); });
    }
};

enum Strategy { Win, Lose };

auto giant_squid(const string& input, Strategy strategy) -> string {
    auto lines = utl::lines(input);

    auto nums = utl::map(utl::split(lines[0], ','), utl::parse<int>);
    auto bingo_cards = Bingo::generate(lines);

    auto fun = [&nums](const auto& b) { return b.simulate(nums); };
    auto [steps, bingo] = (strategy == Strategy::Win ? utl::min(bingo_cards, fun) : utl::max(bingo_cards, fun));

    auto acc = utl::reduce(bingo.numbers(), 0, [&nums, &steps](int acc, int key) {
        return acc + (utl::contains(nums | utl::slice(0, steps + 1), key) ? 0 : key);
    });

    return std::to_string(acc * nums[steps]);
}

export struct Day04 : Puzzle {
    auto part_one(string input) -> string override { return giant_squid(input, Strategy::Win); }
    auto part_two(string input) -> string override { return giant_squid(input, Strategy::Lose); }
};