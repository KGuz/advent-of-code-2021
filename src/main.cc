#include "advent.hh"
#include "dataset.hh"
#include "parser.hh"
#include "utils.hh"

using std::format, utils::print;

auto main(int argc, char **argv) -> int {
    auto [day, example] = parse_arguments(argc, argv);
    auto input = Dataset::get(day, example);
    auto puzzle = Advent::get(day);

    print(format("{:*^60}", format(" Advent of Code 2021 - Day {} ", day)));
    auto [part_one, part_two] = puzzle->solve(input);
    print(format("Part one {:.>51}", part_one));
    print(format("Part two {:.>51}", part_two));
    return 0;
}
