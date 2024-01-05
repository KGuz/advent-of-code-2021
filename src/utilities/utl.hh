#pragma once
#include "itertools.hh"
#include "pprint.hh"
#include <algorithm>
#include <climits>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <vector>

namespace ranges = std::ranges;
namespace views = std::views;
namespace pp = pprint;

namespace pprint { // extension of pprint.hh library
inline auto print(std::ostream& os, const auto&... args) {
    pprint::PrettyPrinter(os).print(args...);
}

inline auto print(const auto&... args) { print(std::cout, args...); }

inline auto print_inline(std::ostream& os, const auto&... args) {
    pprint::PrettyPrinter(os).compact(true).print(args...);
}

inline auto print_inline(const auto&... args) { print_inline(std::cout, args...); }
} // namespace pprint

namespace iter { // extension of itertools.hh library
template <typename C, typename V>
auto append(C& container, V&& value) {
    if constexpr (requires(C& c, V&& v) { c.push_back(std::forward<V>(v)); }) {
        return container.push_back(std::forward<V>(value));
    } else {
        return container.insert(container.end(), std::forward<V>(value));
    }
}

template <template <typename> typename C, typename I>
auto collect(I&& iterator) {
    using value_t = std::decay_t<decltype(*iterator.begin())>;

    C<value_t> container;
    if constexpr (requires(I&& iter) { iter.size(); }) {
        container.reserve(iterator.size());
    }

    for (auto&& value : iterator) {
        append(container, std::forward<value_t>(value));
    }
    return container;
}
} // namespace iter

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

template <ranges::range R>
inline auto to_vector(R&& r) {
    return std::vector(ranges::begin(r), ranges::end(r));
}

template <typename T>
auto intersection(const std::set<T>& a, const std::set<T>& b) -> std::set<T> {
    std::set<T> c;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.end()));
    return c;
}

template <typename T>
auto difference(const std::set<T>& a, const std::set<T>& b) -> std::set<T> {
    std::set<T> c;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.end()));
    return c;
}

template <typename T>
auto concat(const std::vector<T>& a, const std::vector<T>& b) {
    auto c = std::vector<T>{a.begin(), a.end()};
    c.insert(c.end(), b.begin(), b.end());
    return c;
}

template <class Iterable, class Predicate>
auto reduce(const Iterable& iter, auto&& init, Predicate pred) {
    return std::accumulate(iter.begin(), iter.end(), init, pred);
}

template <class Iterable>
auto contains(const Iterable& iter, const auto& val) -> bool {
    return std::any_of(iter.begin(), iter.end(), [&val](const auto& elem) { return elem == val; });
}

template <typename T, class Predicate>
auto min(const std::vector<T>& vec, Predicate pred) {
    auto min_val = INT_MAX, min_idx = 0;
    for (const auto& [idx, elem] : iter::enumerate(vec)) {
        if (auto val = pred(elem); val < min_val) {
            min_val = val, min_idx = idx;
        }
    }
    return std::make_pair(min_val, vec[min_idx]);
}

template <typename T, class Predicate>
auto max(const std::vector<T>& vec, Predicate pred) {
    auto max_val = INT_MIN, max_idx = static_cast<int>(vec.size() - 1);
    for (const auto& [idx, elem] : iter::enumerate(vec)) {
        if (auto val = pred(elem); val > max_val) {
            max_val = val, max_idx = idx;
        }
    }
    return std::make_pair(max_val, vec[max_idx]);
}
} // namespace utl
