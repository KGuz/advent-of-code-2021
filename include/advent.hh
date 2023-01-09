#pragma once

#include "puzzle.hh"
#include <memory>

struct Advent {
    static auto get(int) -> std::unique_ptr<Puzzle>;
    auto operator[](int) -> std::unique_ptr<Puzzle>;
};