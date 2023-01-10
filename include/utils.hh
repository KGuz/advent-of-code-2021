#pragma once

#include "pprint.hh"
#include <format>
#include <ranges>
#include <sstream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

namespace views {
using namespace std::views;
}
namespace ranges {
using namespace std::ranges;
}

namespace {
template <typename Iterable>
class enumerate_object {
  private:
    Iterable _iter;
    size_t _size;
    decltype(std::begin(_iter)) _begin;
    const decltype(std::end(_iter)) _end;

  public:
    enumerate_object(Iterable iter) : _iter(iter), _size(0), _begin(std::begin(iter)), _end(std::end(iter)) {}

    const enumerate_object &begin() const { return *this; }
    const enumerate_object &end() const { return *this; }

    bool operator!=(const enumerate_object &) const { return _begin != _end; }

    void operator++() {
        ++_begin;
        ++_size;
    }

    auto operator*() const -> std::pair<size_t, decltype(*_begin)> { return {_size, *_begin}; }
};
} // namespace

namespace utils {
inline auto ltrim(string &&s) -> string;

inline auto rtrim(string &&s) -> string;

inline auto trim(string &&s) -> string;

auto lines(const string &s) -> vector<string>;

auto split_once(const string &s, char c) -> std::pair<string, string>;

template <class Iterable, class UnaryPredicate>
auto map(const Iterable &vec, UnaryPredicate pred) {
    using result_t = std::decay_t<decltype(pred(vec[0]))>;

    vector<result_t> res;
    res.reserve(vec.size());
    std::transform(vec.begin(), vec.end(), std::back_inserter(res), pred);
    return res;
}

template <typename... Args>
auto print(Args... args) {
    auto printer = pprint::PrettyPrinter();
    printer.compact(true);
    printer.print(args...);
}

template <typename T> inline
auto parse(const string &str) -> T { return static_cast<T>(std::stof(str)); }

template <typename Iterable>
auto enumerate(Iterable &&iter) -> enumerate_object<Iterable> {
    return {std::forward<Iterable>(iter)};
}
} // namespace utils
