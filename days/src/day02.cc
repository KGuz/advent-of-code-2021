#include "day02.hh"
#include "utils.hh"

namespace {
enum Dir { Forward, Down, Up };
auto to_dir(std::string_view text) -> Dir {
    if (text.compare("forward") == 0) {
        return Dir::Forward;
    }
    if (text.compare("down") == 0) {
        return Dir::Down;
    }
    if (text.compare("up") == 0) {
        return Dir::Up;
    }
}

template <typename Pred>
auto calculate(const string &input, Pred predicate) -> string {
    auto lines = utils::lines(input);
    auto commands = utils::map(lines, [](const auto &line) {
        auto [direction, units] = utils::split_once(line, ' ');
        return std::make_pair(to_dir(direction), utils::parse<int>(units));
    });

    auto pos = std::make_tuple(0, 0, 0);
    for (const auto &[dir, units] : commands) {
        predicate(dir, units, pos);
    }
    return std::to_string(std::get<0>(pos) * std::get<1>(pos));
}
} // namespace

auto Day02::part_one(string input) -> string {
    auto interpretation = [](auto &dir, auto &units, auto &pos) {
        switch (dir) {
        case Dir::Forward:
            std::get<0>(pos) += units;
            break;
        case Dir::Up:
            std::get<1>(pos) -= units;
            break;
        case Dir::Down:
            std::get<1>(pos) += units;
            break;
        }
    };
    return calculate(input, interpretation);
}

auto Day02::part_two(string input) -> string {
    auto interpretation = [](auto &dir, auto &units, auto &pos) {
        switch (dir) {
        case Dir::Forward:
            std::get<0>(pos) += units;
            std::get<1>(pos) += units * std::get<2>(pos);
            break;
        case Dir::Up:
            std::get<2>(pos) -= units;
            break;
        case Dir::Down:
            std::get<2>(pos) += units;
            break;
        }
    };
    return calculate(input, interpretation);
}
