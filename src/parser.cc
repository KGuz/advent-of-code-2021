#include "parser.hh"
#include <cassert>
#include <cstring>
#include <string>
#include <tuple>

auto parse_arguments(int argc, char **argv) -> std::tuple<int, bool> {
    assert(argc > 1 and argc < 4);
    switch (argc) {
    case 2:
        return {std::stoi(argv[1]), false};
    default:
        auto [pos, flag] = argv[1][0] != '-' ? std::make_pair(argv[1], argv[2]) : std::make_pair(argv[2], argv[1]);

        auto day = std::stoi(pos);
        auto example = strcmp(flag, "-e") == 0 or strcmp(flag, "--example") == 0;
        return {day, example};
    };
}