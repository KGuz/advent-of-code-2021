module;
#include "pprint.hh"
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <span>
#include <string>
#include <vector>
export module utilities;

using std::string, std::vector;

template <typename Iterable>
class Enumerator {
private:
    Iterable _iter;
    size_t _size;
    decltype(std::begin(_iter)) _begin;
    const decltype(std::end(_iter)) _end;

public:
    Enumerator(Iterable iter) : _iter(iter), _size(0), _begin(std::begin(iter)), _end(std::end(iter)) {}
    const Enumerator& begin() const { return *this; }
    const Enumerator& end() const { return *this; }
    bool operator!=(const Enumerator&) const { return _begin != _end; }
    void operator++() { ++_begin, ++_size; }
    auto operator*() const -> std::pair<size_t, decltype(*_begin)> { return {_size, *_begin}; }
};

struct Slice {
    size_t begin, end;

    template <std::ranges::viewable_range ViewableRange>
    friend auto operator|(ViewableRange& vr, const Slice& s) {
        return std::span{vr.begin() + s.begin, s.end - s.begin};
    }
};

export namespace utl {
template <typename Iterable>
auto enumerate(Iterable&& iter) -> Enumerator<Iterable> {
    return {std::forward<Iterable>(iter)};
}

auto slice(size_t b, size_t e) { return Slice{b, e}; }

template <std::ranges::viewable_range ViewableRange>
auto slice(ViewableRange& vr, size_t b, size_t e) {
    return vr | slice(b, e);
}

template <typename... Args>
auto print(Args... args) {
    pprint::PrettyPrinter().print(args...);
}

template <typename... Args>
auto print(std::ostream& os, Args... args) {
    pprint::PrettyPrinter(os).print(args...);
}

template <typename T>
inline auto parse(const string& str) -> T {
    return static_cast<T>(std::stof(str));
}

template <class Iterable, class Predicate>
auto map(const Iterable& iter, Predicate pred) {
    using result_t = std::decay_t<decltype(pred(iter[0]))>;

    vector<result_t> res;
    res.reserve(iter.size());
    std::transform(iter.begin(), iter.end(), std::back_inserter(res), pred);
    return res;
}

inline auto ltrim(string&& s) -> string {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    return s;
}

inline auto rtrim(string&& s) -> string {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    return s;
}

inline auto trim(string&& s) -> string { return rtrim(ltrim(std::move(s))); }

auto lines(const string& s) -> vector<string> {
    auto lines = vector<string>{};
    auto ss = std::stringstream(s);

    for (string line; std::getline(ss, line);) {
        lines.push_back(rtrim(std::move(line)));
    }
    return lines;
}

auto split_once(const string& s, char c) -> std::pair<string, string> {
    auto delim = s.begin() + static_cast<int>(s.find(c));
    return {string(s.begin(), delim), string(delim + 1, s.end())};
}
auto split(const string& s, char c) -> vector<string> {
    auto res = vector<string>{};
    auto ss = std::stringstream(s);

    for (string line; std::getline(ss, line, c);) {
        if (not line.empty()) {
            res.push_back(line);
        }
    }
    return res;
}

template <typename T, class Predicate>
auto min(const vector<T>& vec, Predicate pred) {
    auto min_val = INT_MAX, min_idx = 0;
    for (const auto& [idx, elem] : enumerate(vec)) {
        if (auto val = pred(elem); val < min_val) {
            min_val = val, min_idx = idx;
        }
    }
    return std::make_pair(min_val, vec[min_idx]);
}

template <typename T, class Predicate>
auto max(const vector<T>& vec, Predicate pred) {
    auto max_val = INT_MIN, max_idx = static_cast<int>(vec.size() - 1);
    for (const auto& [idx, elem] : enumerate(vec)) {
        if (auto val = pred(elem); val > max_val) {
            max_val = val, max_idx = idx;
        }
    }
    return std::make_pair(max_val, vec[max_idx]);
}

template <class Iterable>
auto contains(const Iterable& iter, const auto& val) -> bool {
    return std::any_of(iter.begin(), iter.end(), [&val](const auto& elem) { return elem == val; });
}

template <class Iterable, class Predicate>
auto reduce(const Iterable& iter, const auto& init, Predicate pred) {
    return std::accumulate(iter.begin(), iter.end(), init, pred);
}
} // namespace utl
