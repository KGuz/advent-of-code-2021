
#include "utl.hh"
#include <algorithm>
#include <coroutine>
#include <exception>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace utl {
auto ltrim(std::string&& s) -> std::string {
    auto f = std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); });
    s.erase(s.begin(), f);
    return s;
}

auto rtrim(std::string&& s) -> std::string {
    auto f = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); });
    s.erase(f.base(), s.end());
    return s;
}

auto trim(std::string&& s) -> std::string { return rtrim(ltrim(std::move(s))); }

auto split_once(const std::string& s, char c) -> std::pair<std::string, std::string> {
    auto delim = s.begin() + static_cast<int>(s.find(c));
    return {std::string(s.begin(), delim), std::string(delim + 1, s.end())};
}

auto split(const std::string& s, char c) -> std::vector<std::string> {
    auto res = std::vector<std::string>{};
    auto ss = std::stringstream(s);

    for (std::string line; std::getline(ss, line, c);) {
        if (not line.empty()) {
            res.push_back(line);
        }
    }
    return res;
}

auto lines(const std::string& s) -> std::vector<std::string> {
    auto lines = std::vector<std::string>{};
    auto ss = std::stringstream(s);

    for (std::string line; std::getline(ss, line);) {
        lines.push_back(rtrim(std::move(line)));
    }
    return lines;
}
} // namespace utl
