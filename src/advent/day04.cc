#include "advent.hh"
#include "utl.hh"
#include <map>

namespace {
class Bingo {
    std::map<int, std::pair<size_t, size_t>> lut;
    size_t size;

public:
    Bingo(const std::vector<std::vector<int>>& v) : size{v.size()} {
        for (auto&& [y, x] : iter::product<2>(views::iota(0u, size))) {
            lut.emplace(v[y][x], std::make_pair(y, x));
        }
    }

    auto simulate(const std::vector<int>& nums) const -> int {
        auto card = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
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

    auto bingo(const std::vector<std::vector<bool>>& card) const -> bool {
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

    static auto generate(const std::vector<std::string>& lines) -> std::vector<Bingo> {
        auto boards = std::vector<std::vector<std::vector<int>>>();
        for (auto i = 2, n = 0; i < lines.size(); ++i, ++n) {
            boards.emplace_back();
            for (; i < lines.size() and !lines[i].empty(); ++i) {
                auto numbers = utl::split(lines[i], ' ') | views::transform(utl::parse<int>);
                boards[n].push_back(utl::to_vector(numbers));
            }
        }
        return utl::to_vector(boards | views::transform([](const auto& v) { return Bingo(v); }));
    }
};

enum Strategy { Win, Lose };

auto giant_squid(const std::string& input, Strategy strategy) -> std::string {
    auto lines = utl::lines(input);

    auto nums = utl::to_vector(utl::split(lines[0], ',') | views::transform(utl::parse<int>));
    auto bingo_cards = Bingo::generate(lines);

    auto fun = [&](const auto& b) { return b.simulate(nums); };
    auto [steps, bingo] =
        (strategy == Strategy::Win ? utl::min(bingo_cards, fun) : utl::max(bingo_cards, fun));

    auto acc = utl::reduce(bingo.numbers(), 0, [&](int acc, int key) {
        return acc + (utl::contains(nums | iter::slice(0, steps + 1), key) ? 0 : key);
    });

    return std::to_string(acc * nums[steps]);
}
} // namespace

auto advent::Day04::part_one(const std::string& input) -> std::string {
    return giant_squid(input, Strategy::Win);
}
auto advent::Day04::part_two(const std::string& input) -> std::string {
    return giant_squid(input, Strategy::Lose);
}
