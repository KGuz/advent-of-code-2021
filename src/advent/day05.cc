#include "advent.hh"
#include "itertools.hh"
#include "utl.hh"
#include <iostream>
#include <map>

using pt = std::pair<int, int>;

namespace {
auto parse_vents(const std::string& input) -> std::vector<std::pair<pt, pt>> {
    auto vents = utl::lines(input) | views::transform([](const auto& s) {
        auto tokens = utl::split(s, ' ');
        auto [x1, y1] = utl::split_once(tokens[0], ',');
        auto [x2, y2] = utl::split_once(tokens[2], ',');

        auto pt1 = pt{utl::parse<int>(x1), utl::parse<int>(y1)};
        auto pt2 = pt{utl::parse<int>(x2), utl::parse<int>(y2)};
        return std::make_pair(pt1, pt2);
    });
    return utl::to_vector(vents);
}

[[maybe_unused]] auto visualize(const std::map<pt, int>& map) {
    auto [width, height] = [](const auto& m) {
        auto keys = utl::to_vector(views::keys(m));
        auto x_max = utl::max(keys, [](const auto& p) { return p.first; }).second.first;
        auto x_min = utl::min(keys, [](const auto& p) { return p.first; }).second.first;
        auto y_max = utl::max(keys, [](const auto& p) { return p.second; }).second.second;
        auto y_min = utl::min(keys, [](const auto& p) { return p.second; }).second.second;
        return pt{x_max - x_min + 1, y_max - y_min + 1};
    }(map);

    for (auto y = 0; y < width; ++y) {
        for (auto x = 0; x < height; ++x) {
            std::cout << (map.contains(pt{x, y}) ? std::to_string(map.at(pt{x, y})) : ".");
        }
        std::cout << "\n";
    }
}

auto hydrothermal_venture(std::vector<std::pair<pt, pt>>&& points) -> int {
    auto map = std::map<pt, int>();
    for (const auto& [p1, p2] : points) {
        if (p1.first == p2.first) {
            auto y1 = p1.second, y2 = p2.second;
            auto inc_y = y1 < y2 ? 1 : -1;

            for (auto y = y1; y != y2; y += inc_y) {
                map[pt{p1.first, y}] += 1;
            }
        } else if (p1.second == p2.second) {
            auto x1 = p1.first, x2 = p2.first;
            auto inc_x = x1 < x2 ? 1 : -1;

            for (auto x = x1; x != x2; x += inc_x) {
                map[pt{x, p1.second}] += 1;
            }
        } else {
            auto [x1, y1] = p1;
            auto [x2, y2] = p2;
            auto inc_x = x1 < x2 ? 1 : -1;
            auto inc_y = y1 < y2 ? 1 : -1;

            for (auto x = x1, y = y1; x != x2 + inc_x; x += inc_x, y += inc_y) {
                map[pt{x, y}] += 1;
            }
        }
    }

    return utl::reduce(map, 0,
        [](const auto acc, const auto& pair) { return acc + static_cast<int>(pair.second >= 2); });
}
} // namespace

auto advent::Day05::part_one(const std::string& input) -> std::string {
    auto points = parse_vents(input) | views::filter([](const auto& coords) {
        const auto& [p1, p2] = coords;
        return p1.first == p2.first || p1.second == p2.second;
    });
    return std::to_string(hydrothermal_venture(utl::to_vector(points)));
}
auto advent::Day05::part_two(const std::string& input) -> std::string {
    return std::to_string(hydrothermal_venture(parse_vents(input)));
}
