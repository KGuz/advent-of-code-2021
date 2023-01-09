#include "utils.hh"

namespace utils {
inline auto ltrim(string &&s) -> string {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    return s;
}

inline auto rtrim(string &&s) -> string {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    return s;
}

inline auto trim(string &&s) -> string { return rtrim(ltrim(std::move(s))); }

auto lines(const string &s) -> vector<string> {
    auto lines = vector<string>{};
    auto ss = std::stringstream(s);

    for (string line; std::getline(ss, line, '\n');) {
        lines.push_back(rtrim(std::move(line)));
    }

    return lines;
}

auto split_once(const string &s, char c) -> std::pair<string, string> {
    auto delim = s.begin() + s.find(c);
    return {string(s.begin(), delim), string(delim + 1, s.end())};
}

} // namespace utils