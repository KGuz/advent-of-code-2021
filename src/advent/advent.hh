#pragma once
#include <cstdlib>
#include <memory>
#include <string>

namespace advent {
struct Puzzle {
    virtual auto part_one(const std::string& input) -> std::string { return ""; };
    virtual auto part_two(const std::string& input) -> std::string { return ""; };
};

struct Day01 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day02 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day03 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day04 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day05 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day06 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day07 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day08 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day09 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day10 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day11 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day12 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day13 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day14 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day15 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day16 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day17 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day18 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day19 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day20 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day21 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day22 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day23 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day24 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};
struct Day25 : public Puzzle {
    auto part_one(const std::string&) -> std::string override;
    auto part_two(const std::string&) -> std::string override;
};

inline auto dispatch(int day) -> std::unique_ptr<Puzzle> {
    switch (day) {
        case 1: return std::make_unique<Day01>(Day01());
        case 2: return std::make_unique<Day02>(Day02());
        case 3: return std::make_unique<Day03>(Day03());
        case 4: return std::make_unique<Day04>(Day04());
        case 5: return std::make_unique<Day05>(Day05());
        case 6: return std::make_unique<Day06>(Day06());
        case 7: return std::make_unique<Day07>(Day07());
        case 8: return std::make_unique<Day08>(Day08());
        case 9: return std::make_unique<Day09>(Day09());
        case 10: return std::make_unique<Day10>(Day10());
        case 11: return std::make_unique<Day11>(Day11());
        case 12: return std::make_unique<Day12>(Day12());
        case 13: return std::make_unique<Day13>(Day13());
        case 14: return std::make_unique<Day14>(Day14());
        case 15: return std::make_unique<Day15>(Day15());
        case 16: return std::make_unique<Day16>(Day16());
        case 17: return std::make_unique<Day17>(Day17());
        case 18: return std::make_unique<Day18>(Day18());
        case 19: return std::make_unique<Day19>(Day19());
        case 20: return std::make_unique<Day20>(Day20());
        case 21: return std::make_unique<Day21>(Day21());
        case 22: return std::make_unique<Day22>(Day22());
        case 23: return std::make_unique<Day23>(Day23());
        case 24: return std::make_unique<Day24>(Day24());
        case 25: return std::make_unique<Day25>(Day25());
        default: std::abort();
    }
}
} // namespace advent
