//
// Created by helywin on 2021/10/14.
//

#ifndef RAY_TRACING_VEC3_HPP
#define RAY_TRACING_VEC3_HPP

#include <cmath>
#include <iostream>
#include "math.hpp"

using std::sqrt;

class vec3
{
public:
    vec3() : e{0, 0, 0}
    {}

    vec3(double e0, double e1, double e2) : e{e0, e1, e2}
    {}

    double x() const
    { return e[0]; }

    double y() const
    { return e[1]; }

    double z() const
    { return e[2]; }

    vec3 operator-() const
    { return vec3(-e[0], -e[1], -e[2]); }

    double operator[](int i) const
    { return e[i]; }

    double &operator[](int i)
    { return e[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline static vec3 random()
    {
        return {random_double(), random_double(), random_double()};
    }

    inline static vec3 random(double min, double max)
    {
        return {random_double(min, max),
                random_double(min, max),
                random_double(min, max)};
    }

public:
    double e[3];
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator+(const vec3 &u, double v)
{
    return {u.e[0] + v, u.e[1] + v, u.e[2] + v};
}

inline vec3 operator+(double u, const vec3 &v)
{
    return {u + v.e[0], u + v.e[1], u + v.e[2]};
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(double t, const vec3 &v)
{
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0]
           + u.e[1] * v.e[1]
           + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return {
            u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]
    };
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

// ????????????????????????
vec3 random_in_unit_sphere1()
{
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_in_unit_sphere()
{
    double u = random_double(0, 1);
    double v = random_double(0, 1);
    double theta = 2 * pi * u;
    double phi = acos(2 * v - 1);
    double x = sin(theta) * sin(phi);
    double y = cos(theta) * sin(phi);
    double z = 2 * v - 1;
    return {x, y, z};
}

#endif //RAY_TRACING_VEC3_HPP
