#pragma once
#include <format>
#include <fstream>
#include <string>

namespace assets {
inline auto load_input(int day) -> std::string {
    auto path = std::format("assets/inputs/day{:02}.txt", day);
    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline auto load_example(int day) -> std::string {
    auto path = std::format("assets/examples/day{:02}.txt", day);
    auto f = std::ifstream(path);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline auto load(int day, bool example) -> std::string {
    return example ? load_example(day) : load_input(day);
}
}; // namespace assets
