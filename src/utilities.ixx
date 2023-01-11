module;
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include "pprint.hh"

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
    const Enumerator &begin() const { return *this; }
    const Enumerator &end() const { return *this; }
    bool operator!=(const Enumerator &) const { return _begin != _end; }
    void operator++() { ++_begin, ++_size; }
    auto operator*() const -> std::pair<size_t, decltype(*_begin)> { return {_size, *_begin}; }
};

export namespace utl {
template <typename Iterable>
auto enumerate(Iterable &&iter) -> Enumerator<Iterable> {
    return {std::forward<Iterable>(iter)};
}

template <typename... Args>
auto print(Args... args) {
    pprint::PrettyPrinter().print(args...);
}

template <typename T>
inline auto parse(const string &str) -> T {
    return static_cast<T>(std::stof(str));
}

template <class Iterable, class Predicate>
auto map(const Iterable &vec, Predicate pred) {
    using result_t = std::decay_t<decltype(pred(vec[0]))>;

    vector<result_t> res;
    res.reserve(vec.size());
    std::transform(vec.begin(), vec.end(), std::back_inserter(res), pred);
    return res;
}

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
    auto delim = s.begin() + static_cast<int>(s.find(c));
    return {string(s.begin(), delim), string(delim + 1, s.end())};
}
} // namespace utl