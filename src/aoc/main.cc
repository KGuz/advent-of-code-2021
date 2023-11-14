#include "advent.hh"
#include "args.hh"
#include "assets.hh"
#include <format>
#include <iostream>

auto main(int argc, char** argv) -> int {
    auto [day, example] = args::parse(argc, argv);
    auto input = assets::load(day, example);
    auto puzzle = advent::dispatch(day);

    std::cout << std::format("{:*^60}\n", std::format(" Advent of Code 2021 - Day {} ", day));
    std::cout << std::format("Part one {:.>51}", puzzle->part_one(input)) << std::endl;
    std::cout << std::format("Part two {:.>51}", puzzle->part_two(input)) << std::endl;
    return 0;
}
