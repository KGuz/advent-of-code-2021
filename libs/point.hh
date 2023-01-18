#pragma once
#include <cmath>
#include <iostream>

template <class T>
struct pt2 {
    T x, y;

    pt2() : x(0), y(0) {}
    pt2(T x, T y) : x(x), y(y) {}
    pt2(const pt2& p) : x(p.x), y(p.y) {}

    pt2& operator=(const pt2& p) {
        x = p.x, y = p.y;
        return *this;
    }

    pt2 operator+(pt2& p) { return pt2(x + p.x, y + p.y); }
    pt2 operator-(pt2& p) { return pt2(x - p.x, y - p.y); }

    pt2& operator+=(pt2& p) {
        x += p.x, y += p.y;
        return *this;
    }
    pt2& operator-=(pt2& p) {
        x -= p.x, y -= p.y;
        return *this;
    }

    pt2 operator+(T s) { return pt2(x + s, y + s); }
    pt2 operator-(T s) { return pt2(x - s, y - s); }
    pt2 operator*(T s) { return pt2(x * s, y * s); }
    pt2 operator/(T s) { return pt2(x / s, y / s); }

    pt2& operator+=(T s) {
        x += s, y += s;
        return *this;
    }
    pt2& operator-=(T s) {
        x -= s, y -= s;
        return *this;
    }
    pt2& operator*=(T s) {
        x *= s, y *= s;
        return *this;
    }
    pt2& operator/=(T s) {
        x /= s, y /= s;
        return *this;
    }

    float mag() const { return std::sqrt(x * x + y * y); }

    pt2& norm() {
        if (mag() == 0) {
            return *this;
        }
        *this *= (1.0 / mag());
        return *this;
    }

    float dist(pt2 p) const {
        pt2 d(p.x - x, p.y - y);
        return d.mag();
    }

    friend std::ostream& operator<<(std::ostream& os, const pt2& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    bool operator<(const pt2& p) const { return x * x + y * y < p.x * p.x + p.y * p.y; }

    //    static float dot(pt2 p1, pt2 p2) { return p1.x * p2.x + p1.y * p2.y; }
    //    static float cross(pt2 p1, pt2 p2) { return (p1.x * p2.y) - (p1.y * p2.x); }
};

template <class T>
struct pt3 {
    T x, y, z;

    pt3() : x(0), y(0), z(0) {}
    pt3(T x, T y, T z) : x(x), y(y), z(z) {}
    pt3(const pt3& p) = default;

    pt3& operator=(const pt3& p) {
        x = p.x, y = p.y, z = p.z;
        return *this;
    }

    pt3 operator+(pt3& p) { return pt3(x + p.x, y + p.y, z + p.z); }
    pt3 operator-(pt3& p) { return pt3(x - p.x, y - p.y, z - p.z); }

    pt3& operator+=(pt3& p) {
        x += p.x, y += p.y, z += p.z;
        return *this;
    }
    pt3& operator-=(pt3& p) {
        x -= p.x, y -= p.y, z -= p.z;
        return *this;
    }

    pt3 operator+(T s) { return pt3(x + s, y + s, z + s); }
    pt3 operator-(T s) { return pt3(x - s, y - s, z - s); }
    pt3 operator*(T s) { return pt3(x * s, y * s, z * s); }
    pt3 operator/(T s) { return pt3(x / s, y / s, z / s); }

    pt3& operator+=(T s) {
        x += s, y += s, z += s;
        return *this;
    }
    pt3& operator-=(T s) {
        x -= s, y -= s, z -= s;
        return *this;
    }
    pt3& operator*=(T s) {
        x *= s, y *= s, z *= s;
        return *this;
    }
    pt3& operator/=(T s) {
        x /= s, y /= s, z /= s;
        return *this;
    }

    float mag() const { return std::sqrt(x * x + y * y + z * z); }

    pt3& norm() {
        if (mag() == 0) {
            return *this;
        }
        *this *= (1.0 / mag());
        return *this;
    }

    float dist(pt3 p) const {
        pt3 d(p.x - x, p.y - y, p.z - z);
        return d.mag();
    }

    friend std::ostream& operator<<(std::ostream& os, const pt3& p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }

//    bool operator<(const pt3& p) const {
//        if (x == p.x) {
//
//        } else {
//            return x < p.x
//        }
//        return ;
//    }
};

template <typename T>
auto pt(T x, T y) -> pt2<T> {
    return pt2(x, y);
}

template <typename T>
auto pt(T x, T y, T z) -> pt3<T> {
    return pt3(x, y, z);
}