#pragma once

#include <string>

struct Dataset {
    static auto get(int, bool) -> std::string;
    auto operator[](std::pair<int, bool>) -> std::string;
};