#pragma once
#include <ranges>
#include <string>
#include <vector>

namespace ranges = std::ranges;
namespace views = std::views;

namespace utl {
auto ltrim(std::string&& s) -> std::string;
auto rtrim(std::string&& s) -> std::string;
auto trim(std::string&& s) -> std::string;

auto split_once(const std::string& s, char c) -> std::pair<std::string, std::string>;
auto split(const std::string& s, char c) -> std::vector<std::string>;

auto lines(const std::string& s) -> std::vector<std::string>;

template <typename T>
inline auto parse(const std::string& str) -> T {
    return static_cast<T>(std::stof(str));
}
} // namespace utl