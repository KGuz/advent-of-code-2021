module;
#include "itertools.hh"
#include "pprint.hh"
#include <algorithm>
#include <coroutine>
#include <exception>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

export module utilities;
export using std::string, std::vector;
export namespace ranges = std::ranges;
export namespace views = std::views;

namespace iter {
template <typename C, typename V>
auto append(C& container, V&& value) {
    if constexpr (requires(C & c, V && v) { c.push_back(std::forward<V>(v)); }) {
        return container.push_back(std::forward<V>(value));
    } else {
        return container.insert(container.end(), std::forward<V>(value));
    }
}

export template <template <typename> typename C, typename I>
auto collect(I&& iterator) {
    using value_t = std::decay_t<decltype(*iterator.begin())>;

    C<value_t> container;
    if constexpr (requires(I && iter) { iter.size(); }) container.reserve(iterator.size());

    for (auto&& value : iterator) {
        append(container, std::forward<value_t>(value));
    }
    return container;
}

export template <typename I>
auto collect_vec(I&& iterator) {
    return collect<vector>(iterator);
}
} // namespace iter

export namespace utl {
/* --------------------------------- print utilities --------------------------------- */
inline auto print(std::ostream& os, const auto&... args) { pprint::PrettyPrinter(os).print(args...); }

inline auto print(const auto&... args) { utl::print(std::cout, args...); }

inline auto print_inline(std::ostream& os, const auto&... args) {
    pprint::PrettyPrinter(os).compact(true).print(args...);
}

inline auto print_inline(const auto&... args) { utl::print_inline(std::cout, args...); }

/* --------------------------------- string utilities -------------------------------- */
inline auto ltrim(string&& s) -> string {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    return s;
}

inline auto rtrim(string&& s) -> string {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    return s;
}

inline auto trim(string&& s) -> string { return rtrim(ltrim(std::move(s))); }

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

template <typename T>
inline auto parse(const string& str) -> T {
    return static_cast<T>(std::stof(str));
}

auto lines(const string& s) -> vector<string> {
    auto lines = vector<string>{};
    auto ss = std::stringstream(s);

    for (string line; std::getline(ss, line);) {
        lines.push_back(rtrim(std::move(line)));
    }
    return lines;
}

/* ------------------------------- algorithm utilities ------------------------------- */
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
auto concat(const vector<T>& a, const vector<T>& b) {
    auto c = vector<T>{a.begin(), a.end()};
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
auto min(const vector<T>& vec, Predicate pred) {
    auto min_val = INT_MAX, min_idx = 0;
    for (const auto& [idx, elem] : iter::enumerate(vec)) {
        if (auto val = pred(elem); val < min_val) {
            min_val = val, min_idx = idx;
        }
    }
    return std::make_pair(min_val, vec[min_idx]);
}

template <typename T, class Predicate>
auto max(const vector<T>& vec, Predicate pred) {
    auto max_val = INT_MIN, max_idx = static_cast<int>(vec.size() - 1);
    for (const auto& [idx, elem] : iter::enumerate(vec)) {
        if (auto val = pred(elem); val > max_val) {
            max_val = val, max_idx = idx;
        }
    }
    return std::make_pair(max_val, vec[max_idx]);
}

inline auto to_vector(ranges::range auto&& range) {
    return ranges::to<vector>(range);
}

/* --------------------------------- generator impl ---------------------------------- */

template <typename T>
struct generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        T value_;
        std::exception_ptr exception_;

        generator get_return_object() { return generator(handle_type::from_promise(*this)); }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { exception_ = std::current_exception(); }

        template <std::convertible_to<T> From>
        std::suspend_always yield_value(From&& from) {
            value_ = std::forward<From>(from);
            return {};
        }
        void return_void() {}
    };

    handle_type h_;

    generator(handle_type h) : h_(h) {}
    ~generator() { h_.destroy(); }
    explicit operator bool() {
        fill();
        return !h_.done();
    }
    T operator()() {
        fill();
        full_ = false;
        return std::move(h_.promise().value_);
    }

private:
    bool full_ = false;

    void fill() {
        if (!full_) {
            h_();
            if (h_.promise().exception_) std::rethrow_exception(h_.promise().exception_);
            full_ = true;
        }
    }
};
} // namespace utl
