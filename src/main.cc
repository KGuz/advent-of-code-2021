#include <format>
#include <iostream>

import advent;
import dataset;
import args;

using std::format, std::cout, std::endl;

auto main(int argc, char **argv) -> int {
    auto [day, example] = Args::parse(argc, argv);
    auto input = Dataset::get(day, example);
    auto puzzle = Advent::get(day);

    cout << format("{:*^60}", format(" Advent of Code 2021 - Day {} ", day)) << endl;
    auto [part_one, part_two] = puzzle->solve(input);
    cout << format("Part one {:.>51}", part_one) << endl;
    cout << format("Part two {:.>51}", part_two) << endl;
    return 0;
}
