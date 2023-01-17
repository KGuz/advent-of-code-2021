#include <format>
#include <iostream>

import advent;
import args;
import dataset;
import utilities;

auto main(int argc, char** argv) -> int {
    auto [day, example] = args::parse(argc, argv);
    auto input = dataset::input(day, example);
    auto puzzle = advent::puzzle(day);

    utl::print(std::format("{:*^60}", std::format(" Advent of Code 2021 - Day {} ", day)));
    auto [part_one, part_two] = puzzle->solve(input);
    utl::print(std::format("Part one {:.>51}", part_one));
    utl::print(std::format("Part two {:.>51}", part_two));
    return 0;
}
