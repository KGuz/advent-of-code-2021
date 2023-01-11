module;
#include "puzzle.hh"
#include <cassert>
#include <memory>

export module advent;
import day01;
import day02;
import day03;
import day04;
import day05;
import day06;
import day07;
import day08;
import day09;
import day10;
import day11;
import day12;
import day13;
import day14;
import day15;
import day16;
import day17;
import day18;
import day19;
import day20;
import day21;
import day22;
import day23;
import day24;
import day25;

using std::unique_ptr, std::make_unique, std::unreachable;

export struct Advent {
    static auto get(int day) -> unique_ptr<Puzzle> {
        assert(0 < day and day < 26);
        switch (day) {
        case 1: return make_unique<Day02>(Day02());
        case 2: return make_unique<Day02>(Day02());
        case 3: return make_unique<Day03>(Day03());
        case 4: return make_unique<Day04>(Day04());
        case 5: return make_unique<Day05>(Day05());
        case 6: return make_unique<Day06>(Day06());
        case 7: return make_unique<Day07>(Day07());
        case 8: return make_unique<Day08>(Day08());
        case 9: return make_unique<Day09>(Day09());
        case 10: return make_unique<Day10>(Day10());
        case 11: return make_unique<Day11>(Day11());
        case 12: return make_unique<Day12>(Day12());
        case 13: return make_unique<Day13>(Day13());
        case 14: return make_unique<Day14>(Day14());
        case 15: return make_unique<Day15>(Day15());
        case 16: return make_unique<Day16>(Day16());
        case 17: return make_unique<Day17>(Day17());
        case 18: return make_unique<Day18>(Day18());
        case 19: return make_unique<Day19>(Day19());
        case 20: return make_unique<Day20>(Day20());
        case 21: return make_unique<Day21>(Day21());
        case 22: return make_unique<Day22>(Day22());
        case 23: return make_unique<Day23>(Day23());
        case 24: return make_unique<Day24>(Day24());
        case 25: return make_unique<Day25>(Day25());
        default: unreachable();
        }
    }
};