module;
#include "puzzle.hh"
#include <ranges>

export module day02;
import utilities;

enum Dir { Forward, Down, Up };
auto to_dir(const string& text) -> Dir {
    if (text == "down") return Dir::Down;
    if (text == "up") return Dir::Up;
    return Dir::Forward;
}

template <typename Interpretation>
auto calculate(const string& input, Interpretation fn) -> string {
    auto commands = utl::lines(input) | views::transform([](const auto& line) {
        auto [direction, units] = utl::split_once(line, ' ');
        return std::make_pair(to_dir(direction), utl::parse<int>(units));
    });

    auto pos = std::make_tuple(0, 0, 0);
    for (const auto& [dir, units] : commands) {
        fn(dir, units, pos);
    }
    return std::to_string(get<0>(pos) * get<1>(pos));
}

export struct Day02 : Puzzle {
    auto part_one(const std::string& input) -> string {
        auto interpretation = [](auto& dir, auto& units, auto& pos) {
            switch (dir) {
                case Dir::Forward: std::get<0>(pos) += units; break;
                case Dir::Up: std::get<1>(pos) -= units; break;
                case Dir::Down: std::get<1>(pos) += units; break;
            }
        };
        return calculate(input, interpretation);
    }

    auto part_two(const std::string& input) -> string {
        auto interpretation = [](auto& dir, auto& units, auto& pos) {
            switch (dir) {
                case Dir::Forward:
                    std::get<0>(pos) += units;
                    std::get<1>(pos) += units * std::get<2>(pos);
                    break;
                case Dir::Up: std::get<2>(pos) -= units; break;
                case Dir::Down: std::get<2>(pos) += units; break;
            }
        };
        return calculate(input, interpretation);
    }
};