#include "advent.hh"
#include "day01.hh"
#include "day02.hh"
#include "day03.hh"
#include "day04.hh"
#include "day05.hh"
#include "day06.hh"
#include "day07.hh"
#include "day08.hh"
#include "day09.hh"
#include "day10.hh"
#include "day11.hh"
#include "day12.hh"
#include "day13.hh"
#include "day14.hh"
#include "day15.hh"
#include "day16.hh"
#include "day17.hh"
#include "day18.hh"
#include "day19.hh"
#include "day20.hh"
#include "day21.hh"
#include "day22.hh"
#include "day23.hh"
#include "day24.hh"
#include "day25.hh"
#include <memory>

using std::unique_ptr, std::make_unique;

auto Advent::get(int day) -> unique_ptr<Puzzle> {
    switch (day) {
    case 1:
        return make_unique<Day01>(Day01());
    case 2:
        return make_unique<Day02>(Day02());
    case 3:
        return make_unique<Day03>(Day03());
    case 4:
        return make_unique<Day04>(Day04());
    case 5:
        return make_unique<Day05>(Day05());
    case 6:
        return make_unique<Day06>(Day06());
    case 7:
        return make_unique<Day07>(Day07());
    case 8:
        return make_unique<Day08>(Day08());
    case 9:
        return make_unique<Day09>(Day09());
    case 10:
        return make_unique<Day10>(Day10());
    case 11:
        return make_unique<Day11>(Day11());
    case 12:
        return make_unique<Day12>(Day12());
    case 13:
        return make_unique<Day13>(Day13());
    case 14:
        return make_unique<Day14>(Day14());
    case 15:
        return make_unique<Day15>(Day15());
    case 16:
        return make_unique<Day16>(Day16());
    case 17:
        return make_unique<Day17>(Day17());
    case 18:
        return make_unique<Day18>(Day18());
    case 19:
        return make_unique<Day19>(Day19());
    case 20:
        return make_unique<Day20>(Day20());
    case 21:
        return make_unique<Day21>(Day21());
    case 22:
        return make_unique<Day22>(Day22());
    case 23:
        return make_unique<Day23>(Day23());
    case 24:
        return make_unique<Day24>(Day24());
    case 25:
        return make_unique<Day25>(Day25());
    default:
        return make_unique<Day01>(Day01());
    }
}

auto Advent::operator[](int index) -> unique_ptr<Puzzle> { return this->get(index); }