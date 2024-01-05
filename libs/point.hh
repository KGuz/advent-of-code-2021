/*
Copyright (c) 2022 Kamil Guz

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include <cmath>
#include <functional>
#include <iostream>

template <typename T>
struct P2 {
    T x{}, y{};

    P2(T x, T y) : x(x), y(y) {}
    P2(const P2& p) = default;
    P2(P2&& p) noexcept = default;

    auto operator=(const P2& p) -> P2& {
        x = p.x, y = p.y;
        return *this;
    }
    auto operator<=>(const P2& p) const = default;

    auto operator+(const P2& p) const -> P2 { return P2(x + p.x, y + p.y); }
    auto operator-(const P2& p) const -> P2 { return P2(x - p.x, y - p.y); }
    auto operator*(const P2& p) const -> P2 { return P2(x * p.x, y * p.y); }
    auto operator/(const P2& p) const -> P2 { return P2(x / p.x, y / p.y); }

    auto operator+=(P2& p) -> P2& {
        x += p.x, y += p.y;
        return *this;
    }
    auto operator-=(P2& p) -> P2& {
        x -= p.x, y -= p.y;
        return *this;
    }
    auto operator*=(P2& p) -> P2& {
        x *= p.x, y *= p.y;
        return *this;
    }
    auto operator/=(P2& p) -> P2& {
        x /= p.x, y /= p.y;
        return *this;
    }

    auto operator+(T s) const -> P2 { return P2(x + s, y + s); }
    auto operator-(T s) const -> P2 { return P2(x - s, y - s); }
    auto operator*(T s) const -> P2 { return P2(x * s, y * s); }
    auto operator/(T s) const -> P2 { return P2(x / s, y / s); }

    auto operator+=(T s) -> P2& {
        x += s, y += s;
        return *this;
    }
    auto operator-=(T s) -> P2& {
        x -= s, y -= s;
        return *this;
    }
    auto operator*=(T s) -> P2& {
        x *= s, y *= s;
        return *this;
    }
    auto operator/=(T s) -> P2& {
        x /= s, y /= s;
        return *this;
    }

    friend auto operator<<(std::ostream& os, const P2& p) -> std::ostream& {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    template <size_t index>
    decltype(auto) get() const {
        static_assert(index < 2, "Index out of bounds for pt2d");
        if constexpr (index == 0) return x;
        if constexpr (index == 1) return y;
    }

    auto norm() -> P2& {
        if (auto len = mag(); len != 0) {
            *this *= (1.0 / len);
        }
        return *this;
    }

    inline auto mag() const -> float { return std::sqrt(x * x + y * y); }

    inline auto dist(const P2& p) const -> float { return (p - this).mag(); }

    inline auto dot(const P2& p) const -> float { return x * p.x + y * p.y; }

    inline auto cross(const P2& p) const -> P2 { return P2(x * p.y, y * p.x); }
};

template <typename T>
struct P3 {
    T x{}, y{}, z{};

    P3(T x, T y, T z) : x(x), y(y), z(z) {}
    P3(const P3& p) = default;
    P3(P3&& p) noexcept = default;

    auto operator=(const P3& p) -> P3& {
        x = p.x, y = p.y, z = p.z;
        return *this;
    }
    auto operator<=>(const P3& p) const = default;

    auto operator+(const P3& p) const -> P3 { return P3(x + p.x, y + p.y, z + p.z); }
    auto operator-(const P3& p) const -> P3 { return P3(x - p.x, y - p.y, z - p.z); }
    auto operator*(const P3& p) const -> P3 { return P3(x * p.x, y * p.y, z * p.z); }
    auto operator/(const P3& p) const -> P3 { return P3(x / p.x, y / p.y, z / p.z); }

    auto operator+=(P3& p) -> P3& {
        x += p.x, y += p.y, z += p.z;
        return *this;
    }
    auto operator-=(P3& p) -> P3& {
        x -= p.x, y -= p.y, z -= p.z;
        return *this;
    }
    auto operator*=(P3& p) -> P3& {
        x *= p.x, y *= p.y, z *= p.z;
        return *this;
    }
    auto operator/=(P3& p) -> P3& {
        x /= p.x, y /= p.y, z /= p.z;
        return *this;
    }

    auto operator+(T s) const -> P3 { return P3(x + s, y + s, z + s); }
    auto operator-(T s) const -> P3 { return P3(x - s, y - s, z - s); }
    auto operator*(T s) const -> P3 { return P3(x * s, y * s, z * s); }
    auto operator/(T s) const -> P3 { return P3(x / s, y / s, z / s); }

    auto operator+=(T s) -> P3& {
        x += s, y += s, z += s;
        return *this;
    }
    auto operator-=(T s) -> P3& {
        x -= s, y -= s, z -= s;
        return *this;
    }
    auto operator*=(T s) -> P3& {
        x *= s, y *= s, z *= s;
        return *this;
    }
    auto operator/=(T s) -> P3& {
        x /= s, y /= s, z /= s;
        return *this;
    }

    friend auto operator<<(std::ostream& os, const P3& p) -> std::ostream& {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }

    template <size_t index>
    decltype(auto) get() const {
        static_assert(index < 3, "Index out of bounds for pt3d");
        if constexpr (index == 0) return x;
        if constexpr (index == 1) return y;
        if constexpr (index == 2) return z;
    }

    auto norm() -> P3& {
        if (auto len = mag(); len != 0) {
            *this *= (1.0 / len);
        }
        return *this;
    }

    inline auto mag() const -> float { return std::sqrt(x * x + y * y + z * z); }

    inline auto dist(const P3& p) const -> float { return (p - this).mag(); }

    inline auto dot(const P3& p) const -> float { return x * p.x + y * p.y + z * p.z; }

    inline auto cross(const P3& p) const -> P3 {
        return P3(y * p.z - z * p.y, -(x * p.z - z * p.x), x * p.y - y * p.x);
    }
};

/* -------------------------------- utility functions -------------------------------- */
template <typename T>
auto pt(T x, T y) -> P2<T> {
    return P2(x, y);
}
template <typename T>
auto pt(T x, T y, T z) -> P3<T> {
    return P3(x, y, z);
}

template <typename T>
auto to_point(std::pair<T, T>&& pair) -> P2<T> {
    return pt(pair.first, pair.second);
}
template <typename T>
auto to_point(std::tuple<T, T>&& tuple) -> P2<T> {
    return pt(get<0>(tuple), get<1>(tuple));
}
template <typename T>
auto to_point(std::tuple<T, T, T>&& tuple) -> P3<T> {
    return pt(get<0>(tuple), get<1>(tuple), get<2>(tuple));
}
template <typename T>
auto to_point(const std::pair<T, T>& pair) -> P2<T> {
    return pt(pair.first, pair.second);
}
template <typename T>
auto to_point(const std::tuple<T, T>& tuple) -> P2<T> {
    return pt(get<0>(tuple), get<1>(tuple));
}
template <typename T>
auto to_point(const std::tuple<T, T, T>& tuple) -> P3<T> {
    return pt(get<0>(tuple), get<1>(tuple), get<2>(tuple));
}

/* --------------------------------- hash functions ---------------------------------- */
template <typename T>
struct std::hash<P2<T>> {
    auto operator()(const P2<T>& p) const noexcept -> size_t {
        return std::hash<T>{}(p.x) ^ (std::hash<T>{}(p.y) << 1);
    }
};
template <typename T>
struct std::hash<P3<T>> {
    auto operator()(const P3<T>& p) const noexcept -> size_t {
        return ((hash<T>{}(p.x) ^ (hash<T>{}(p.y) << 1)) >> 1) ^ (hash<T>{}(p.z) << 1);
    }
};

/* ------------------------------- structured bindings ------------------------------- */
template <typename T>
struct std::tuple_size<P2<T>> : std::integral_constant<size_t, 2> {};

template <typename T>
struct std::tuple_size<P3<T>> : std::integral_constant<size_t, 3> {};

template <typename T, size_t index>
struct std::tuple_element<index, P2<T>> {
    using type = T;
};
template <typename T, size_t index>
struct std::tuple_element<index, P3<T>> {
    using type = T;
};
