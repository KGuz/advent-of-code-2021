module;
#include "puzzle.hh"
#include <algorithm>
#include <deque>
#include <ranges>
#include <set>
#include <string>
#include <vector>

export module day09;
import utilities;

using pt = std::pair<int, int>;

struct HightMap {
    vector<vector<int>> data;
    pt size;

    HightMap(const string& input) {
        auto lines = utl::lines(input);
        for (const auto& line : lines) {
            data.emplace_back(utl::to_vector(line | std::views::transform([](const auto& c) { return c - '0'; })));
        }
        size = {data.size(), data[0].size()};
    }

    auto adjacent(int x, int y) const -> vector<pt> {
        auto neighbours = vector<pt>{
            {y - 1, x},
            {y, x - 1},
            {y, x + 1},
            {y + 1, x},
        };
        auto [h, w] = size;
        return utl::to_vector(neighbours | std::views::filter([h, w](const auto& neighbour) {
            auto& [ny, nx] = neighbour;
            return (0 <= ny and ny < h) and (0 <= nx and nx < w);
        }));
    }

    auto is_low_point(int x, int y) const -> bool {
        auto adj = adjacent(x, y) | views::transform([&](const auto& a) { return data[a.first][a.second]; }) | ranges::to<vector>();
        return std::all_of(adj.begin(), adj.end(), [&](const auto& a) { return a > data[y][x]; });
    }

    auto low_points() -> vector<pt> {
        auto [h, w] = size;

        auto points = vector<pt>();
        for (auto y = 0; y < h; ++y) {
            for (auto x = 0; x < w; ++x) {
                if (is_low_point(x, y)) points.emplace_back(y, x);
            }
        }
        return points;
    }

    auto basin_size(const pt& basin) -> size_t {
        auto queue = std::deque<pt>{basin};
        auto visited = std::set<pt>();

        for (; !queue.empty(); queue.pop_front()) {
            auto [y, x] = queue.front();
            if (visited.contains(pt{y, x})) {
                continue;
            }

            visited.insert(pt{y, x});
            for (auto& [ny, nx] : adjacent(x, y)) {
                if (!visited.contains(pt{ny, nx}) and data[ny][nx] != 9) {
                    queue.emplace_back(ny, nx);
                }
            }
        }
        return visited.size();
    }
};

export struct Day09 : Puzzle {
    auto part_one(const std::string& input) -> string override {
        auto map = HightMap(input);
        auto risk_level = utl::reduce(
            map.low_points(), 0, [&map](auto acc, auto& pt) { return acc + map.data[pt.first][pt.second] + 1; });
        return std::to_string(risk_level);
    }

    auto part_two(const std::string& input) -> string override {
        auto map = HightMap(input);
        auto sizes = map.low_points() | views::transform([&map](const auto& basin) { return map.basin_size(basin); }) | ranges::to<vector>();
        ranges::sort(sizes, ranges::greater());

        auto answer = utl::reduce(sizes | std::views::take(3), 1u, [](auto acc, auto& size) { return acc * size; });
        return std::to_string(answer);
    }
};
